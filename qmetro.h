#ifndef QMETRO_H
#define QMETRO_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qpushbutton.h>
#include <QMouseEvent>
#include <qmenu.h>
#include <qmenubar.h>
#include <qtoolbar.h>
#include <qaction.h>
#include <qlabel.h>
#include <qlabel.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qsystemtrayicon.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qlineedit.h>
#include <qtimer.h>
#include <qstring.h>

class QMetro : public QMainWindow
{
	Q_OBJECT

public:
	QMetro(QWidget *parent = 0);
	~QMetro();

protected:
	// 鼠标事件
	QPoint dragPosition;
	bool isLeftPressDown;
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	// 右上角系统工具条
	QHBoxLayout *hlSysLayout;
	void createSystemButton(QPushButton* (&pushbutton), QIcon ico);

	QPushButton *btClose;
	QPushButton *btMin;
	QPushButton *btMax;
	QPushButton *btFullScreen;
	QPushButton *btSetting;
	
};

#endif // QMETRO_H
