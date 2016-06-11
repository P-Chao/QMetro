#include "QMetroWindow.h"


QMetroWindow::QMetroWindow()
{
	this->setMinimumSize(60, 20);
	this->resize(QSize(100, 100));
	this->setMouseTracking(true);
	isLeftPressDown = false;
}


QMetroWindow::~QMetroWindow()
{
}


void QMetroWindow::mousePressEvent(QMouseEvent *event)
{
	if (!isFullScreen())
	{
		switch (event->button()) {
		case Qt::LeftButton:
			isLeftPressDown = true;
			if (dir != NONE) {
				this->mouseGrabber();
			}
			else {
				dragPosition = event->globalPos() - this->frameGeometry().topLeft();
			}
			break;
		default:
			break;
		}
	}
	return;
}

void QMetroWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (!isFullScreen())
	{
		QPoint gloPoint = event->globalPos();
		QRect rect = this->rect();
		QPoint tl = mapToGlobal(rect.topLeft());
		QPoint rb = mapToGlobal(rect.bottomRight());

		if (!isLeftPressDown) {
			this->region(gloPoint);
		}
		else {
			if (dir != NONE) {
				QRect rMove(tl, rb);

				switch (dir) {
				case LEFT:
					if (rb.x() - gloPoint.x() <= this->minimumWidth())
						rMove.setX(tl.x());
					else
						rMove.setX(gloPoint.x());
					break;
				case RIGHT:
					rMove.setWidth(gloPoint.x() - tl.x());
					break;
				case UP:
					if (rb.y() - gloPoint.y() <= this->minimumHeight())
						rMove.setY(tl.y());
					else
						rMove.setY(gloPoint.y());
					break;
				case DOWN:
					rMove.setHeight(gloPoint.y() - tl.y());
					break;
				case LEFTTOP:
					if (rb.x() - gloPoint.x() <= this->minimumWidth())
						rMove.setX(tl.x());
					else
						rMove.setX(gloPoint.x());
					if (rb.y() - gloPoint.y() <= this->minimumHeight())
						rMove.setY(tl.y());
					else
						rMove.setY(gloPoint.y());
					break;
				case RIGHTTOP:
					rMove.setWidth(gloPoint.x() - tl.x());
					if (rb.y() - gloPoint.y() <= this->minimumHeight())
						rMove.setY(tl.y());
					else
						rMove.setY(gloPoint.y());
					break;
				case LEFTBOTTOM:
					rMove.setHeight(gloPoint.y() - tl.y());
					if (rb.x() - gloPoint.x() <= this->minimumWidth())
						rMove.setX(tl.x());
					else
						rMove.setX(gloPoint.x());
					break;
				case RIGHTBOTTOM:
					rMove.setWidth(gloPoint.x() - tl.x());
					rMove.setHeight(gloPoint.y() - tl.y());
					break;
				default:
					break;
				}
				this->setGeometry(rMove);
				hlSysLayout->setGeometry(QRect(this->width() - 60, 0, 60, 20));
			}
			else {
				move(event->globalPos() - dragPosition);
				event->accept();
			}
		}
	}
	return;

}

void QMetroWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if (!isFullScreen())
	{
		if (event->button() == Qt::LeftButton) {
			isLeftPressDown = false;
			if (dir != NONE) {
				this->releaseMouse();
				this->setCursor(QCursor(Qt::ArrowCursor));
			}
		}
	}
	return;
}

#ifndef PADDING
#define PADDING 2 //�����ڱ߿��ϵ��ƶ����ı��С�ķ�Χ
#endif
void QMetroWindow::region(const QPoint &cursorGlobalPoint)
{
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	int x = cursorGlobalPoint.x();
	int y = cursorGlobalPoint.y();

	if (tl.x() + PADDING >= x && tl.x() - PADDING <= x && tl.y() + PADDING >= y && tl.y() - PADDING <= y) {
		// ���Ͻ�
		dir = LEFTTOP;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));  // ���������״
	}
	else if (x >= rb.x() - PADDING && x <= rb.x() + PADDING && y >= rb.y() - PADDING && y <= rb.y() + PADDING) {
		// ���½�
		dir = RIGHTBOTTOM;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x() - PADDING && y >= rb.y() - PADDING && y <= rb.y() + PADDING) {
		//���½�
		dir = LEFTBOTTOM;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= rb.x() + PADDING && x >= rb.x() - PADDING && y >= tl.y() - PADDING && y <= tl.y() + PADDING) {
		// ���Ͻ�
		dir = RIGHTTOP;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x() - PADDING) {
		// ���
		dir = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (x <= rb.x() + PADDING && x >= rb.x() - PADDING) {
		// �ұ�
		dir = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (y >= tl.y() - PADDING && y <= tl.y() + PADDING){
		// �ϱ�
		dir = UP;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if (y <= rb.y() + PADDING && y >= rb.y() - PADDING) {
		// �±�
		dir = DOWN;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else {
		// Ĭ��
		dir = NONE;
		this->setCursor(QCursor(Qt::ArrowCursor));
	}

}

void QMetroWindow::onBtMinization()
{
	this->showMinimized();
	return;
}

void QMetroWindow::onBtFullScreen()
{
	if (this->isFullScreen())
	{
		this->setGeometry(fullScreenPosition);

		QPixmap image_full(":/QMetro/max");
		btFullScreen->setIcon(image_full);

		hlSysLayout->setGeometry(QRect(0, 0, this->width(), 20));
	}
	else
	{
		QPoint temp_point = this->pos();
		fullScreenPosition = this->rect();

		fullScreenPosition.moveTo(temp_point);

		this->showFullScreen();
		hlSysLayout->setGeometry(QRect(0, 0, this->width(), 20));

		QPixmap image_norm(":/QMetro/restore");
		btFullScreen->setIcon(image_norm);
	}
}