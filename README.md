# Модуль оплаты beGateway для Drupal Commerce

## Установка

  * [Скачайте](https://github.com/beGateway/drupal-commerce-payment-module/blob/master/begateway_payment.zip?raw=true) архив с модулем и распакуйте его
  * Папку `begateway_payment ` с модулем положите в `sites/all/modules`
  * Убедитесь, что Drupal модуль [libraries](https://www.drupal.org/project/libraries) установлен и включен
  * [Скачайте](https://github.com/beGateway/drupal-commerce-payment-module/blob/master/begateway_library.zip?raw=true) архив библиотеки и распакуйте его
  * Папку `beGateway` библиотеки положите в `sites/all/libraries`
  * Включите модуль `beGateway payment` в Drupal
  * Настройка модуля находятся в `/admin/commerce/config/payment-methods`
  * Список заказов и работа c транзакциями находятся в `/admin/config/begateway_payment/orders`


## Тестирование

Вы можете использовать следующие данные, чтобы настроить способ оплаты в тестовом режиме

  * Идентификационный номер магазина - 361
  * Секретный ключ магазина - b8647b68898b084b836474ed8d61ffe117c9a01168d867f24953b776ddcb134d
  * Домен платежного шлюза - demo-gateway.begateway.com
  * Домен платежной страницы - checkout.begateway.com

Используйте следующий тестовый набор для тестового платежа:

  * Номер карты 4200000000000000
  * Имя на карте John Doe
  * Месяц срока действия карты 01, чтобы получить успешный платеж
  * Месяц срока действия карты 10, чтобы получить неуспешный платеж
  * CVC 123

# Module payment beGateway for Drupal Commerce

## Installation

  * [Download](https://github.com/beGateway/drupal-commerce-payment-module/blob/master/begateway_payment.zip?raw=true) module archive and unpack it
  * Put the directory `begateway_payment ` to `sites/all/modules`
  * Make sure the Drupal module [libraries](https://www.drupal.org/project/libraries) is installed and enabled
  * [Download](https://github.com/beGateway/drupal-commerce-payment-mdule/blob/master/begateway_library.zip?raw=true) library archive and unpack it
  * Put the `beGateway` directory to `sites/all/libraries`
  * Enable the `beGateway payment` module

## Testing

You can use the following information to adjust the payment method in test mode:

  * Identification number of the store - 361
  * The private key store - b8647b68898b084b836474ed8d61ffe117c9a01168d867f24953b776ddcb134d
  * Domain payment gateway - demo-gateway.begateway.com
  * Domain payment page - checkout.begateway.com

Use the following test kit to test payment:

  * Card number 4200000000000000
  * The name on the map of John Doe
  * Month card expires 01 to get a successful payment
  * Month card expires 10 to get an unsuccessful delivery
  * CVC 123
