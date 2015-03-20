#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGraphicsView>
#include <QTextEdit>
#include <QIcon>
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QMainWindow>
#include "figure.h"

class myGraphics: public QGraphicsScene
{
    QMessageBox *msgBox;
public:
    myGraphics()
    {};
    ~ myGraphics(){};
    void mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        if(event->button() == Qt::LeftButton)
        {
            msgBox = new QMessageBox();
            msgBox->setWindowTitle("Hello");
            msgBox->setText("You Clicked Left Mouse Button");
            msgBox->show();
        }
        
        
    };
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
    {
        if(event->button() == Qt::RightButton)
        {
            msgBox = new QMessageBox();
            msgBox->setWindowTitle("Hello");
            msgBox->setText("You Clicked Right Mouse Button");
            msgBox->show();
        }
        
    };
    
};
int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  
  QWidget* window = new QWidget();
  
//  Menulib* menu = new Menulib();
  
  window->setWindowTitle("QHBoxLayout Test");
  
 
  QMenuBar* menubar = new QMenuBar();
  QMenu* fileMenu = new QMenu("File");
  QMenu* editMenu = new QMenu("Edit");
  QMenu* helpMenu = new QMenu("Help");

  menubar->addMenu(fileMenu);
  menubar->addMenu(editMenu);
  menubar->addMenu(helpMenu);

  
  fileMenu->addAction("New");
  fileMenu->addAction("Save");
  fileMenu->addAction("Open");
  editMenu->addAction("Delete");
  editMenu->addAction("Element");
  editMenu->addAction("Configure");
  helpMenu->addAction("About");
  helpMenu->addAction("UserManual");

  QTextEdit *text = new QTextEdit();
  QLabel* label1 = new QLabel("Status Line");
  QLabel* label2 = new QLabel("graphic");
  QLabel* label3 = new QLabel("data");

  QPushButton *button1 = new QPushButton();
  button1->setIcon(QIcon("/Users/Martin/Desktop/library/cycle.jpg"));

  QPushButton *button2 = new QPushButton();
  button2 ->setIcon(QIcon("/Users/Martin/Desktop/library/Infinity.png"));

  QPushButton *button3 = new QPushButton();
  button3 ->setIcon(QIcon("/Users/Martin/Desktop/library/realline.png"));

  QLineEdit *line = new QLineEdit();

  QGraphicsView *graphical = new QGraphicsView();

  myGraphics* scene = new myGraphics();
  graphical->setScene(scene);
    
  QBrush redBrush(Qt::red);
  QBrush blueBrush(Qt::blue);
  QPen blackpen(Qt::black);
  blackpen.setWidth(6);
    
  QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem();
  ellipse = scene->addEllipse(10,10,100,100,blackpen,redBrush);
  ellipse->setFlag(QGraphicsItem::ItemIsMovable);
  
 
  QGridLayout *layout = new QGridLayout();

  layout->addWidget(graphical,2,0,2,3);
  layout->addWidget(text,2,3,2,3);
  layout->addWidget(button1,0,0,1,1);
  layout->addWidget(button2,0,1,1,1);
  layout->addWidget(button3,0,2,1,1);
  layout->addWidget(label1,4,0,1,1);
  layout->addWidget(line,4,1,1,6);
  layout->addWidget(label2,1,0,1,1);
  layout->addWidget(label3,1,3,1,3);
  window->setLayout(layout);
  window->show();

  return app.exec();
}

