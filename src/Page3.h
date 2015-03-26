#ifndef DEF_PAGE3
#define DEF_PAGE3

#include <QLabel>
#include <QLayout>
#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>
#include "Image.h"

class Page3 : public QLabel
{
  private:
    Image           m_selected_img;
    QLabel         *m_label_img;
    QHBoxLayout    *m_layout;
    QGroupBox      *m_groupbox;
    QFormLayout    *m_form_layout;
    QCheckBox      *m_box_filter_avg;
    QCheckBox      *m_box_fourier;
    QCheckBox      *m_box_fourier_cut;
    QCheckBox      *m_box_fourier_inverse;
    QCheckBox      *m_box_sobel;
    QCheckBox      *m_box_bounding_box;
    QCheckBox      *m_box_interest_points;
    QPushButton    *m_button_reset;

  public:
    Page3(void);
    ~Page3(void);
    void display(Image img);
    void displayFourier();
};

#endif
