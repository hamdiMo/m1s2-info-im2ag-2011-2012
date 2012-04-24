#ifndef _TASKTREE_VIEWER_HH_
#define _TASKTREE_VIEWER_HH_

#include <iostream>
#include <QMouseEvent>
#include <QGraphicsView>
#include "TaskTree.hh"

class TaskTreeItem;
class RoundedMenu;
class TaskTreeViewer : public QGraphicsView { Q_OBJECT

public:

  /** Constructeurs et destructeurs */
  TaskTreeViewer(TaskTree* taskTree);
  ~TaskTreeViewer();

  /** Accesseur */
  std::vector<TaskTreeItem*> getSelectedItems();

  /** Methodes */
  TaskTreeItem* createTaskTreeItems(TaskTree* t);
  void displayTaskTreeItems();
  void displayTaskTree(TaskTree* t, int xmin, int ymin, int xmax, int ymax);
  int computeWidth(TaskTree* t);
  int computeHeight(TaskTree* t);
  void computeSceneRect(int x, int y, int xSize, int ySize);

public slots:

  /** Slots */
  void  keyPressEvent ( QKeyEvent * event );
  void  keyReleaseEvent ( QKeyEvent * event );
  void  mouseDoubleClickEvent ( QMouseEvent * event );
  void  mouseMoveEvent ( QMouseEvent * event );
  void  mousePressEvent ( QMouseEvent * event );
  void  mouseReleaseEvent ( QMouseEvent * event );    
  void  wheelEvent ( QWheelEvent * event );

signals:

  void selectedItemsChanged();

private:
  RoundedMenu *m_roundedMenu;
  TaskTree* m_taskTree;
  QGraphicsScene* m_scene; 
  bool m_personal_menu;
  std::vector<TaskTreeItem*> m_taskTreeItems;
  std::vector<TaskTreeItem*> m_selectedItems;
	int m_dragBeginX;
	int m_dragBeginY;

};

#endif
