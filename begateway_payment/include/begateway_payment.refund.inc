<?php
/*
 * Refund confirmation transaction.
 *
 * @param $form
 * @param $form_state
 * @param $order_id
 * @return array
 */
function begateway_refund_form($form, &$form_state, $order_id) {

  $form_state['order_id'] = $order_id;

  $value = begateway_get_order($form_state['order_id']);
  $ow = entity_metadata_wrapper('commerce_order', $value['order_id']);

  $order_total = $ow->commerce_order_total->value();

  $form = array();
  if ($value['flag'] == 2) {
    $form['amount'] = array(
      '#type' => 'textfield',
      '#title' => t('Refund amount (Captured amount: @total )', array('@total' => commerce_currency_format($value['price'], $order_total['currency_code']) )),
      '#default_value' => commerce_currency_amount_to_decimal($value['price'], $order_total['currency_code']),
      '#size' => 16,
    );
  }
  else {
    $form['amount'] = array(
      '#type' => 'textfield',
      '#title' => t('Refund amount (Captured amount: @total )', array('@total' => commerce_currency_format($value['price'], $order_total['currency_code']) )),
      '#default_value' => commerce_currency_amount_to_decimal($order_total['amount'], $order_total['currency_code']),
      '#size' => 16,
    );
  }
  $form = confirm_form($form, t('Are you sure you want to issue a refund?'), '/admin/config/begateway_payment/orders', '', t('Refund'), t('Cancel'), 'confirm');

  return $form;
}

/**
 * Refund transaction validate.
 */
function begateway_refund_form_validate($form, &$form_state) {

  $value = begateway_get_order($form_state['order_id']);
  $ow = entity_metadata_wrapper('commerce_order', $value['order_id']);

  $order_total = $ow->commerce_order_total->value();

  if (!is_numeric($form['amount']['#value']) || $form['amount']['#value'] <= 0) {
    form_set_error('amount', t('You must specify a positive numeric amount to refund.'));
    return FALSE;
  }

  if (commerce_currency_decimal_to_amount($form['amount']['#value'], $order_total['currency_code']) > $value['price']) {
    form_set_error('amount', t('You cannot refund more than it was payed through beGateway.'));
    return FALSE;
  }
}

/**
 * Refund transaction.
 *
 * @param $form
 * @param $form_state
 */
function begateway_refund_form_submit($form, &$form_state) {

  $id = $form_state['order_id'];

  $value = begateway_get_order($form_state['order_id']);
  $ow = entity_metadata_wrapper('commerce_order', $value['order_id']);
  $order_total = $ow->commerce_order_total->value();

  begateway_payment_method_load();

  $price = commerce_currency_decimal_to_amount($form['amount']['#value'], $order_total['currency_code']);

  $refund = new \beGateway\Refund;
  $refund->setParentUid($value['parent_uid']);
  $refund->money->setCents($price);
  $refund->setReason('customer request');
  
  $refund_response = $refund->submit();

  if ($refund_response->isSuccess()) {
    db_update('begateway_payments')->fields(array(
      'status' => 'Refunded',
      'price' => $value['price'] - $price,
      'parent_uid' => $refund_response->getUid(),
      'flag' => 0,
    ))->condition('id', $id)->execute();

    $transaction = commerce_payment_transaction_new('begateway', $value['order_id']);
    $transaction->amount = -1 * $price;
    $transaction->currency_code = $ow->commerce_order_total->currency_code->value();
    $transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
    $transaction->remote_status = 'Refunded';
    $transaction->remote_id = $refund_response->getUid();
    $transaction->message = t('The payment has been refunded.');
    commerce_payment_transaction_save($transaction);

    drupal_set_message(t("Refunded successfully.") . ' ' . t("UID: ") . $refund_response->getUid());
  }
  else {
    drupal_set_message(t("Refund error:") . ' ' . $refund_response->getMessage(), 'error');
  }

  drupal_goto('/admin/config/begateway_payment/orders');
}
?>
