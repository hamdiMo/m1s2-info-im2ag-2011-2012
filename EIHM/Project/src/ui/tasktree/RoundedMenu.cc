#include "RoundedMenu.hh"
#include <QPainter>




/** Constructeurs et destructeurs */
RoundedMenu::RoundedMenu(QWidget *parent)
  : QWidget(parent){
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
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
  QRect rect(10, 20, 80, 60);
  QPainter painter(this);
  // painter.setPen(pen);
  // painter.setBrush(brush);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setBackgroundMode(Qt::TransparentMode);
  // QColor backgroundColor = palette().light().color();
  // backgroundColor.setAlpha(100);
  // painter.fillRect(QRect(0, 0, width(), height()),backgroundColor);
  //painter.setPen(palette().dark().color());
  // QBrush brush2(Qt::Dense4Pattern);
  // QPainterPath path;
  //path.addEllipse(QRect(0, 0, width() - 1, height() - 1));
  //painter.fillPath(path,brush2);
  // painter.setBrush(Qt::NoBrush);
}
