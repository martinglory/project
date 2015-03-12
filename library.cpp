#include "library.hpp"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsView>
#include <QTextEdit>
#include <QLineEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

GeoLib::GeoLib(QWidget* parent): QWidget(parent)
{
   layout = new QGridLayout();
   
   menuBar = new QMenuBar(this);
   
   fileMenu = menuBar->addMenu("&File");
   editMenu = menuBar->addMenu("Edit");
   helpMenu = menuBar->addMenu("Help");
   
   actNew = new QAction("&New", this);
   actSave = new QAction("&Save", this);
   actOpen = new QAction("&Open", this);
   actDelete = new QAction("&Delelte",this);
   actElements = new QAction("&Elements",this);
   actConfigure = new QAction("&Configure",this);
   actAbout = new QAction("&About",this);
   actUser = new QAction("&UserManual",this);
   
   fileMenu->addAction(actNew);
   fileMenu->addAction(actSave);
   fileMenu->addAction(actOpen);
   editMenu->addAction(actDelete);
   editMenu->addAction(actElements);
   editMenu->addAction(actConfigure);
   helpMenu->addAction(actAbout);
   helpMenu->addAction(actUser);
   
   label1 = new QLabel("Graphic");
   label2 = new QLabel("Data");
   label3 = new QLabel("Status Line");
   button1 = new QPushButton();
   button1->setIcon(QIcon("cycle.jpg"));
   button2 = new QPushButton();
   button2->setIcon(QIcon("Infinity.png"));
   button3 = new QPushButton();
   button3->setIcon(QIcon("realline.png"));
   graphical = new QGraphicsView();
   line = new QLineEdit();
   text = new QTextEdit();
   
   // connect(button1, SIGNAL(released()), this, SLOT(add_cycle_rel());

   layout->addWidget(label1,3,0,1,1);
   layout->addWidget(button1,2,0,1,1);
   layout->addWidget(graphical,4,0,3,4);
   layout->addWidget(text,4,4,3,4);
   layout->addWidget(button2,2,1,1,1);
   layout->addWidget(button3,2,2,1,1);
   layout->addWidget(label3,7,0,1,1);
   layout->addWidget(label2,3,3,1,3);
   layout->addWidget(line,7,1,1,6);
   setLayout(layout);
   setWindowTitle("Geometry Library");



}
// void GeoLib::add_cycle_rel(){}