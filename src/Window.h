#ifndef DEF_WINDOW
#define DEF_WINDOW

#include <QApplication>
//#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QListWidget>
#include <QObject>
#include <QDockWidget>
#include <QToolBar>
#include <QTabWidget>
#include "Image.h"
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"
#include "SearchWindow.h"

class Window : public QMainWindow
{
  private:
    QListWidget    *m_list_path;
    QPushButton    *m_button_addFile;
    QPushButton    *m_button_newSearch;
    QTabWidget     *m_tabs;
    QDockWidget    *m_dockWidget;
    QToolBar       *m_toolBar;
    SearchWindow   *m_searchWindow;
    Page1          *m_p1;
    Page2          *m_p2;
    Page3          *m_p3;

  public:
    Window(void);
    ~Window(void);

  public slots:
    void openFile(void);
    void displayImage(QListWidgetItem *img);
    void openSearchWindow(void);
};

#endif
