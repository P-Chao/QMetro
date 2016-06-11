#include "qmetro.h"

QMetro::QMetro(QWidget *parent)
	: QMainWindow(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint);
	isLeftPressDown = false;
	hlSysLayout = new QHBoxLayout;
	hlSysLayout->addStretch(1000);
}

QMetro::~QMetro()
{

}

void QMetro::mousePressEvent(QMouseEvent *event)
{
	if (!isFullScreen())
	{
		switch (event->button()) {
		case Qt::LeftButton:
			isLeftPressDown = true;
			dragPosition = event->globalPos() - this->frameGeometry().topLeft();
			break;
		default:
			break;
		}
	}
}

void QMetro::mouseMoveEvent(QMouseEvent *event)
{
	if (!isFullScreen())
	{
		QPoint gloPoint = event->globalPos();
		QRect rect = this->rect();
		QPoint tl = mapToGlobal(rect.topLeft());
		QPoint rb = mapToGlobal(rect.bottomRight());

		if (!isLeftPressDown) {
			//this->region(gloPoint);
		}
		else {
				move(event->globalPos() - dragPosition);
				event->accept();
		}
	}

}

void QMetro::mouseReleaseEvent(QMouseEvent *event)
{
	if (!isFullScreen())
	{
		if (event->button() == Qt::LeftButton) {
			isLeftPressDown = false;
			{
				this->releaseMouse();
				this->setCursor(QCursor(Qt::ArrowCursor));
			}
		}
	}
}

void QMetro::createSystemButton(QPushButton* (&pushbutton), QIcon ico)
{
	pushbutton = new QPushButton(this);
	pushbutton->setFlat(true);
	pushbutton->setMaximumSize(20, 20);
	pushbutton->setMinimumSize(20, 20);
	pushbutton->setIcon(ico);
	hlSysLayout->addWidget(pushbutton);
	hlSysLayout->addStretch(1);
	pushbutton->raise();
}