#include "Window.h"
#include <QFileDialog>
#include <QDir>
#include <iostream>


Window::Window() : QMainWindow()
{
  m_list_path = new QListWidget();
  m_button_addFile = new QPushButton("Ajouter un fichier");
  m_button_newSearch = new QPushButton("Nouvelle recherche");
  m_dockWidget = new QDockWidget("Fichiers", this);
  m_toolBar = new QToolBar("Outils",this);
  m_searchWindow = new SearchWindow();
  m_p1 = new Page1();
  m_p2 = new Page2();
  m_p3 = new Page3();
  m_tabs = new QTabWidget();

  m_tabs->setMinimumWidth(640);
  m_tabs->setMinimumHeight(480);
  m_tabs->addTab(m_p1, "Image originale");
  m_tabs->addTab(m_p2, "Histogramme");
  m_tabs->addTab(m_p3, "Image modifiée");

  m_list_path->setMinimumWidth(200);

  m_dockWidget->setWidget(m_list_path);

  m_toolBar->addWidget(m_button_addFile);
  m_toolBar->addSeparator();
  m_toolBar->addWidget(m_button_newSearch);

  setCentralWidget(m_tabs);
  addDockWidget(Qt::LeftDockWidgetArea, m_dockWidget);
  addToolBar(m_toolBar);

  openFile();

  setWindowTitle("Projet Banque de données multimédia");
  show();

  QObject::connect(m_button_addFile, &QPushButton::clicked, this, &Window::openFile);
  QObject::connect(m_button_newSearch, &QPushButton::clicked, this, &Window::openSearchWindow);
  QObject::connect(m_list_path, &QListWidget::itemActivated, this, &Window::displayImage);
}

Window::~Window(void)
{
  delete(m_searchWindow);
  delete(m_button_addFile);
  delete(m_list_path);
  delete(m_p1);
  delete(m_p2);
  delete(m_p3);
  delete(m_tabs);
  delete(m_dockWidget);
  delete(m_toolBar);
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

void Window::openSearchWindow(void)
{
  m_searchWindow->exec();
}
