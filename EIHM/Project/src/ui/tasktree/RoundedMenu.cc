#include "RoundedMenu.hh"
#include <QPainter>




/** Constructeurs et destructeurs */
RoundedMenu::RoundedMenu(QWidget *parent)
  : QWidget(parent){
  setAttribute(Qt::WA_TranslucentBackground);
}


RoundedMenu::~RoundedMenu() {}


QSize RoundedMenu::minimumSizeHint() const{
  return QSize(100, 100);
}



QSize RoundedMenu::sizeHint() const{
  return QSize(100, 100);
}

void RoundedMenu::setPen(const QPen &pen){
  this->pen = pen;
  update();
}

void RoundedMenu::setBrush(const QBrush &brush){
  this->brush = brush;
  update();
}

void RoundedMenu::paintEvent(QPaintEvent * /* event */){

  QPainter painter(this);
  double side=100;
  QRadialGradient gradient(50.0, 50.0, side*0.5,50.0, 50.0);
  gradient.setColorAt(0.0, QColor(255, 255, 255, 255));
  gradient.setColorAt(0.1, QColor(255, 255, 255, 31));
  gradient.setColorAt(0.7, QColor(255, 255, 255, 31));
  gradient.setColorAt(0.8, QColor(0, 31, 0, 31));
  gradient.setColorAt(0.9, QColor(255, 255, 255, 255));
  gradient.setColorAt(1.0, QColor(255, 255, 255, 255));
  painter.setPen(QColor(0, 0, 0, 32));
  painter.setBrush(gradient);
  //-50,-50,100,100
  //painter.drawEllipse(-side/2.0 + 1, -side/2.0 + 1,side - 2, side - 2);
  painter.drawEllipse(QPoint(50,50),49,49);





}
