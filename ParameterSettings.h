#ifndef PARAMETERSETTINGS_H
#define PARAMETERSETTINGS_H

#include <QtGui/QDialog>
#include "ui_ParameterSettings.h"
#include "enum.h"

class ParameterSettings : public QDialog
{
	Q_OBJECT

public:
	ParameterSettings();
	~ParameterSettings();

	void getPara(Apara &apara,Bpara &bpara,Rpara &rpara,Ipara &ipara);

public slots:
	void slotCloseParaWidget();

private:
	Ui::Form ui;
};
#endif