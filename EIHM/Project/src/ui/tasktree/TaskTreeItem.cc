#include "TaskTreeItem.hh"

/** Constructeurs */
TaskTreeItem::TaskTreeItem(TaskTree* taskTree, int x, int y) :
  QLabel(taskTree->getName().c_str()),
  m_taskTree(taskTree),
  m_subTaskTreeItems(),
  m_x(x),
  m_y(y),
  m_xMin(32),
  m_yMin(32),
  m_xMax(32),
  m_yMax(32)
{}
  

/** Accesseurs */
TaskTreeItem* TaskTreeItem::getParent() { return m_parent; }
TaskTree* TaskTreeItem::getTaskTree() { return m_taskTree; }
int TaskTreeItem::getX() { return m_x; }
int TaskTreeItem::getY() { return m_y; }
int TaskTreeItem::getXMin() { return m_xMin; }
int TaskTreeItem::getYMin() { return m_yMin; }
int TaskTreeItem::getXMax() { return m_xMax; }
int TaskTreeItem::getYMax() { return m_yMax; }


/** Mutateurs */
void TaskTreeItem::setParent(TaskTreeItem* parent) { m_parent = parent; }
void TaskTreeItem::setTaskTree(TaskTree* taskTree) { m_taskTree = taskTree; }
void TaskTreeItem::setX(int x) { m_x = x; }
void TaskTreeItem::setY(int y) { m_y = y; }
void TaskTreeItem::setXMin(int xMin) { m_xMin = xMin; }
void TaskTreeItem::setYMin(int yMin) { m_yMin = yMin; }
void TaskTreeItem::setXMax(int xMax) { m_xMax = xMax; }
void TaskTreeItem::setYMax(int yMax) { m_yMax = yMax; }


/** Methods */


void TaskTreeItem::translate(int x, int y) {
  m_x += x;
  m_y += y;
  m_xMin += x;
  m_xMax += x;
  m_yMin += y;
  m_yMax += y;
  for (int i = 0; i < m_subTaskTreeItems.size(); i++) {
    m_subTaskTreeItems[i]->translate(x, y);
  }
}

bool TaskTreeItem::contain(int x, int y){
	if (x >= m_x-16 && x <= m_x+16 && y >= m_y && y <= m_y+32)
		return true;
}
