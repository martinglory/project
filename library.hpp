#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QWidget>

class QPushButton;
class QLabel;
class QLineEdit;
class QGridLayout;
class QGraphicsView;
class QTextEdit;
class QMenuBar;
class QMenu;
class QAction;

class GeoLib: public QWidget
{
  public:
    GeoLib(QWidget* parent=0);
  
  private slots:
    
    //void newFile();
    //void open();
    //void save();
    //void delete();
    //void elements();
    //void configure();
    //void about();
    //void actUser(); 
    
    //void add_cycle_rel();
  private:
    
    //void createActions;
    //void createMenus;
    
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QAction *actNew;
    QAction *actSave;
    QAction *actOpen;
    QAction *actDelete;
    QAction *actElements;
    QAction *actConfigure;
    QAction *actAbout;
    QAction *actUser;
        
    QGridLayout* layout;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QGraphicsView *graphical;
    QLineEdit *line;
    QTextEdit *text;


};

#endif
