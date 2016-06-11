#include "QMetroDialog.h"


QMetroDialog::QMetroDialog(SysBarType type)
{
	this->resize(400, 300);

	bool isConnected = false;

	switch (type)	
	{
	case QMetroDialog::MIN_MAX_CLS:
		createSystemButton(btMin, QIcon(":/QMetro/min"));
		isConnected = connect(btMin, SIGNAL(clicked()), this, SLOT(onBtMinization()));

		createSystemButton(btFullScreen, QIcon(":/QMetro/max"));
		isConnected = connect(btFullScreen, SIGNAL(clicked()), this, SLOT(onBtFullScreen()));

		createSystemButton(btClose, QIcon(":/QMetro/close"));
		isConnected = connect(btClose, SIGNAL(clicked()), this, SLOT(close()));
		break;

	case QMetroDialog::MIN_CLS:
		createSystemButton(btMin, QIcon(":/QMetro/min"));
		connect(btMin, SIGNAL(clicked()), this, SLOT(onBtMinization()));

		createSystemButton(btClose, QIcon(":/QMetro/close"));
		connect(btClose, SIGNAL(clicked()), this, SLOT(close()));
		break;

	case QMetroDialog::CLS:
		createSystemButton(btClose, QIcon(":/QMetro/close"));
		connect(btClose, SIGNAL(clicked()), this, SLOT(close()));
		break;

	default:
		createSystemButton(btClose, QIcon(":/QMetro/close"));
		connect(btClose, SIGNAL(clicked()), this, SLOT(close()));
		break;
	}

	hlSysLayout->setGeometry(QRect(0, 0, this->width(), 20));
}


QMetroDialog::~QMetroDialog()
{
}