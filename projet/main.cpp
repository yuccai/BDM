#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include "Window.h"


int main(int argc, char *argv[ ])
{
  QApplication app(argc, argv);
  Window window;

  return app.exec();
}
