#include "RoundedMenu.hh"
#include <QPainter>
#include <QMouseEvent>



/** Constructeurs et destructeurs */
RoundedMenu::RoundedMenu(QWidget *parent,int x, int y)
  : QWidget(parent),
    p_x(x),
    p_y(y)
{
  setAttribute(Qt::WA_TranslucentBackground);
  double side=100;
  p_gradient= new QRadialGradient(50.0, 50.0, side*0.5, 50.0, 50.0);
  setMouseTracking(true);
  // p_gradient->setColorAt(0.0, QColor(255, 255, 255, 255));
  // p_gradient->setColorAt(0.1, QColor(255, 255, 255, 255));
  // p_gradient->setColorAt(0.7, QColor(255, 255, 255, 200));
  // p_gradient->setColorAt(0.8, QColor(0, 31, 0, 100));
  // p_gradient->setColorAt(0.9, QColor(255, 255, 255, 50));
  // p_gradient->setColorAt(1.0, QColor(255, 255, 255, 0));
  
 
}


RoundedMenu::~RoundedMenu() {}


QSize RoundedMenu::minimumSizeHint() const{
  return QSize(100, 100);
}



QSize RoundedMenu::sizeHint() const{
  return QSize(100, 100);
}


void RoundedMenu::paintEvent(QPaintEvent * /* event */){
  QPainter painter(this);
   
  painter.setPen(QColor(0, 0, 0, 32));
  painter.setBrush(*p_gradient);
  painter.drawEllipse(QPoint(50,50),49,49);
}
/** METHODS */
void RoundedMenu::keyPressEvent ( QKeyEvent * event ){}
void RoundedMenu::keyReleaseEvent ( QKeyEvent * event ) {}
void RoundedMenu::mouseDoubleClickEvent ( QMouseEvent * event ){}
void RoundedMenu::mouseMoveEvent ( QMouseEvent * event ){
  std::cout<<"set focal point "<<event->x()-p_x+50<<"    "<<event->y()-p_y+50<<std::endl;
   p_gradient->setFocalPoint(event->x()-p_x+50,event->y()-p_y+50);
  // p_gradient->setColorAt(0, Qt::red);
  // p_gradient->setColorAt(0.5, Qt::blue);
  // p_gradient->setColorAt(1, Qt::green);   
 // p_gradient->setColorAt(0.0, QColor(255, 255, 255, 0));
 //  p_gradient->setColorAt(0.1, QColor(255, 255, 255, 10));
 //  p_gradient->setColorAt(0.2, QColor(255, 255, 255, 20));
 //  p_gradient->setColorAt(0.3, QColor(0, 31, 0, 30));
 //  p_gradient->setColorAt(0.5, QColor(255, 255, 255, 100));
 //  p_gradient->setColorAt(1.0, QColor(255, 255, 255, 255));
  
// p_gradient->setColorAt(0.0, QColor(255, 255, 255, 255));
//   p_gradient->setColorAt(0.1, QColor(255, 255, 255, 31));
//   p_gradient->setColorAt(0.7, QColor(255, 255, 255, 31));
//   p_gradient->setColorAt(0.8, QColor(0, 31, 0, 31));
//   p_gradient->setColorAt(0.9, QColor(255, 255, 255, 255));
//   p_gradient->setColorAt(1.0, QColor(255, 255, 255, 255));
  repaint();


}
void RoundedMenu::mousePressEvent ( QMouseEvent * event ){
 std::cout << "mouse move PressedEvent" << std::endl;
}
void RoundedMenu::mouseReleaseEvent ( QMouseEvent * event ){
 std::cout << "mouse move mouseReleaseEvent " << std::endl;
}
void RoundedMenu::wheelEvent ( QWheelEvent * event ) {}
