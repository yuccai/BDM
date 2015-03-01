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
#include "lib/qcustomplot.h"

class Window : public QWidget
{
  private:
    QHBoxLayout    *m_main_layout;
    QVBoxLayout    *m_left_layout;
    QVBoxLayout    *m_right_layout;
    QLabel         *m_label_img;
    QListWidget    *m_list_path;
    QPushButton    *m_button_addFile;
    QTabWidget     *m_tabs;
    QCustomPlot    *m_customPlot;

  public:
    Window(void);
    ~Window(void);
    void initLayout(void);
    void initCustomPlot(void);
    QCustomPlot* getCustomPlot(void);

  public slots:
    void openFile(void);
    void displayImage(QListWidgetItem *img);
};

#endif
