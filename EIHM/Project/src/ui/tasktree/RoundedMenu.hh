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
  RoundedMenu(QWidget *parent = 0);
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

protected:
  void paintEvent(QPaintEvent *event);
  


};

#endif
