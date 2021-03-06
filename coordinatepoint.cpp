#include "coordinatepoint.h"
#include <QHBoxLayout>
#include <QVector>
#include <iostream>
#include <fstream>
#include "figure.h"
#include <QTextStream>
#include<QMessageBox>
#include<QFile>
#include<exception>
using namespace std;
using std::exception;

CoordinatePoint::CoordinatePoint(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
,m_pos(0)
{
    F = new figure();
	ui.setupUi(this);

	ui.label_A->setHidden(true);
	ui.label_B->setHidden(true);
    ui.label_C->setHidden(true);
    ui.label_D->setHidden(true);

	ui.widgetC->setObjectName("cycle");
	custom = new CustomPlotWidget;
	QHBoxLayout *sliceHorizontalLayout = new QHBoxLayout(ui.widgetC);
	sliceHorizontalLayout->addWidget(custom);

	custom->xAxis->setRange(-10,10);
	custom->yAxis->setRange(-10,10);

	custom->xAxis->setLabel("X");
	custom->yAxis->setLabel("Y");

	custom->axisRect()->setupFullAxesBox(true);

	m_view = custom->viewport().size();
	m_axis = custom->axisRect()->size();

	connect(custom,SIGNAL(signalCurrentPos(int,int)),this,SLOT(slotShowCurrentPos(int,int)));
	connect(custom,SIGNAL(signalPointACreated(int,int)),this,SLOT(slotShowPointA(int,int)));
	connect(custom,SIGNAL(signalPointBCreated(int,int)),this,SLOT(slotShowPointB(int,int)));
    connect(custom,SIGNAL(signalPointCCreated(int,int)),this,SLOT(slotShowPointC(int,int)));
    connect(custom,SIGNAL(signalPointDCreated(int,int)),this,SLOT(slotShowPointD(int,int)));

	connect(ui.pushButton_3,SIGNAL(clicked()),this,SLOT(slotParaShow()));
	connect(ui.pushButtonplotCycle,SIGNAL(clicked()),this,SLOT(slotShowHello()));
//	connect(ui.pushButton_2,SIGNAL(clicked()),this,SLOT(slotShowU()));
	connect(ui.pushButtonClear,SIGNAL(clicked()),this,SLOT(slotClear()));

}

CoordinatePoint::~CoordinatePoint()
{
if(m_pos)
{
    delete [] m_pos;
    m_pos = NULL;
}
}

void CoordinatePoint::slotClear()
{
custom->clearGraphs();
custom->replot();
custom->setStatusOfPoint();

ui.label_A->setHidden(true);
ui.label_B->setHidden(true);
ui.label_C->setHidden(true);
ui.label_D->setHidden(true);

}// slot clear button
void CoordinatePoint::slotShowU()
{
	//F->get_real_line();
}

void CoordinatePoint::slotShowHello()
{

	ex A=F->add_point(Ax,Ay,"A");

	ex B=F->add_point(Bx,By,"B");
    
    ex C=F->add_point(Cx,Cy,"C");
    
    ex D=F->add_point(Dx,Dy,"D");
    
    
    
    
    
    getParas();

    lst l;
    if(m_paraA.para1)
    l.append(is_orthogonal(A));
    if(m_paraA.para2)
    	l.append(is_different(A));
    if(m_paraA.para3)
        l.append(is_tangent(A));
    if(m_paraA.para4)
    	l.append(is_f_orthogonal(A));
    if(m_paraB.para1)
    	l.append(is_orthogonal(B));
    if(m_paraB.para2)
    	l.append(is_different(B));
    if(m_paraB.para3)
    	l.append(is_tangent(B));
    if(m_paraB.para4)
    	l.append(is_f_orthogonal(B));
    if(m_paraC.para1)
        l.append(is_orthogonal(C));
    if(m_paraC.para2)
        l.append(is_different(C));
    if(m_paraC.para3)
        l.append(is_tangent(C));
    if(m_paraC.para4)
        l.append(is_f_orthogonal(C));
    
    if(m_paraD.para1)
        l.append(is_orthogonal(D));
    if(m_paraD.para2)
        l.append(is_different(D));
    if(m_paraD.para3)
        l.append(is_tangent(D));
    if(m_paraD.para4)
        l.append(is_f_orthogonal(D));
    if(m_paraR.para1)
    	l.append(is_orthogonal(F->get_real_line()));
    if(m_paraR.para2)
    	l.append(is_different(F->get_real_line()));
    if(m_paraR.para3)
    	l.append(is_tangent(F->get_real_line()));
    if(m_paraR.para4)
    	l.append(is_f_orthogonal(F->get_real_line()));
    if(m_paraI.para1)
    	l.append(is_orthogonal(F->get_infinity()));
    if(m_paraI.para2)
    	l.append(is_different(F->get_infinity()));
    if(m_paraI.para3)
    	l.append(is_tangent(F->get_infinity()));
    if(m_paraI.para4)
    	l.append(is_f_orthogonal(F->get_infinity()));
    if(!m_paraA.para1&&
       !m_paraA.para2&&
       !m_paraA.para3&&
       !m_paraA.para4&&
       !m_paraB.para1&&
       !m_paraB.para2&&
       !m_paraB.para3&&
       !m_paraB.para4&&
       !m_paraC.para1&&
       !m_paraC.para2&&
       !m_paraC.para3&&
       !m_paraC.para4
       )
    {
        QMessageBox::warning(NULL,"error","Parameters have not been set!",
                             QMessageBox::Ok);
        return;
    }
    ex a=F->add_cycle_rel(l,"a");// add parameter into cycle

    

	ex L=F->get_cycles(a);

	for (lst::const_iterator it =ex_to<lst>(L).begin(); it != ex_to<lst>(L).end(); ++it) 
	{
        cycle2D C=ex_to<cycle2D>(*it);
        
        
        if (C.radius_sq().is_zero()) {
            
            cout << "It is a point " << C.center() << endl;
            
        }//point of cycle
        else if (C.get_k().is_zero()) {
            
            cout << "It is a line with the equation ("
            
            << ex_to<numeric>(C.get_l(0).evalf()).to_double() << ")*x + ("
            
            << ex_to<numeric>(C.get_l(1).evalf()).to_double() << ")*y = "
            
            << ex_to<numeric>((C.get_m()/2).evalf()).to_double() << endl;
            
        }//line of  cycle
        else {
            
            
            
            cout << "It is a circle with the centre is: " << C.center() << endl; // This is again a list, see below
            
            cout << "(centre's first coordinate: " << ex_to<numeric>(C.center().op(0)).to_double()
            
            << ", second coordinate: " << ex_to<numeric>(C.center().op(1)).to_double()
            
            << ")" << endl; 
            
            cout << "Square of the radius is: " << ex_to<numeric>(C.radius_sq()).to_double() << endl;
            
            
        }// circle of cycle
        
        fstream wri;
        wri.open("./para.txt",ios::out);
        wri<<C.center().op(0)<<" "<<C.center().op(1)<<" "<<C.radius_sq()<<" "<<C.radius_sq().is_zero()<<" "<<C.get_k().is_zero()<<" "<<(C.get_m()/2).evalf() <<" "<<C.center() <<" "<< C.get_l(0).evalf()<<" "<<C.get_l(1).evalf()<< endl;
        if(ex_to<numeric>(C.radius_sq()).to_double() < 0){
            QMessageBox::warning(NULL,"error","Parameters have not been set!",
                                 QMessageBox::Ok);}
	}

    float para[9] = {0};
    ifstream rea("./para.txt");
    for(int i=0;i<9;i++)
    {
        rea>>para[i];
    }
    
    center_x = para[0];
    center_y = para[1];
    m_radius = qSqrt(para[2]);
    m_point = para[3];
    m_line = para[4];
    line = para[5];
    point = para[6];
    what = para[7];
    why = para[8];

    

    if (m_point)
    {
        QMessageBox::warning(NULL, "error","The radius of the cycle is improper!",
                             QMessageBox::Ok);

        QFile fileRead("./outpoint");
        bool isop = fileRead.open(QIODevice::ReadOnly|QFile::Text);
        QTextStream in(&fileRead);
        QString str = "";
        while(!in.atEnd())
        {
            str+=in.readLine();
        }

        fileRead.flush();
        fileRead.close();

        QFile fileReadc("./outcenter");
        fileReadc.open(QIODevice::ReadOnly|QFile::Text);
        QTextStream inc(&fileReadc);
        QString strc = "";
        while(!inc.atEnd())
        {
            strc+=inc.readLine();
        }

        fileReadc.flush();
        fileReadc.close();

        QString  string = str+"\n"+strc+"\n";
        ui.label_4->adjustSize();
        ui.label_4->setWordWrap(true);

        ui.label_4->setText(string + QString("It is a point = {%1,%2}").arg(point).arg(point));

        QVector<double> px0(1),py0(1);
        for (int i=0; i<1; i++) {
            px0[i] = point;
            py0[i] = point;
        }
        custom->addGraph();
        custom->graph()->setData(px0,py0);
        custom->replot();

    }//draw point

    else if(m_line)
    {
        QFile fileRead("./outpoint");
        bool isop = fileRead.open(QIODevice::ReadOnly|QFile::Text);
        QTextStream in(&fileRead);
        QString str = "";
        while(!in.atEnd())
        {
            str+=in.readLine();
        }

        fileRead.flush();
        fileRead.close();

        QFile fileReadc("./outline");
        fileReadc.open(QIODevice::ReadOnly|QFile::Text);
        QTextStream inc(&fileReadc);
        QString strc = "";
        while(!inc.atEnd())
        {
            strc+=inc.readLine();
        }

        fileReadc.flush();
        fileReadc.close();

        QString  string = str+"\n"+strc+"\n";
        ui.label_4->adjustSize();
        ui.label_4->setWordWrap(true);

        ui.label_4->setText(string + QString("The Line with the equation; %1*x+%2*y = %3 ").arg(center_x).arg(center_y).arg(line));

        QVector<double> px(2),py(2);
        for (int i=0;i<2; i++)
        {
            if (center_x == 0) {
                px[0] = 10;
                py[0] = line/center_y;
                px[1] = -10;
                py[1] = line/center_y;
            }
            else if(center_y == 0)
            {
                px[0] =  line/center_x;
                py[0] = 10;
                px[1] =  line/center_x;
                py[1] = -10;
            }
            else{
            px[0] = 10;
            py[0] = (line - 10*center_x)/center_y ;
            px[1] = -10;
            py[1] = (line + 10*center_x)/center_y;
            }
        }
        custom->addGraph();
        custom->graph()->setData(px,py);
        custom->replot();
    }// draw line

    else{
        QFile fileRead("./outpoint");
        bool isop = fileRead.open(QIODevice::ReadOnly|QFile::Text);
        QTextStream in(&fileRead);
        QString str = "";
        while(!in.atEnd())
        {
            str+=in.readLine();
        }

        fileRead.flush();
        fileRead.close();

        QFile fileReadc("./outcycle");
        fileReadc.open(QIODevice::ReadOnly|QFile::Text);
        QTextStream inc(&fileReadc);
        QString strc = "";
        while(!inc.atEnd())
        {
            strc+=inc.readLine();
        }

        fileReadc.flush();
        fileReadc.close();

        QString  string = str+"\n"+strc+"\n";
        ui.label_4->adjustSize();
        ui.label_4->setWordWrap(true);

        ui.label_4->setText(string + QString("center of circle=(%1,%2)\nradius of circle=%3").arg(center_x).arg(center_y).arg(m_radius));

        QVector<double> px(180),py(180);
        for (int i=0;i<180;i++)
        {
            px[i] = m_radius*cos((double)i*PI/180) + center_x;
            py[i] = m_radius*sin((double)i*PI/180) + center_y;
        }
        custom->addGraph();
        custom->graph()->setData(px,py);
        custom->replot();




        QVector<double> px1(180),py1(180);
        for (int i=180;i<360;i++)
        {
            px1[i-180] = m_radius*cos((double)i*PI/180) + center_x;
            py1[i-180] = m_radius*sin((double)i*PI/180) + center_y;
        }
        custom->addGraph();
        custom->graph()->setData(px1,py1);
        custom->replot();
    }//draw circle
}

void CoordinatePoint::slotShowCurrentPos(int x,int y)
{
	float pos_x = getPosFromPixel(x,y)[0];
	float pos_y = getPosFromPixel(x,y)[1];
		
	ui.lineEdit->setText(QString("%1,%2").arg(pos_x,0,'f',2).arg(pos_y,0,'f',2));
}// display mouse position

void CoordinatePoint::slotShowPointA(int x,int y)
{
	float pos_x = getPosFromPixel(x,y)[0];
	float pos_y = getPosFromPixel(x,y)[1];

	ui.label_A->setHidden(false);
	ui.label_A->setText(QString("A(%1,%2)").arg(pos_x,0,'f',2).arg(pos_y,0,'f',2));
	ui.label_A->move(x+80,y+80);
    ui.label_A->raise();
	plotPoint(pos_x,pos_y);

	Ax = pos_x;
	Ay = pos_y;

	custom->replot();
}// create point A

void CoordinatePoint::slotShowPointB(int x,int y)
{

	float pos_x = getPosFromPixel(x,y)[0];
	float pos_y = getPosFromPixel(x,y)[1];

	ui.label_B->setHidden(false);
	ui.label_B->setText(QString("B(%1,%2)").arg(pos_x,0,'f',2).arg(pos_y,0,'f',2));
	ui.label_B->move(x+80,y+80);
	ui.label_B->raise();

	plotPoint(pos_x,pos_y);

	Bx = pos_x;
	By = pos_y;

	custom->replot();
}//create point B
void CoordinatePoint::slotShowPointC(int x,int y)
{
    
    float pos_x = getPosFromPixel(x,y)[0];
    float pos_y = getPosFromPixel(x,y)[1];
    
    ui.label_C->setHidden(false);
    ui.label_C->setText(QString("C(%1,%2)").arg(pos_x,0,'f',2).arg(pos_y,0,'f',2));
    ui.label_C->move(x+80,y+80);
    ui.label_C->raise();
    
    plotPoint(pos_x,pos_y);
    
    Cx = pos_x;
    Cy = pos_y;
    
    custom->replot();
}//create point C
void CoordinatePoint::slotShowPointD(int x,int y)
{
    
    float pos_x = getPosFromPixel(x,y)[0];
    float pos_y = getPosFromPixel(x,y)[1];
    
    ui.label_D->setHidden(false);
    ui.label_D->setText(QString("D(%1,%2)").arg(pos_x,0,'f',2).arg(pos_y,0,'f',2));
    ui.label_D->move(x+80,y+80);
    ui.label_D->raise();
    
    plotPoint(pos_x,pos_y);
    
    Dx = pos_x;
    Dy = pos_y;
    
    custom->replot();
}//create point D

void CoordinatePoint::plotPoint(float x,float y)
{
	QVector<double> px(1),py(1);
	for (int i=0;i<1;i++)
	{
		px[i] = x;
		py[i] = y;
	}
	custom->addGraph();
	custom->graph()->setData(px,py);
	custom->graph()->setPen(QPen(Qt::blue));
	custom->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc));

	custom->replot();
}// draw points

float *CoordinatePoint::getPosFromPixel(int x,int y)
{
	if(m_pos)
    {delete [] m_pos;
        m_pos = NULL;}
    m_pos = new float[2];
	float pos_x =  x - (m_view.width()-m_axis.width())/2;
	float pos_y = y - (m_view.height()-m_axis.height())/2;

	m_pos[0] = -10 + pos_x*20/363.0;
	m_pos[1] =  10 - pos_y*20/353.0;

	return m_pos;
}// define scope of coordinate system

void CoordinatePoint::slotParaShow()
{
	para = new ParameterSettings;
	para->exec();
}//slot parameter


void CoordinatePoint::getParas()
{
    para->getPara(m_paraA,m_paraB,m_paraC,m_paraD,m_paraR,m_paraI);
}// get parameters


