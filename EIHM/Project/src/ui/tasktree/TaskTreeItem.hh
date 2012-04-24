#ifndef _TASK_TREE_ITEM_
#define _TASK_TREE_ITEM_


#include <QLabel>
#include "TaskTree.hh"

class TaskTreeItem : public QLabel { Q_OBJECT

public:

  /** Constructeurs */
  TaskTreeItem(TaskTree*, int, int);
  
  /** Accesseurs */
  TaskTreeItem* getParent();
  TaskTree* getTaskTree();
  int getX();
  int getY();
  // int getXMin();
  // int getYMin();
  // int getXMax();
  // int getYMax();

  /** Mutateurs */
  void setParent(TaskTreeItem*);
  void setTaskTree(TaskTree*);
  void setX(int);
  void setY(int);
  // void setXMin(int);
  // void setYMin(int);
  // void setXMax(int);
  // void setYMax(int);
	
  /** Predicats */
  bool contain(int x, int y);

private:

  TaskTreeItem* m_parent;
  TaskTree* m_taskTree;
  int m_x, m_y;
  // int m_xMin, m_yMin, m_xMax, m_yMax;

};

#endif
