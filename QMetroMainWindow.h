#pragma once
#include "QMetroWindow.h"
class QMetroMainWindow :
	public QMetroWindow
{
	Q_OBJECT

public:
	QMetroMainWindow();
	~QMetroMainWindow();

protected:
	QSystemTrayIcon *trayIcon;
	QMenu *trayMenu;
	QAction *restoreWinAction;
	QAction *quitAction;
	void createTrayMenu();

protected slots:
	void onBtMinization();
	void showNormal();
	void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
	
};
