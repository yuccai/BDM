#include "Window.h"
#include <QFileDialog>
#include <QDir>
#include <iostream>


Window::Window() : QWidget()
{
  initLayout();
  m_list_path = new QListWidget();
  m_button_addFile = new QPushButton("Add File");
  m_p1 = new Page1();
  m_p2 = new Page2();
  m_p3 = new Page3();
  m_tabs = new QTabWidget();
  m_tabs->setMinimumWidth(640);
  m_tabs->setMinimumHeight(480);
  m_list_path->setMinimumWidth(200);

  QObject::connect(m_button_addFile, &QPushButton::clicked, this, &Window::openFile);
  QObject::connect(m_list_path, &QListWidget::itemActivated, this, &Window::displayImage);

  m_left_layout->addWidget(m_list_path);
  m_left_layout->addWidget(m_button_addFile);
  m_right_layout->addWidget(m_tabs);

  m_tabs->addTab(m_p1, "Image originale");
  m_tabs->addTab(m_p2, "Histogramme");
  m_tabs->addTab(m_p3, "Image modifiée");

  openFile();

  setWindowTitle("Projet Banque de données multimédia");
  show();
}

Window::~Window(void)
{
  delete(m_button_addFile);
  delete(m_list_path);
  delete(m_p1);
  delete(m_p2);
  delete(m_p3);
  delete(m_tabs);
  delete(m_left_layout);
  delete(m_right_layout);
  delete(m_main_layout);
}

void Window::initLayout(void)
{
  m_main_layout = new QHBoxLayout();
  m_left_layout = new QVBoxLayout();
  m_right_layout = new QVBoxLayout();
  m_main_layout->addLayout(m_left_layout);
  m_main_layout->addLayout(m_right_layout);
  this->setLayout(m_main_layout);
}

void Window::openFile(void)
{
  //QStringList files = QFileDialog::getOpenFileNames(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
  QStringList files = QDir("img").entryList();
  QString path = QDir("img").absolutePath();

  foreach(QString file, files)
  {
    file = path + "/" +  file;
    Image *it = new Image();
    it->setName(file.split("/").last());
    it->setPath(file);
    it->setText(it->getName());
    it->loadImage(file);
    m_list_path->insertItem(0,it);
    if(file == files.first())
      displayImage(it);
  }
}

void Window::displayImage(QListWidgetItem *l)
{
  Image& img = dynamic_cast<Image&>(*l);
  m_p1->display(img);
  m_p2->display(img);
  m_p3->display(img);
}
