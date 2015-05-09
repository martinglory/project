#include "coordinatepoint.h"
#include <QtGui/QApplication>
#include "CustomPlotWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CoordinatePoint w;
	w.show();
	return a.exec();
}
