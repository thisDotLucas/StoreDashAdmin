#include "StoreDashAdmin.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	a.setStyle("Fusion");
	StoreDashAdmin w;
	w.show();
	return a.exec();
}
