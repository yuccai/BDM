#ifndef DEF_FILTER
#define DEF_FILTER

#include <QVector>
#include <QImage>
#include <QList>
#include <QPoint>

class Filter
{
  private:
    QVector <QVector <int> > m_avg;
    QVector <QVector <int> > m_sobelX;
    QVector <QVector <int> > m_sobelY;

  public:
    Filter(void);
    ~Filter(void);
    void avgFilter(QImage *dest);
    void sobelFilter(QImage *dest);
    QList <QPoint> findInterestPoints(QImage src);
    QList <QPoint> findHoughPoints(QImage src);
    void erosion(QImage *dest, int r);
    void dilatation(QImage *dest, int r);
    void negative(QImage *img);
};

#endif
