#ifndef DEF_SEARCHWINDOW
#define DEF_SEARCHWINDOW

#include <QDialog>
#include <QPushButton>
#include "Image.h"

class SearchWindow : public  QDialog
{
  private:
    QPushButton    *m_button_openFile;
    Image          *m_searchImg;
    QLabel         *m_labelImg;
    QHBoxLayout    *m_layout;

  public:
    SearchWindow();
    ~SearchWindow();
    void openFile(void);
    void compute(void);
};

#endif
