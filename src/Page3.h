#ifndef DEF_PAGE3
#define DEF_PAGE3

#include <QLabel>
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QList>
#include <QPoint>
#include "Image.h"
#include "Hough.h"

class Page3 : public QLabel
{
  private:
    Image           m_selected_img;
    QLabel         *m_label_img;
    QHBoxLayout    *m_layout;
    QHBoxLayout    *m_layout_threshold;
    QHBoxLayout    *m_layout_morpho;
    QGroupBox      *m_groupbox;
    QFormLayout    *m_form_layout;
    QPushButton    *m_button_filter_avg;
    QPushButton    *m_button_fourier;
    QPushButton    *m_button_fourier_cut;
    QPushButton    *m_button_fourier_inverse;
    QPushButton    *m_button_sobel;
    QPushButton    *m_button_bounding_box;
    QCheckBox      *m_box_interest_points;
    QCheckBox      *m_hide_options;
    QPushButton    *m_button_reset;
    QSpinBox       *m_threshold_inf;
    QSpinBox       *m_threshold_sup;
    QSpinBox       *m_morpho_r;
    QPushButton    *m_button_threshold;
    QPushButton    *m_button_hough;
    QPushButton    *m_button_erosion;
    QPushButton    *m_button_dilatation;
    QPushButton    *m_button_negative;
    Hough           m_hough;

  public:
    Page3(void);
    ~Page3(void);
    void display(Image img);
    void displayFourier();
    void displayFourierCut();
    void displayFourierInverse();
    void displayAvgFilter();
    void displaySobelFilter();
    void displayThresold();
    void displayInterestPoints(bool b);
    void displayHoughChart();
    void displayHough();
    void displayErosion();
    void displayDilatation();
    void displayNegative();
    void reset();
};

#endif
