#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include "APaintWidget.h"
#include <QtCore/QTimer>

class myWindow : public QMainWindow{
    Q_OBJECT
public:
	QSlider *sld_m1;
	QSlider *sld_m2;
	QWidget * wdg;
	QVBoxLayout *vlay;
	QCheckBox *checkBox_m1;
	QCheckBox *checkBox_m2;
	QComboBox *comboBox_m1;
	QComboBox *comboBox_m2;
	QLabel *label_m1; 
	QLabel *label_m2;
	APaintWidget *painti;
	QTimer *timer;

	myWindow();
	
	
public slots:
	void OnSliderMoved_M1(int i);
	void OnSliderMoved_M2(int i);
	void OnCheckboxClicked_M1(int state);
	void OnCheckboxClicked_M2(int state);
	void OnDirectionChanged_M1(int index);
	void OnDirectionChanged_M2(int index);
	void UpdateGUI();
	
private:
    void writeValues();
	void resetSlider(QSlider *slider);
	bool motor1_active = false;
	bool motor2_active = false;
};


