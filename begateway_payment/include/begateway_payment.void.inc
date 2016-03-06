<?php
/**
 * Void confirmation transaction.
 *
 * @param $form
 * @param $form_state
 * @param $order_id
 * @return array
 */
function begateway_void_form($form, &$form_state, $order_id) {
  $form_state['order_id'] = $order_id;

  $value = begateway_get_order($form_state['order_id']);
  $ow = entity_metadata_wrapper('commerce_order', $value['order_id']);
  $order_total = $ow->commerce_order_total->value();

  $form = array();
  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Void amount') . ', ' . $order_total['currency_code'],
    '#attributes' => array('disabled' => 'disabled'),
    '#default_value' => commerce_currency_amount_to_decimal($value['price'], $order_total['currency_code']),
    '#size' => 16,
  );
  $form = confirm_form($form, t('Are you sure you want to issue a void?'), '/admin/config/begateway_payment/orders', '', t('Void'), t('Cancel'), 'confirm');

  return $form;
}

/**
 * Void transaction validate.
 *
 * @param $form
 * @param $form_state
 * @return bool
 */
function begateway_void_form_validation($form, &$form_state) {

  $value = begateway_get_order($form_state['order_id']);
  $ow = entity_metadata_wrapper('commerce_order', $value['order_id']);

  $order_total = $ow->commerce_order_total->value();

  if (!is_numeric($form['amount']['#value']) || $form['amount']['#value'] <= 0) {
    form_set_error('amount', t('You must specify a positive numeric amount to be voided.'));
    return FALSE;
  }

  if (commerce_currency_decimal_to_amount($form['amount']['#value'], $order_total['currency_code']) > $value['price']) {
    form_set_error('amount', t('You cannot void more than it was authorized through beGateway.'));
    return FALSE;
  }
}

/**
 * Void transaction.
 *
 * @param $form
 * @param $form_state
 */
function begateway_void_form_submit($form, &$form_state) {

  $id = $form_state['order_id'];

  $value = begateway_get_order($form_state['order_id']);
  $ow = entity_metadata_wrapper('commerce_order', $value['order_id']);
  $order_total = $ow->commerce_order_total->value();

  begateway_payment_method_load();

  $price = commerce_currency_decimal_to_amount($form['amount']['#value'], $order_total['currency_code']);

  $void = new \beGateway\Void;
  $void->setParentUid($value['parent_uid']);
  $void->money->setCents($price);
  $void->money->setCurrency($ow->commerce_order_total->currency_code->value());
  $void_response = $void->submit();

  if ($void_response->isSuccess()) {

    db_update('begateway_payments')->fields(array(
      'status' => 'Void',
      'parent_uid' => $void_response->getUid(),
      'flag' => '0',
    ))->condition('id', $id)->execute();

    $transaction = commerce_payment_transaction_new('begateway', $value['order_id']);
    $transaction->amount = $price;
    $transaction->currency_code = $ow->commerce_order_total->currency_code->value();
    $transaction->status = COMMERCE_PAYMENT_STATUS_FAILURE;
    $transaction->remote_status = 'Void';
    $transaction->remote_id = $void_response->getUid();
    $transaction->message = t('The payment has been voided.');
    commerce_payment_transaction_save($transaction);

    $ow->status = 'canceled';
    $ow->save();

    drupal_set_message(t('Voided successfully') . ' ' . t('UID: ') . $void_response->getUid());
  } else {
    drupal_set_message(t("Void error:") . ' ' . $void_response->getMessage(), 'error');
  }

  drupal_goto('/admin/config/begateway_payment/orders');
}
?>
