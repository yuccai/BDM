#ifndef DEF_SEARCHWINDOW
#define DEF_SEARCHWINDOW

#include <QDialog>
#include <QList>
#include <QPushButton>
#include "Image.h"

class SearchWindow : public  QDialog
{
  private:
    QPushButton    *m_button_openFile;
    QList <Image*> *m_list_image;
    Image          *m_searchImg;
    QLabel         *m_labelImg;
    QHBoxLayout    *m_layout;
    QList <QString> m_res;

  public:
    SearchWindow(QList <Image*> *li);
    ~SearchWindow();
    void openFile(void);
    void compute(void);
    void loadListImage(void);
};

#endif
