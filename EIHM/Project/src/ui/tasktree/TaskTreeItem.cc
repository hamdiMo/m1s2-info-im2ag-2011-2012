#include "TaskTreeItem.hh"

/** Constructeurs */
TaskTreeItem::TaskTreeItem(TaskTree* taskTree, int x, int y) :
  QLabel(taskTree->getName().c_str()),
  m_taskTree(taskTree),
  m_x(x),
  m_y(y)
{}
  
/** Accesseurs */
TaskTree* TaskTreeItem::getTaskTree() { return m_taskTree; }
int TaskTreeItem::getX() { return m_x; }
int TaskTreeItem::getY() { return m_y; }
// int getXMin();
// int getYMin();
// int getXMax();
// int getYMax();

/** Mutateurs */
void TaskTreeItem::setTaskTree(TaskTree* taskTree) { m_taskTree = taskTree; }
void TaskTreeItem::setX(int x) { m_x = x; }
void TaskTreeItem::setY(int y) { m_y = y; }
// void setXMin(int);
// void setYMin(int);
// void setXMax(int);
// void setYMax(int);


/** Methods */
bool TaskTreeItem::isPointInside(int x, int y){
	if (x >= m_x-16 && x <= m_x+16 && y >= m_y && y <= m_y+32)
		return true;
}