#include "Window.h"
#include <QFileDialog>
#include <iostream>


Window::Window() : QWidget()
{
  initLayout();
  m_button_addFile = new QPushButton("Add File");
  m_list_path = new QListWidget();
  m_label_img = new QLabel();
  m_list_path->setMinimumWidth(200);

  QObject::connect(m_button_addFile, &QPushButton::clicked, this, &Window::openFile);
  QObject::connect(m_list_path, &QListWidget::itemActivated, this, &Window::displayImage);

  QImage img("img/banana.jpg");
  QPixmap pixmap = QPixmap::fromImage(img);
  m_label_img->setPixmap(pixmap);

  m_left_layout->addWidget(m_list_path);
  m_left_layout->addWidget(m_button_addFile);
  m_right_layout->addWidget(m_label_img);

  setWindowTitle("Projet Banque de données multimédia");
  show();
}

Window::~Window()
{
  delete(m_button_addFile);
  delete(m_list_path);
  delete(m_label_img);
  delete(m_left_layout);
  delete(m_right_layout);
  delete(m_main_layout);
}

void Window::initLayout()
{
  m_main_layout = new QHBoxLayout();
  m_left_layout = new QVBoxLayout();
  m_right_layout = new QVBoxLayout();
  m_main_layout->addLayout(m_left_layout);
  m_main_layout->addLayout(m_right_layout);
  setLayout(m_main_layout);
}

void Window::openFile()
{
  QStringList files = QFileDialog::getOpenFileNames(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");

  foreach(QString file, files)
  {
    Image *it = new Image();
    it->setName(file.split("/").last());
    it->setPath(file);
    it->setText(it->getName());
    m_list_path->insertItem(0,it);
    if(file == files.first())
      displayImage(it);
  }
}

void Window::displayImage(QListWidgetItem *l)
{
  Image& img = dynamic_cast<Image&>(*l);
  m_label_img->setPixmap(QPixmap(img.getPath()).scaled(680,460));
}
