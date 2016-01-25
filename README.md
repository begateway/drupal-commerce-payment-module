# Модуль оплаты beGateway для Drupal Commerce

## Установка

  * (Скачайте)[] архив с модулем и распакуйте его
  * Папку `begateway_payment ` с модулем положите в `sites/all/modules`
  * Убедитесь, что Drupal модуль (libraries)[https://www.drupal.org/project/libraries] установлен и включен
  * (Скачайте)[] архив библиотеки и раскакуйте его
  * Папку `beGateway` библиотеки положите в `sites/all/libraries`
  * Включите модуль `beGateway payment` в Drupal
  * Настройка модуля находятся в `/admin/commerce/config/payment-methods`
  * Список заказов и работа c транзакциями находятся в `/admin/config/begateway_payment/orders`


### Вы можете использовать следующие данные, чтобы настроить способ оплаты в тестовом режиме

* Идентификационный номер магазина - 361

* Секретный ключ магазина - b8647b68898b084b836474ed8d61ffe117c9a01168d867f24953b776ddcb134d

* Домен платежного шлюза - demo-gateway.begateway.com

* Домен платежной страницы - checkout.begateway.com

### Используйте следующий тестовый набор для тестового платежа:
* Номер карты 4200000000000000

* Имя на карте John Doe

* Месяц срока действия карты 01, чтобы получить успешный платеж

* Месяц срока действия карты 10, чтобы получить неуспешный платеж

* CVC 123


# Module payment beGateway for Drupal Commerce

## Installation

*  Folder with a module put in (sites/all/modules/begateway_payment)

*  Put the library in a folder (sites/all/libraries/beGateway)
    Make sure the path to the library file becomes: (sites/all/libraries/beGateway)
    [download url] (https://github.com/beGateway/begateway-api-php)

* Module settings are in (/admin/commerce/config/payment-methods)

* List of order and transactions are in (/admin/config/begateway_payment/orders)

### You can use the following information to adjust the payment method in test mode:

* Identification number of the store - 361

* The private key store - b8647b68898b084b836474ed8d61ffe117c9a01168d867f24953b776ddcb134d

* Domain payment gateway - demo-gateway.begateway.com

* Domain payment page - checkout.begateway.com

###  Use the following test kit to test payment:

* Card number 4200000000000000

* The name on the map of John Doe

* Month card expires 01 to get a successful payment

* Month card expires 10 to get an unsuccessful delivery

* CVC 123
