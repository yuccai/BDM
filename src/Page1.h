#ifndef DEF_PAGE1
#define DEF_PAGE1

#include <QLabel>
#include "Image.h"

class Page1 : public QLabel
{
  private:

  public:
    Page1(void);
    ~Page1(void);
    void display(Image img);
};

#endif
