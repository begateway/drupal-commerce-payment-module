all:
	if [[ -e begateway_payment.zip ]]; then rm begateway_payment.zip; fi
	zip -r begateway_payment.zip begateway_payment -x "*/test/*" -x "*/.git/*" -x "*/examples/*"
