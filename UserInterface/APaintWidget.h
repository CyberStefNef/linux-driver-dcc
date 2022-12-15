
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtWidgets/QWidget>
#include <math.h>
 
class APaintWidget : public QWidget
{
    Q_OBJECT
public:
	APaintWidget();
	int amplitude0=0;
	int amplitude1=0;
	int data[2][800] = {0};
	int size = 800;
protected:
    void paintEvent(QPaintEvent *event);
signals:
public slots:
 
};
