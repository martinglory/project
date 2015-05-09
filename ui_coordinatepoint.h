/********************************************************************************
** Form generated from reading UI file 'coordinatepoint.ui'
**
** Created: Tue May 5 09:10:47 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COORDINATEPOINT_H
#define UI_COORDINATEPOINT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CoordinatePointClass
{
public:
    QWidget *centralWidget;
    QLabel *label_A;
    QLabel *label_B;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonplotCycle;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButtonClear;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QWidget *widgetC;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_C;
    QLabel *label_D;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CoordinatePointClass)
    {
        if (CoordinatePointClass->objectName().isEmpty())
        CoordinatePointClass->resize(987, 646);
        centralWidget = new QWidget(CoordinatePointClass);
        label_A = new QLabel(centralWidget);
        label_A->setGeometry(QRect(80, 570, 120, 12));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_A->sizePolicy().hasHeightForWidth());
        label_A->setSizePolicy(sizePolicy);
        label_A->setMinimumSize(QSize(120, 0));
        label_A->setMaximumSize(QSize(120, 16777215));
        label_B = new QLabel(centralWidget);
        label_B->setGeometry(QRect(260, 570, 120, 16));
        sizePolicy.setHeightForWidth(label_B->sizePolicy().hasHeightForWidth());
        label_B->setSizePolicy(sizePolicy);
        label_B->setMinimumSize(QSize(120, 0));
        label_B->setMaximumSize(QSize(120, 16777215));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setGeometry(QRect(81, 34, 793, 463));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        pushButtonplotCycle = new QPushButton(layoutWidget);

        horizontalLayout_4->addWidget(pushButtonplotCycle);

//        pushButton_2 = new QPushButton(layoutWidget);

        pushButton_3 = new QPushButton(layoutWidget);
        
        pushButtonClear = new QPushButton(layoutWidget);

        horizontalLayout_4->addWidget(pushButton_3);

        horizontalLayout_4->addWidget(pushButtonClear);

//        horizontalLayout_4->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(408, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        widgetC = new QWidget(layoutWidget);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetC->sizePolicy().hasHeightForWidth());
        widgetC->setSizePolicy(sizePolicy1);
        widgetC->setMinimumSize(QSize(400, 400));
        widgetC->setMaximumSize(QSize(400, 400));

        horizontalLayout->addWidget(widgetC);

        groupBox_2 = new QGroupBox(layoutWidget);
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        label_4 = new QLabel(groupBox_2);

        horizontalLayout_3->addWidget(label_4);


        horizontalLayout->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        label = new QLabel(layoutWidget);

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);

        horizontalLayout_2->addWidget(lineEdit);

        horizontalSpacer_2 = new QSpacerItem(548, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        label_C = new QLabel(centralWidget);
        label_C->setGeometry(QRect(450, 570, 120, 16));
        sizePolicy.setHeightForWidth(label_C->sizePolicy().hasHeightForWidth());
        label_C->setSizePolicy(sizePolicy);
        label_C->setMinimumSize(QSize(120, 0));
        label_C->setMaximumSize(QSize(120, 16777215));
        label_D = new QLabel(centralWidget);
        label_D->setGeometry(QRect(630, 570, 120, 16));
        sizePolicy.setHeightForWidth(label_D->sizePolicy().hasHeightForWidth());
        label_D->setSizePolicy(sizePolicy);
        label_D->setMinimumSize(QSize(120, 0));
        label_D->setMaximumSize(QSize(120, 16777215));
        CoordinatePointClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CoordinatePointClass);
        menuBar->setGeometry(QRect(0, 0, 987, 23));
        CoordinatePointClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CoordinatePointClass);
        CoordinatePointClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CoordinatePointClass);
        CoordinatePointClass->setStatusBar(statusBar);

        retranslateUi(CoordinatePointClass);

        QMetaObject::connectSlotsByName(CoordinatePointClass);
    } // setupUi

    void retranslateUi(QMainWindow *CoordinatePointClass)
    {
        CoordinatePointClass->setWindowTitle(QApplication::translate("CoordinatePointClass", "CoordinatePoint", 0, QApplication::UnicodeUTF8));
        label_A->setText(QApplication::translate("CoordinatePointClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_B->setText(QApplication::translate("CoordinatePointClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        pushButtonplotCycle->setText(QApplication::translate("CoordinatePointClass", "cycle", 0, QApplication::UnicodeUTF8));
//        pushButton_2->setText(QApplication::translate("CoordinatePointClass", "infinty", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("CoordinatePointClass", "parameters", 0, QApplication::UnicodeUTF8));
        pushButtonClear->setText(QApplication::translate("CoordinatePointClass", "clear", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CoordinatePointClass", "Data", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CoordinatePointClass", "", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CoordinatePointClass", "Current Position", 0, QApplication::UnicodeUTF8));
        label_C->setText(QApplication::translate("CoordinatePointClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_D->setText(QApplication::translate("CoordinatePointClass", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CoordinatePointClass: public Ui_CoordinatePointClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COORDINATEPOINT_H
