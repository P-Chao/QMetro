#pragma once
#include "qmetro.h"
class QMetroWindow :
	public QMetro
{
	Q_OBJECT

public:
	QMetroWindow();
	~QMetroWindow();

protected:
	// Êó±êÊÂ¼þ
	enum Direction{
		UP = 0,
		DOWN = 1,
		LEFT,
		RIGHT,
		LEFTTOP,
		LEFTBOTTOM,
		RIGHTBOTTOM,
		RIGHTTOP,
		NONE
	};
	Direction dir;
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void region(const QPoint &cursorGlobalPoint);

	QRect fullScreenPosition;

protected slots:
	void onBtFullScreen();
	void onBtMinization();
};

