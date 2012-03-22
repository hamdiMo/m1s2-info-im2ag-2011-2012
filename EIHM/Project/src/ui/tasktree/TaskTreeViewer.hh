#ifndef _TASKTREE_VIEWER_HH_
#define _TASKTREE_VIEWER_HH_


#include <iostream>
#include <QMouseEvent>
#include <QGraphicsView>
class TaskTreeViewer : public QGraphicsView { Q_OBJECT
public:
  /** Constructeurs et destructeurs */
  TaskTreeViewer();
  ~TaskTreeViewer();
   
public slots:

  /** SLOTS**/
  void  keyPressEvent ( QKeyEvent * event );
  void  keyReleaseEvent ( QKeyEvent * event );
  void  mouseDoubleClickEvent ( QMouseEvent * event );
  void  mouseMoveEvent ( QMouseEvent * event );
  void  mousePressEvent ( QMouseEvent * event );
  void  mouseReleaseEvent ( QMouseEvent * event );    
  void  wheelEvent ( QWheelEvent * event );


};

#endif
