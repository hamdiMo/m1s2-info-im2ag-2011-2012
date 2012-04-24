#ifndef _ROUNDED_MENU_HH_
#define _ROUNDED_MENU_HH_

#include <iostream>
#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QPixmap>
 

class RoundedMenu : public QWidget { Q_OBJECT

public:
   /** Constructeurs et destructeurs */
  RoundedMenu(QWidget *parent = 0,int=0,int=0);
  ~RoundedMenu();
  
  QSize minimumSizeHint() const;
  QSize sizeHint() const;
  void  keyPressEvent ( QKeyEvent * event );
  void  keyReleaseEvent ( QKeyEvent * event );
  void  mouseDoubleClickEvent ( QMouseEvent * event );
  void  mouseMoveEvent ( QMouseEvent * event );
  void  mousePressEvent ( QMouseEvent * event );
  void  mouseReleaseEvent ( QMouseEvent * event );    
  void  wheelEvent ( QWheelEvent * event );

  static const int SIZE=150;
  static const float PI=3.14159265;
  static const int SIDE=100;  
protected:
  void paintEvent(QPaintEvent *event);
  

private:
  int p_x;
  int p_y;
  int souris_x;
  int souris_y;
  QRadialGradient* p_gradient;

};

#endif
