#include "StoreDashAdmin.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	a.setStyle("Fusion");
	a.setWindowIcon(QIcon("storedash.png"));

	StoreDashAdmin w;
	w.show();

	return a.exec();
}
