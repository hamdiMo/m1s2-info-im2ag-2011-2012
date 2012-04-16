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
  // //QRect rect(10, 20, 80, 60);
   QPainter painter(this);
  // // painter.setPen(pen);
  // // painter.setBrush(brush);
  // // painter.setRenderHint(QPainter::Antialiasing, true);
  // // //
  // painter.setBackgroundMode(Qt::TransparentMode);
   //QColor backgroundColor = palette().light().color();
    // backgroundColor.setAlpha(200);
  //  painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    //painter.fillRect(QRect(40, 40, width()-10, height()-10),backgroundColor);
   painter.setPen(palette().dark().color());
   QBrush brush2(Qt::Dense4Pattern);
    QPainterPath path;
    path.addEllipse(QRect(0, 0, width() - 1, height() - 1));
    painter.fillPath(path,brush2);
  // painter.setBrush(Qt::NoBrush);



    // QPainter p(this);
    // p.setRenderHint(QPainter::Antialiasing);
    // // p.setClipRect(e->rect());

    // //make sure you clean your widget with a transparent
    // //  color before doing any rendering
    // //  note the usage of a composition mode Source
    // //  it's important!
    // // p.save();
    // p.setCompositionMode(QPainter::CompositionMode_Source);
    // p.fillRect(rect(), Qt::transparent);
    // p.restore();
    // QPixmap   cache;
    
    // cache.fill(Qt::transparent);
    // QPainter p2(&cache);
    // p2.setRenderHint(QPainter::Antialiasing);
    // //renderer->render(&p);
    // p2.drawPixmap(0, 0, cache);
    // QColor backgroundColor = palette().light().color();
    // backgroundColor.setAlpha(100);
    // p.fillRect(QRect(40, 40, width()-10, height()-10),backgroundColor);






}
