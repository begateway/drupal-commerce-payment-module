all:
	if [[ -e begateway_payment.zip ]]; then rm begateway_payment.zip; fi
	zip -r begateway_payment.zip begateway_payment
	if [[ -e begateway_library.zip ]]; then rm begateway_library.zip; fi
	cd libraries && zip -r ../begateway_library.zip beGateway
