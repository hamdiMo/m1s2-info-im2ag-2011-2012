#ifndef _TASK_TREE_ITEM_
#define _TASK_TREE_ITEM_


#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <vector>
#include <QIcon>
#ifdef WIN32
#include "..\..\model\TaskTree.hh"
#else
#include "TaskTree.hh"
#endif

#define ITEM_SIZE 32

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
  QGraphicsProxyWidget* getQGraphicsProxyWidget();
  QGraphicsRectItem* getQGraphicsItemCadre();
  QGraphicsRectItem* getQGraphicsItemSelect();
  QGraphicsLineItem* getQGraphicsItemParent();
  QGraphicsLineItem* getQGraphicsItemTransition1();
  QGraphicsLineItem* getQGraphicsItemTransition2();
  QGraphicsPixmapItem* getQGraphicsItemIconeTransition();


  /** Mutateurs */
  void setParent(TaskTreeItem*);
  void setTaskTree(TaskTree*);
  void setX(int);
  void setY(int);
  void setXMin(int);
  void setYMin(int);
  void setXMax(int);
  void setYMax(int);
  void setQGraphicsProxyWidget(QGraphicsProxyWidget*);
  void setQGraphicsItemCadre(QGraphicsRectItem*);
  void setQGraphicsItemSelect(QGraphicsRectItem*);
  void setQGraphicsItemParent(QGraphicsLineItem*);
  void setQGraphicsItemTransition1(QGraphicsLineItem*);
  void setQGraphicsItemTransition2(QGraphicsLineItem*);
  void setQGraphicsItemIconeTransition(QGraphicsPixmapItem*);
	
  /** Predicats */
  void addSubTaskTreeItem(TaskTreeItem* t);
  void translateNode(int x, int y);
  void translate(int x, int y);
  void permute(int x, int y);
  bool contain(int x, int y);

private:

  TaskTreeItem* m_parent;
  std::vector<TaskTreeItem*> m_subTaskTreeItems;
  TaskTree* m_taskTree;
  int m_x, m_y;
  int m_xMin, m_yMin, m_xMax, m_yMax;
  QGraphicsProxyWidget *m_proxy;
  QGraphicsRectItem *m_itemCadre, *m_itemSelect;
  QGraphicsLineItem *m_itemParent, *m_itemTransition1, *m_itemTransition2;
  QGraphicsPixmapItem* m_itemIconeTransition;
};

#endif
