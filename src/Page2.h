#ifndef DEF_PAGE2
#define DEF_PAGE2

#include <QLabel>
#include <QLayout>
#include "Image.h"
#include "lib/qcustomplot/qcustomplot.h"

class Page2 : public QLabel
{
  private:
    QCustomPlot    *m_customPlot;
    QVBoxLayout    *m_layout;

  public:
    Page2(void);
    ~Page2(void);
    void initCustomPlot(void);
    void display(Image img);
    void toggleBarChart(QCPLegend *l, QCPAbstractLegendItem *i, QMouseEvent *e);
};

#endif
