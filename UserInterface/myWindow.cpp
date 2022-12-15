#include "myWindow.h"
#include "./../transferStruct.h"
#include <stdio.h>
#include <unistd.h>

struct transferStruct strus={
	.direction=0,
	.motor_address=2,
	.speed=0,
};

myWindow::myWindow()
{

	wdg = new QWidget(this);
	comboBox_m1=new QComboBox();
	comboBox_m2=new QComboBox();
	checkBox_m1=new QCheckBox();
	checkBox_m2=new QCheckBox();
	painti=new APaintWidget();

	timer=new QTimer();
	timer->setInterval(50);

	label_m1 =new QLabel();
	label_m1->setText("0");

	label_m2 =new QLabel();
	label_m2->setText("0");

	checkBox_m1->setText("Motor 1 aktivieren");
	checkBox_m2->setText("Motor 2 aktivieren");

	sld_m1 = new QSlider(Qt::Vertical);
	sld_m2 = new QSlider(Qt::Vertical);

	sld_m1->setRange(0, 255);
	sld_m2->setRange(0, 255);

	comboBox_m1->addItem("Rechts");
	comboBox_m1->addItem("Links");

	comboBox_m2->addItem("Rechts");
	comboBox_m2->addItem("Links");
	
	QGridLayout *layout = new QGridLayout;
 
	layout->addWidget(checkBox_m1, 0, 0);
	layout->addWidget(comboBox_m1, 1, 0);
	layout->addWidget(sld_m1, 2, 0);
	layout->addWidget(label_m1, 2, 1);

	layout->addWidget(painti, 3, 0, 3, 3);

	layout->addWidget(checkBox_m2, 0, 2);
	layout->addWidget(comboBox_m2, 1, 2);
	layout->addWidget(sld_m2, 2, 2);
	layout->addWidget(label_m2, 2, 3);

	wdg->setLayout(layout);
	this->setCentralWidget(wdg);

	QObject::connect(checkBox_m1, SIGNAL (stateChanged(int)), this, SLOT(OnCheckboxClicked_M1(int)));
	QObject::connect(comboBox_m1, SIGNAL (currentIndexChanged(int)),this, SLOT(OnDirectionChanged_M1(int)));
	QObject::connect(sld_m1, SIGNAL (valueChanged(int)),this, SLOT(OnSliderMoved_M1(int)));


	QObject::connect(checkBox_m2, SIGNAL (stateChanged(int)), this, SLOT(OnCheckboxClicked_M2(int)));
	QObject::connect(comboBox_m2, SIGNAL (currentIndexChanged(int)),this, SLOT(OnDirectionChanged_M2(int)));
	QObject::connect(sld_m2, SIGNAL (valueChanged(int)),this, SLOT(OnSliderMoved_M2(int)));

	QObject::connect(timer, SIGNAL (timeout()), this, SLOT(UpdateGUI()));
	timer->start();

}

void myWindow::OnCheckboxClicked_M1(int state) {
	
	if(state) {
		motor1_active=1;
		return;
	}
	strus.speed = 0;
	strus.motor_address = 1;
	strus.direction = comboBox_m1->currentIndex();
	writeValues();
	motor1_active=0;
	resetSlider(sld_m1);
}

void myWindow::OnCheckboxClicked_M2(int state) {
	if(state) {
		motor2_active=1;
		return;
	}
	strus.speed = 0;
	strus.motor_address = 2;
	strus.direction = comboBox_m2->currentIndex();
	writeValues();
	motor2_active=0;
	resetSlider(sld_m2);
}

void myWindow::OnDirectionChanged_M1(int index) {
	strus.motor_address = 1;
	strus.direction = index;
	if(sld_m1->value()) {
		strus.speed = 0;
		writeValues();
		usleep(1000000 * 0.5);
	}
	strus.speed = sld_m1->value();
	writeValues();
}

void myWindow::OnDirectionChanged_M2(int index) {
	strus.motor_address = 2;
	strus.direction = index;
	if(sld_m2->value()) {
		strus.speed = 0;
		writeValues();
		usleep(1000000 * 0.5);
	}
	strus.speed = sld_m2->value();
	writeValues();
}

void myWindow::writeValues() {
	FILE* f=fopen( "/dev/KernelModul", "w");
	fwrite(&strus,1,sizeof(strus),f);
	fclose(f);
}
    
void myWindow::OnSliderMoved_M1(int i)
{
	if(motor1_active) {
		strus.speed = i;
		strus.motor_address = 1;
		strus.direction = comboBox_m1->currentIndex();
		label_m1->setText(QString::number(i));
		writeValues();
		return;
	}
	resetSlider(sld_m1);
}

void myWindow::OnSliderMoved_M2(int i)
{
	if(motor2_active) {
		strus.speed = i;
		strus.motor_address = 2;
		strus.direction = comboBox_m2->currentIndex();
		label_m2->setText(QString::number(i));
		writeValues();
		return;
	}
	resetSlider(sld_m2);
}

void myWindow::resetSlider(QSlider *slider) {
	slider->setValue(0);
}

void myWindow::UpdateGUI()
{   

	painti->amplitude0=sld_m1->value();
	painti->amplitude1=sld_m2->value();
	this->repaint();
}
