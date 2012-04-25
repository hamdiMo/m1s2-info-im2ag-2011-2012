#include "RoundedMenu.hh"
//#include <direct.h>
#include <QPainter>
#include <QMouseEvent>
#include <QPicture>
#include <math.h>


/** Constructeurs et destructeurs */
RoundedMenu::RoundedMenu(QWidget *parent,int x, int y,std::vector<QAction*>* action)
  : QWidget(parent),
    p_x(x),
    p_y(y),
    p_Actions(action)
{
  setAttribute(Qt::WA_TranslucentBackground);
  p_gradient= new QRadialGradient(SIZE/2,SIZE/2,SIDE*0.5,SIZE/2,SIZE/2);
  /*Definition du Gradient */
  p_gradient->setFocalPoint(SIZE/2,SIZE/2);
  p_gradient->setColorAt(0.0, QColor(74,241,250,0 ));
  p_gradient->setColorAt(0.1, QColor(74,241,250, 0));
  p_gradient->setColorAt(0.2, QColor(74,241,250, 0));
  p_gradient->setColorAt(0.3, QColor(74,241,250, 0));
  p_gradient->setColorAt(0.4, QColor(74,241,250, 0));
  p_gradient->setColorAt(0.5, QColor(74,241,250, 0));
  p_gradient->setColorAt(0.6, QColor(74,241,250, 60));
  p_gradient->setColorAt(0.7, QColor(74,241,250, 80));
  p_gradient->setColorAt(1.0, QColor(74,241,250, 100));
  souris_x=p_x;
  souris_y=p_y;
  setMouseTracking(true);
  if(p_Actions!=0)
    p_nb_case=p_Actions->size();
  else
    p_nb_case=4;
}





RoundedMenu::~RoundedMenu() {}


QSize RoundedMenu::minimumSizeHint() const{
  return QSize(SIZE, SIZE);
}



QSize RoundedMenu::sizeHint() const{
  return QSize(SIZE, SIZE);
}


void RoundedMenu::paintEvent(QPaintEvent * /* event */){
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  // painter.setPen(QColor(0, 0, 0, 255));

  painter.setPen(QColor(0, 0, 0, 50));
  painter.setBrush(*p_gradient);

  QRectF rectangle(0,0, SIZE, SIZE);
  // painter.drawRect( rectangle);
  //  
  int startAngle = 0;
  int spanAngle = 380* 16;
  painter.drawArc(rectangle,startAngle,spanAngle);
  int rang=0;
  for (float angle=0.0 ; angle<2*PI;angle+=2*PI/p_nb_case){
    float Bx  =((SIZE/2-1) * cos(angle));
    float By  =((SIZE/2-1) * sin(angle));
    float B1x  =SIZE/2+((SIZE/6) * cos(angle));
    float B1y  =SIZE/2+((SIZE/6) * sin(angle));
    painter.drawLine(B1x,B1y,Bx+SIZE/2,By+SIZE/2);
    if(p_Actions!=0){
      float B2x  =SIZE/2+((SIZE/3) * cos(angle+PI/p_nb_case));
      float B2y  =SIZE/2+((SIZE/3) * sin(angle+PI/p_nb_case));
      QPixmap img = (*p_Actions)[rang]->icon().pixmap(SIZE/3,SIZE/3);
      painter.drawPixmap(QPoint(B2x-img.width()/2,B2y-img.height()/2),img);
    }

    ++rang;
  }
  float angle = 0.0;
  if(souris_x!=0){
    angle = atan((double)souris_y/(double)souris_x);
    if (souris_x < 0) angle += PI; 
   
  }
  else if (souris_y < 0) angle = PI/2.0;
  else angle =(-((float)PI)/2.0);
  if (angle < 0) angle += 2*PI;

  for (float p_angle=0.0 ; p_angle<2*3.14;p_angle+=2*PI/p_nb_case){
    if(2*PI-angle>p_angle&&2*PI-angle<p_angle+2*PI/p_nb_case){
      painter.drawPie(rectangle,16*((p_angle)*180/PI), 16 *((2*PI/p_nb_case)*180/PI)  );
    }
  }
 

}
/** METHODS */
void RoundedMenu::keyPressEvent ( QKeyEvent * event ){}
void RoundedMenu::keyReleaseEvent ( QKeyEvent * event ) {

}
void RoundedMenu::mouseDoubleClickEvent ( QMouseEvent * event ){}
void RoundedMenu::mouseMoveEvent ( QMouseEvent * event ){
  souris_x=event->x()-p_x;
  souris_y=event->y()-p_y;
  repaint();

}
void RoundedMenu::mousePressEvent ( QMouseEvent * event ){
  std::cout << "mouse move PressedEvent" << std::endl;
}
void RoundedMenu::mouseReleaseEvent ( QMouseEvent * event ){
 
  int nb=0;
  float angle = 0.0;
  if(souris_x!=0){
    angle = atan((double)souris_y/(double)souris_x);
    if (souris_x < 0) angle += PI; 
   
  }
  else if (souris_y < 0) angle = PI/2.0;
  else angle =(-((float)PI)/2.0);
  if (angle < 0) angle += 2*PI;

  for (float p_angle=0.0 ; p_angle<2*3.14;p_angle+=2*PI/p_nb_case){
    if(angle>p_angle&&angle<p_angle+2*PI/p_nb_case){
      (*p_Actions)[nb]->trigger();
    }
    ++nb;
  }
}
void RoundedMenu::wheelEvent ( QWheelEvent * event ) {}
