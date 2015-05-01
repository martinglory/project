#include "CustomPlotWidget.h"

CustomPlotWidget::CustomPlotWidget()
:m_pointA(false)
,m_pointB(false)
{

}

CustomPlotWidget::~CustomPlotWidget()
{

}

//����AB���״̬
void CustomPlotWidget::setStatusOfPoint()
{
	m_pointA = false;
	m_pointB = false;
}

//����ƶ���ʾ����
void CustomPlotWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint point = event->pos();
	emit signalCurrentPos(point.x(),point.y());
}

//������������A��B��
void CustomPlotWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->buttons()&Qt::LeftButton&&!m_pointA&&!m_pointB)
	{
		QPoint point = event->pos();
		m_pointA = true;
		emit signalPointACreated(point.x(),point.y());
		return;
	}

	if(event->buttons()&Qt::LeftButton&&m_pointA&&!m_pointB)
	{
		QPoint point = event->pos();
		emit signalPointBCreated(point.x(),point.y());
		m_pointB = true;
		return;
	}
}