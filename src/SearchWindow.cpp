#include "SearchWindow.h"
#include "Histogram.h"

SearchWindow::SearchWindow(QList <Image*> *li) : QDialog()
{
  m_button_openFile = new QPushButton("Selection fichier");
  m_searchImg = new Image();
  m_labelImg = new QLabel();
  m_layout = new QHBoxLayout();
  m_list_image = new QList <Image*>();
  m_list_image = li;


  this->setLayout(m_layout);
  m_layout->addWidget(m_labelImg);
  m_layout->addWidget(m_button_openFile);

  QObject::connect(m_button_openFile, &QPushButton::clicked, this, &SearchWindow::openFile);
}

SearchWindow::~SearchWindow()
{
  delete(m_button_openFile);
  delete(m_labelImg);
  delete(m_searchImg);
  delete(m_layout);
}

void SearchWindow::openFile(void)
{
  QString file = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");

  m_searchImg->setName(file.split("/").last());
  m_searchImg->setPath(file);
  m_searchImg->setText(m_searchImg->getName());
  m_searchImg->loadImage(file);
  m_labelImg->setPixmap(QPixmap::fromImage(m_searchImg->getImageOriginal()).scaled(480,360));
  loadListImage();
}

void SearchWindow::compute(void)
{
  m_searchImg->getHistogram().compute(m_searchImg->getImageOriginal());
  loadListImage();
}

void SearchWindow::loadListImage()
{
  Histogram h;
  QList <int> cols;
  int l,i;

  m_res.clear();
  h = m_searchImg->getHistogram();
  h.compute(m_searchImg->getImageOriginal());
  cols = h.getColors();

  std::cout << "BEGIN : " << m_searchImg->getPath().toStdString() << std::endl;
  foreach(Image *img, *m_list_image){
    h = img->getHistogram();
    h.compute(img->getImageOriginal());

    i=0;
    l = min(h.getColors().count(),cols.count());

    foreach(int c1, h.getColors())
    {
      //std::cout << "c1 : " << c1 << std::endl;
      foreach(int c2, cols)
      {
        //std::cout << "c2 : " << c2 << std::endl;
        if(abs(c1-c2)<=1)
          i++;
      }
    }
    if(i>=l && i >0){
      m_res << img->getPath();
      std::cout << "i : " << i << ", l : " << l << " -> " << img->getPath().toStdString() << std::endl;
    }
  }
  std::cout << "END : res = " << m_res.count()<< std::endl;
}
