/********************************************************************************
** Form generated from reading UI file 'coordinatepoint.ui'
**
** Created: Wed Apr 29 23:33:21 2015
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
    QWidget *widget;
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
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CoordinatePointClass)
    {
        if (CoordinatePointClass->objectName().isEmpty())
            CoordinatePointClass->setObjectName(QString::fromUtf8("CoordinatePointClass"));
        CoordinatePointClass->resize(987, 646);
        centralWidget = new QWidget(CoordinatePointClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_A = new QLabel(centralWidget);
        label_A->setObjectName(QString::fromUtf8("label_A"));
        label_A->setGeometry(QRect(80, 570, 120, 12));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_A->sizePolicy().hasHeightForWidth());
        label_A->setSizePolicy(sizePolicy);
        label_A->setMinimumSize(QSize(120, 0));
        label_A->setMaximumSize(QSize(120, 16777215));
        label_B = new QLabel(centralWidget);
        label_B->setObjectName(QString::fromUtf8("label_B"));
        label_B->setGeometry(QRect(260, 570, 120, 16));
        sizePolicy.setHeightForWidth(label_B->sizePolicy().hasHeightForWidth());
        label_B->setSizePolicy(sizePolicy);
        label_B->setMinimumSize(QSize(120, 0));
        label_B->setMaximumSize(QSize(120, 16777215));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(81, 34, 793, 463));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButtonplotCycle = new QPushButton(widget);
        pushButtonplotCycle->setObjectName(QString::fromUtf8("pushButtonplotCycle"));

        horizontalLayout_4->addWidget(pushButtonplotCycle);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);

        pushButtonClear = new QPushButton(widget);
        pushButtonClear->setObjectName(QString::fromUtf8("pushButtonClear"));

        horizontalLayout_4->addWidget(pushButtonClear);

        horizontalSpacer = new QSpacerItem(408, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widgetC = new QWidget(widget);
        widgetC->setObjectName(QString::fromUtf8("widgetC"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetC->sizePolicy().hasHeightForWidth());
        widgetC->setSizePolicy(sizePolicy1);
        widgetC->setMinimumSize(QSize(400, 400));
        widgetC->setMaximumSize(QSize(400, 400));

        horizontalLayout->addWidget(widgetC);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);


        horizontalLayout->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        horizontalSpacer_2 = new QSpacerItem(548, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        CoordinatePointClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CoordinatePointClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 987, 23));
        CoordinatePointClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CoordinatePointClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CoordinatePointClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CoordinatePointClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
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
        pushButton_2->setText(QApplication::translate("CoordinatePointClass", "infinty", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("CoordinatePointClass", "parameters", 0, QApplication::UnicodeUTF8));
        pushButtonClear->setText(QApplication::translate("CoordinatePointClass", "clear", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CoordinatePointClass", "Data", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CoordinatePointClass", "hello", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CoordinatePointClass", "Current Position", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CoordinatePointClass: public Ui_CoordinatePointClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COORDINATEPOINT_H
