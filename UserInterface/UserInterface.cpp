#include "myWindow.h"

int main(int argc, char *argv[])
{
	/*
	FILE* f=fopen( "/dev/KernelModul", "w");
	
	struct transferStruct strus={
        .direction=0,
        .motor_address=2,
        .speed=0,
        .light=0,
    };
	
	printf("Nachricht:%d i:%d  j:%d values:",strus.direction);
	printf("sende %d Bytes\n",sizeof(strus));
	int angenommen=fwrite(&strus,1,sizeof(strus),f);
	printf("Der Treiber hat %d bytes angenommen\n",angenommen);*/

	printf("Start Application!\n");
	QApplication a(argc, argv);
	myWindow *wnd=new myWindow();
	wnd->show();
	return a.exec();

	//fclose(f);
}

	
	
	
