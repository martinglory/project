#include "CustomPlotWidget.h"

CustomPlotWidget::CustomPlotWidget()
:m_pointA(false)
,m_pointB(false)
{

}

CustomPlotWidget::~CustomPlotWidget()
{

}

//设置AB点的状态
void CustomPlotWidget::setStatusOfPoint()
{
	m_pointA = false;
	m_pointB = false;
}

//鼠标移动显示坐标
void CustomPlotWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint point = event->pos();
	emit signalCurrentPos(point.x(),point.y());
}

//鼠标左键点击获得A，B点
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