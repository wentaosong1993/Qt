	QRegExp regContactPhoneNumber("^[0-9]{3,4}-([0-9]{3,8}$)|(^[1-9]{3,4}-([0-9]{3}-([0-9]{3,4}$)))|(^[1-9][0-9]{2,3}-([0-9]{3}-([0-9]{3,4}$)))|(^[1-9][0-9]{9}$)|(^[1][0-9]{10}$)");
	QValidator *validatorPhoneNumberContent = new QRegExpValidator(regContactPhoneNumber, ui.phoneNumberLineEdit);
	ui.phoneNumberLineEdit->setValidator(validatorPhoneNumberContent);