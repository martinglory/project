#include "library.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  
  GeoLib* window = new GeoLib();

  window->show();
  
  return app.exec();


}
