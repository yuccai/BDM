#ifndef DEF_WINDOW
#define DEF_WINDOW

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QListWidget>
#include <QObject>
#include <QTabWidget>
#include "Image.h"
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"

class Window : public QWidget
{
  private:
    QHBoxLayout    *m_main_layout;
    QVBoxLayout    *m_left_layout;
    QVBoxLayout    *m_right_layout;
    QListWidget    *m_list_path;
    QPushButton    *m_button_addFile;
    QTabWidget     *m_tabs;
    Page1          *m_p1;
    Page2          *m_p2;
    Page3          *m_p3;

  public:
    Window(void);
    ~Window(void);
    void initLayout(void);

  public slots:
    void openFile(void);
    void displayImage(QListWidgetItem *img);
};

#endif
