#include "QMetroMainWindow.h"


QMetroMainWindow::QMetroMainWindow()
{
	this->setWindowTitle("MainWindow");
	this->setMinimumSize(800, 600);
	this->resize(800, 600);
	this->setStyleSheet("background:gray");
	QDesktopWidget *deskdop = QApplication::desktop();
	move((deskdop->width() - this->width()) / 2, (deskdop->height() - this->height()) / 2);
	this->setWindowIcon(QIcon(":/QMetro/ico"));

	// 系统托盘
	createTrayMenu();
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon(":/QMetro/ico"));
	trayIcon->setToolTip(tr("Metro GUI"));
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));
	trayIcon->show();
	trayIcon->showMessage(tr("Metro GUI"), tr("is running now. \n\t ----By Peng Chao!"),
		QSystemTrayIcon::Information, 15000);
	trayIcon->setContextMenu(trayMenu);

	// 系统栏布局

	createSystemButton(btMin, QIcon(":/QMetro/min"));
	connect(btMin, SIGNAL(clicked()), this, SLOT(onBtMinization()));

	createSystemButton(btFullScreen, QIcon(":/QMetro/max"));
	connect(btFullScreen, SIGNAL(clicked()), this, SLOT(onBtFullScreen()));

	createSystemButton(btClose, QIcon(":/QMetro/close"));
	connect(btClose, SIGNAL(clicked()), this, SLOT(close()));

	

	hlSysLayout->setGeometry(QRect(0, 0, this->width(), 20));

}




QMetroMainWindow::~QMetroMainWindow()
{
}

void QMetroMainWindow::createTrayMenu()
{
	restoreWinAction = new QAction(QIcon(":/QMetro/ico"), tr("Open"), this);
	quitAction = new QAction("quit", this);

	connect(restoreWinAction, SIGNAL(triggered()), this, SLOT(showNormal()));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

	trayMenu = new QMenu((QWidget*)QApplication::desktop());

	trayMenu->addAction(restoreWinAction);
	trayMenu->addSeparator();
	trayMenu->addAction(quitAction);
}

void QMetroMainWindow::showNormal()
{
	this->show();
	this->activateWindow();
}

void QMetroMainWindow::onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason){
	case QSystemTrayIcon::Trigger:
		break;
	case QSystemTrayIcon::DoubleClick:
		showNormal();
		break;
	case QSystemTrayIcon::MiddleClick:
		break;
	default:
		break;
	}
}


void QMetroMainWindow::onBtMinization()
{
	if (!QSystemTrayIcon::isSystemTrayAvailable())
	{
		this->showMinimized();
		return;
	}
	else
	{
		trayIcon->showMessage(tr("MonitoringTool V1.0"), tr("Monitoring Tool is runing in the background!"),
			QSystemTrayIcon::Information, 10000);
		this->hide();
	}
}

