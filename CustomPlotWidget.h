#ifndef CUSTOMPLOTWIDGET_H
#define CUSTOMPLOTWIDGET_H

#include <QObject>
#include "qcustomplot.h"

class CustomPlotWidget : public QCustomPlot
{
	Q_OBJECT
public:
	CustomPlotWidget();
	~CustomPlotWidget();


	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);

	void setStatusOfPoint();


private:
	bool m_pointA;
	bool m_pointB;
    bool m_pointC;
    bool m_pointD;


signals:
	void signalCurrentPos(int x,int y);
	void signalPointACreated(int x,int y);
	void signalPointBCreated(int x,int y);
    void signalPointCCreated(int x, int y);
    void signalPointDCreated(int x, int y);


};
#endif