#include "CustomPlotWidget.h"

CustomPlotWidget::CustomPlotWidget()
:m_pointA(false)
,m_pointB(false)
,m_pointC(false)
,m_pointD(false)
{

}

CustomPlotWidget::~CustomPlotWidget()
{

}

void CustomPlotWidget::setStatusOfPoint()
{
	m_pointA = false;
	m_pointB = false;
    m_pointC = false;
    m_pointD = false;

}

void CustomPlotWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint point = event->pos();
	emit signalCurrentPos(point.x(),point.y());
}

void CustomPlotWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton&&!m_pointA&&!m_pointB&&!m_pointC&&!m_pointD)
    {
        QPoint point = event->pos();
        m_pointA = true;
        emit signalPointACreated(point.x(),point.y());
        return;
    }
    
    if(event->buttons()&Qt::LeftButton&&m_pointA&&!m_pointB&&!m_pointC&&!m_pointD)
    {
        QPoint point = event->pos();
        emit signalPointBCreated(point.x(),point.y());
        m_pointB = true;
        return;
    }
    if (event->buttons()&Qt::LeftButton&&m_pointA&&m_pointB&&!m_pointC&&!m_pointD)
    {
        QPoint point = event->pos();
        emit signalPointCCreated(point.x(),point.y());
        m_pointC = true;
        return;
    }
    if (event->buttons()&Qt::LeftButton&&m_pointA&&m_pointB&&m_pointC&&!m_pointD)
    {
        QPoint point = event->pos();
        emit signalPointDCreated(point.x(),point.y());
        m_pointD = true;
        return;
    }

}