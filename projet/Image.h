#ifndef DEF_IMAGE
#define DEF_IMAGE

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QListWidget>
#include <QObject>
#include <QRgb>

class Image : public QListWidgetItem
{
  private:
    QString m_name;
    QString m_path;
    QImage  m_img;

  public:
    Image();
    ~Image();
    void setName(const QString str);
    void setPath(const QString str);
    void loadImage(const QString str);
    QString getName(void);
    QString getPath(void);
    QImage getImage(void);
    int* historgramme[256](void);
};

#endif
