# Перевод

  * Извлечь ресурсы для перевода, используя `Translate` модуль по пути `/admin/config/regional/translate/extract`

  * Перевести ресурсы внутри извлеченного файла и поместить его в `translate` директорию

```
xgettext -L php --keyword=t include/begateway_payment.* -j -d translations/ru_RU
xgettext -L php --keyword=t begateway_payment.module -j -d translations/ru_RU
```
# Translation

  * Extract resources to translate with assistance of the `Translate` module located by the path `/admin/config/regional/translate/extract`

  * Translate resource file and put to the `translate` folder

```
xgettext -L php --keyword=t include/begateway_payment.* -j -d translations/ru_RU
xgettext -L php --keyword=t begateway_payment.module -j -d translations/ru_RU
```
