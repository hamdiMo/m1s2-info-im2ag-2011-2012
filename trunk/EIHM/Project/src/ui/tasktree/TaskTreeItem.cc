
#include "TaskTreeItem.hh"


/** Constructeurs */
TaskTreeItem::TaskTreeItem(TaskTree* taskTree) :
  QLabel(taskTree->getName().c_str()),
  m_parent(0),
  m_taskTree(taskTree),
  m_subTaskTreeItems(),
  m_x(32),
  m_y(32),
  m_xMin(0),
  m_yMin(0),
  m_xMax(64),
  m_yMax(64)
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
void TaskTreeItem::addSubTaskTreeItem(TaskTreeItem* t) {
  m_subTaskTreeItems.push_back(t);
}

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
    if (x >= m_x && x <= m_x+32 && y >= m_y && y <= m_y+32)
		return true;
    return false;
}
