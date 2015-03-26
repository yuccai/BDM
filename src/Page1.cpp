#include "Page1.h"

Page1::Page1(void) : QLabel()
{
}

Page1::~Page1(void)
{
}

void Page1::display(Image img)
{
  this->setPixmap(QPixmap::fromImage(img.getImageOriginal()).scaled(640,480));
}
