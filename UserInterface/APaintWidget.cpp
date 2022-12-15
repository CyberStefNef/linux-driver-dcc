#include "APaintWidget.h"
 
 
 APaintWidget::APaintWidget()
 {
	 setMinimumHeight(300);
	 setMinimumWidth(800);
 }
 
void APaintWidget::paintEvent(QPaintEvent *event)
{

    for(int i=0;i<size-1;i++)
    {
        data[0][i]=data[0][i+1];
		data[1][i]=data[1][i+1];
    }
    data[0][size-1]=amplitude0;
	data[1][size-1]=amplitude1;

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen myPen(Qt::red, 2, Qt::SolidLine);
	painter.setPen(myPen);

	QPainterPath path;
	painter.drawLine(0, 300, 800, 300);
	painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::FlatCap));
	path.moveTo(0,0);
	for(int i=0;i<size;i++)
		path.lineTo(i,(int)(-1*data[0][i]+300));
	painter.drawPath(path);

	QPainterPath path2;
	painter.drawLine(0, 300, 800, 300);
	painter.setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::FlatCap));
	path2.moveTo(0,0);
	for(int i=0;i<size;i++)
		path2.lineTo(i,(int)(-1*data[1][i]+300));
	painter.drawPath(path2);

	painter.end(); 
}
