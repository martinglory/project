#ifndef COORDINATEPOINT_H
#define COORDINATEPOINT_H

#include <QtGui/QMainWindow>
#include "ui_coordinatepoint.h"
#include "CustomPlotWidget.h"
#include "ParameterSettings.h"
class figure;
#define  PI  3.1415927


class CoordinatePoint : public QMainWindow
{
	Q_OBJECT

public:
	CoordinatePoint(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CoordinatePoint();

	void plotPoint(float x,float y);
	float *getPosFromPixel(int x,int y);
	void getParas();
	

    public slots:
		void slotClear();
		void slotShowU();
	void slotShowHello();
	void slotShowCurrentPos(int x,int y);
	void slotShowPointA(int x,int y);
	void slotShowPointB(int x,int y);
	void slotParaShow();

private:
	Ui::CoordinatePointClass ui;
	CustomPlotWidget *custom;
	QSize m_view;
	QSize m_axis;
	ParameterSettings *para;
	Apara m_paraA;
	Bpara m_paraB;
    Rpara m_paraR;
    Ipara m_paraI;
    
	float center_x;
	float center_y;
	float m_radius;
	float Ax;
	float Ay;
	float Bx;
	float By;
    float *m_pos;
    figure* F;

};

#endif // COORDINATEPOINT_H
