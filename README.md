# Модуль оплаты BeGateway для Drupal Commerce

## Установка

  * [Скачайте](https://github.com/beGateway/drupal-commerce-payment-module/blob/master/begateway_payment.zip?raw=true) архив с модулем и распакуйте его
  * Папку `begateway_payment ` с модулем положите в `sites/all/modules` или воспользуйтесь установкой модуля с помощью __Установить новый модуль__ из администраторской зоны через страницу _Главная → Администрирование → Модули_
  * Включите модуль `BeGateway payment` в Drupal
  * Настройка модуля находятся в `/admin/commerce/config/payment-methods`
  * Список заказов и работа c транзакциями находятся в `/admin/config/begateway_payment/orders`

## Тестирование

Вы можете использовать следующие данные, чтобы настроить способ оплаты в тестовом режиме

  * __Идентификационный номер магазина:__ 361
  * __Секретный ключ магазина:__ b8647b68898b084b836474ed8d61ffe117c9a01168d867f24953b776ddcb134d
  * __Домен платежного шлюза:__ demo-gateway.begateway.com
  * __Домен платежной страницы:__ checkout.begateway.com
  * __Режим работы:__ Тестовый

Используйте следующие данные карты для успешного тестового платежа:

  * Номер карты: 4200000000000000
  * Имя на карте: JOHN DOE
  * Месяц срока действия карты: 01/30
  * CVC: 123

Используйте следующие данные карты для неуспешного тестового платежа:

  * Номер карты: 4005550000000019
  * Имя на карте: JOHN DOE
  * Месяц срока действия карты: 01/30
  * CVC: 123

# Module payment BeGateway for Drupal Commerce

## Installation

  * [Download](https://github.com/beGateway/drupal-commerce-payment-module/blob/master/begateway_payment.zip?raw=true) module archive and unpack it
  * Put the directory `begateway_payment ` to `sites/all/modules` or use `Install new module` link in _Home → Administration → Modules_
  * Enable the `BeGateway payment` module

## Testing

You can use the following information to adjust the payment method in test mode:

  * __Shop ID:__ 361
  * __Shop Key:__ b8647b68898b084b836474ed8d61ffe117c9a01168d867f24953b776ddcb134d
  * __Payment gateway domain:__ demo-gateway.begateway.com
  * __Checkout page domain:__ checkout.begateway.com

Use the following test card to make successful test payment:

  * Card number: 4200000000000000
  * Name on card: JOHN DOE
  * Card expiry date: 01/30
  * CVC: 123

Use the following test card to make failed test payment:

  * Card number: 4005550000000019
  * Name on card: JOHN DOE
  * Card expiry date: 01/30
  * CVC: 123
