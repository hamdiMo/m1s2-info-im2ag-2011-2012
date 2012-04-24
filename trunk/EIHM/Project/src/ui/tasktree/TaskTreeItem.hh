#ifndef _TASK_TREE_ITEM_
#define _TASK_TREE_ITEM_


#include <QLabel>
#include <vector>

#ifdef WIN32
#include "..\..\model\TaskTree.hh"
#else
#include "TaskTree.hh"
#endif

class TaskTreeItem : public QLabel { Q_OBJECT

public:

  /** Constructeurs */
  TaskTreeItem(TaskTree*);
  
  /** Accesseurs */
  TaskTreeItem* getParent();
  TaskTree* getTaskTree();
  int getX();
  int getY();
  int getXMin();
  int getYMin();
  int getXMax();
  int getYMax();

  /** Mutateurs */
  void setParent(TaskTreeItem*);
  void setTaskTree(TaskTree*);
  void setX(int);
  void setY(int);
  void setXMin(int);
  void setYMin(int);
  void setXMax(int);
  void setYMax(int);
	
  /** Predicats */
  void addSubTaskTreeItem(TaskTreeItem* t);
  void translate(int x, int y);
  bool contain(int x, int y);

private:

  TaskTreeItem* m_parent;
  std::vector<TaskTreeItem*> m_subTaskTreeItems;
  TaskTree* m_taskTree;
  int m_x, m_y;
  int m_xMin, m_yMin, m_xMax, m_yMax;

};

#endif
