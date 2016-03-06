<?php
/**
 * Capture confirmation transaction.
 *
 * @param $form
 * @param $form_state
 * @param $order_id
 * @return array
 */
function begateway_capture_form($form, &$form_state, $order_id) {

  $form_state['order_id'] = $order_id;
  $value = begateway_get_order($form_state['order_id']);

  $ow = entity_metadata_wrapper('commerce_order', $value['order_id']);

  $order_total = $ow->commerce_order_total->value();
  $form = array();
  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Capture amount (Order amount: @total)', array('@total' => commerce_currency_amount_to_decimal($order_total['amount'], $order_total['currency_code']) . ' ' . $order_total['currency_code'])),
    '#default_value' => commerce_currency_amount_to_decimal($value['price'], $order_total['currency_code']),
    '#size' => 16,
  );
  $form = confirm_form($form, t('Are you sure you want to issue a capture?'), '/admin/config/begateway_payment/orders', '', t('Capture'), t('Cancel'), 'confirm');

  return $form;
}

/**
 * Capture transaction validate.
 *
 * @param $form
 * @param $form_state
 * @return bool
 */
function begateway_capture_form_validation($form, &$form_state) {

  $value = begateway_get_order($form_state['order_id']);
  $ow = entity_metadata_wrapper('commerce_order', $value['order_id']);

  $order_total = $ow->commerce_order_total->value();

  if (!is_numeric($form['amount']['#value']) || $form['amount']['#value'] <= 0) {
    form_set_error('amount', t('You must specify a positive numeric amount to be captured.'));
    return FALSE;
  }

  if (commerce_currency_decimal_to_amount($form['amount']['#value'], $order_total['currency_code']) > $value['price']) {
    form_set_error('amount', t('You cannot capture more than it was authorized through beGateway.'));
    return FALSE;
  }
}

/**
 * Capture transaction.
 *
 * @param $form
 * @param $form_state
 */
function begateway_capture_form_submit($form, &$form_state) {

  $id = $form_state['order_id'];

  $value = begateway_get_order($form_state['order_id']);
  $ow = entity_metadata_wrapper('commerce_order', $value['order_id']);
  $order_total = $ow->commerce_order_total->value();

  $price = commerce_currency_decimal_to_amount($form['amount']['#value'], $order_total['currency_code']);

  begateway_payment_method_load();

  $capture = new \beGateway\Capture;
  $capture->setParentUid($value['parent_uid']);
  $capture->money->setCents($price);
  $capture->money->setCurrency($order_total['currency_code']);
  $capture_response = $capture->submit();
  if ($capture_response->isSuccess()) {

    $flag = 2;

    if ($value['flag'] == 2) {
      $flag = 0;
    }

    db_update('begateway_payments')->fields(array(
      'status' => 'Captured',
      'price' => $price,
      'parent_uid' => $capture_response->getUid(),
      'flag' => $flag,
    ))->condition('id', $id)->execute();

    $transaction = commerce_payment_transaction_new('begateway', $value['order_id']);
    $transaction->amount = $price;
    $transaction->currency_code = $order_total['currency_code'];
    $transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
    $transaction->remote_status = 'Captured';
    $transaction->remote_id = $capture_response->getUid();
    $transaction->message = t('The payment has been captured.');
    commerce_payment_transaction_save($transaction);
    $ow->status = 'completed';
    $ow->save();

    drupal_set_message(t("Captured successfully.") . ' ' . t('UID: ') . $capture_response->getUid());
  }
  else {
    drupal_set_message(t("Capture error:") . ' ' . $capture_response->getMessage(), 'error');
  }

  drupal_goto('/admin/config/begateway_payment/orders');
}
?>
