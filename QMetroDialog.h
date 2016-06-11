#pragma once
#include "QMetroWindow.h"
class QMetroDialog :
	public QMetroWindow
{

	Q_OBJECT

public:
	enum SysBarType{
		MIN_MAX_CLS,
		MIN_CLS,
		CLS
	};
	QMetroDialog(SysBarType type);
	~QMetroDialog();

};

