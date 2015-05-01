#include "ParameterSettings.h"

ParameterSettings::ParameterSettings()
{
	ui.setupUi(this);
	connect(ui.pushButtonSure,SIGNAL(clicked()),this,SLOT(slotCloseParaWidget()));
}

ParameterSettings::~ParameterSettings()
{

}

void ParameterSettings::slotCloseParaWidget()
{
	this->close();
}
//获取参数设置值
void ParameterSettings::getPara(Apara &apara,Bpara &bpara,Rpara &rpara,Ipara &ipara)
{
	apara.para1= ui.checkBox_5->isChecked();
	apara.para2= ui.checkBox_6->isChecked();
	apara.para3= ui.checkBox_7->isChecked();
	apara.para4= ui.checkBox_8->isChecked();
	bpara.para1= ui.checkBox->isChecked();
	bpara.para2= ui.checkBox_2->isChecked();
	bpara.para3= ui.checkBox_3->isChecked();
	bpara.para4= ui.checkBox_4->isChecked();
	rpara.para1= ui.checkBox_9->isChecked();
	rpara.para2= ui.checkBox_10->isChecked();
	rpara.para3= ui.checkBox_11->isChecked();
	rpara.para4= ui.checkBox_12->isChecked();
	ipara.para1= ui.checkBox_13->isChecked();
	ipara.para2= ui.checkBox_14->isChecked();
	ipara.para3= ui.checkBox_15->isChecked();
	ipara.para4= ui.checkBox_16->isChecked();
}

