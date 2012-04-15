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
			
public slots:
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);

protected:
  void paintEvent(QPaintEvent *event);

private:
 
  QPen pen;
  QBrush brush;
  QPixmap pixmap;

};

#endif
