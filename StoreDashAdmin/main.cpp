#include "StoreDashAdmin.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	StoreDashAdmin w;
	w.show();
	return a.exec();
}
