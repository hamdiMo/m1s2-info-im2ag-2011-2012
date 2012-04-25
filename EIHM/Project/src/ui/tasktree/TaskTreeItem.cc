
#include "TaskTreeItem.hh"


/** Constructeurs */
TaskTreeItem::TaskTreeItem(TaskTree* taskTree) :
  QLabel(taskTree->getName().c_str()),
  m_parent(0),
  m_subTaskTreeItems(),
  m_taskTree(taskTree),
  m_x(32),
  m_y(32),
  m_xMin(0),
  m_yMin(0),
  m_xMax(64),
  m_yMax(64),
  m_proxy(0),
  m_itemCadre(0),
  m_itemParent(0),
  m_itemTransition(0)
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
QGraphicsProxyWidget* TaskTreeItem::getQGraphicsProxyWidget() { return m_proxy; }
QGraphicsRectItem* TaskTreeItem::getQGraphicsItemCadre() { return m_itemCadre; }
QGraphicsLineItem* TaskTreeItem::getQGraphicsItemParent() { return m_itemParent; }
QGraphicsLineItem* TaskTreeItem::getQGraphicsItemTransition() { return m_itemTransition; }

/** Mutateurs */
void TaskTreeItem::setParent(TaskTreeItem* parent) { m_parent = parent; }
void TaskTreeItem::setTaskTree(TaskTree* taskTree) { m_taskTree = taskTree; }
void TaskTreeItem::setX(int x) { m_x = x; }
void TaskTreeItem::setY(int y) { m_y = y; }
void TaskTreeItem::setXMin(int xMin) { m_xMin = xMin; }
void TaskTreeItem::setYMin(int yMin) { m_yMin = yMin; }
void TaskTreeItem::setXMax(int xMax) { m_xMax = xMax; }
void TaskTreeItem::setYMax(int yMax) { m_yMax = yMax; }
void TaskTreeItem::setQGraphicsProxyWidget(QGraphicsProxyWidget* proxy) { m_proxy = proxy; }
void TaskTreeItem::setQGraphicsItemCadre(QGraphicsRectItem* item) { m_itemCadre = item; }
void TaskTreeItem::setQGraphicsItemParent(QGraphicsLineItem* item) { m_itemParent = item; }
void TaskTreeItem::setQGraphicsItemTransition(QGraphicsLineItem* item) { m_itemTransition = item; }

/** Methods */
void TaskTreeItem::addSubTaskTreeItem(TaskTreeItem* t) {
  m_subTaskTreeItems.push_back(t);
}

void TaskTreeItem::translateNode(int x, int y) {
  if (m_xMin <= m_x + x && m_x + x <= m_xMax) {
    m_x += x;
    m_y += y;
  }
  else {
    m_x += x;
    m_y += y;
    permute(x, y);
  }
}

void TaskTreeItem::translate(int x, int y) {
  m_x += x;
  m_y += y;
  m_xMin += x;
  m_xMax += x;
  m_yMin += y;
  m_yMax += y;
  for (unsigned int i = 0; i < m_subTaskTreeItems.size(); i++) {
    m_subTaskTreeItems[i]->translate(x, y);
  }
}

void TaskTreeItem::permute(int x, int y) {
  if (m_parent && m_parent->m_subTaskTreeItems.size() > 0) {
    if (m_x < m_xMin && x < 0) {
      unsigned int index = 0;
      while (m_parent->m_subTaskTreeItems[index]->m_xMin != m_xMin) index++;
      if (index-1 < m_parent->m_subTaskTreeItems.size()) {
	TaskTreeItem* itemLeft = m_parent->m_subTaskTreeItems[index-1];
	itemLeft->translate(m_xMax - m_xMin, 0);
	translate(itemLeft->m_xMin - itemLeft->m_xMax, 0);
	m_x -= itemLeft->m_xMin - itemLeft->m_xMax;
	m_parent->m_subTaskTreeItems[index-1] = this;
	m_parent->m_subTaskTreeItems[index] = itemLeft;
      }
    }
    else if (m_x > m_xMax && x > 0) {
      unsigned int index = 0;
      while (m_parent->m_subTaskTreeItems[index]->m_xMin != m_xMin) index++;
      if (index+1 < m_parent->m_subTaskTreeItems.size()) {
	TaskTreeItem* itemRight = m_parent->m_subTaskTreeItems[index+1];
	itemRight->translate(m_xMin - m_xMax, 0);
	translate(itemRight->m_xMax - itemRight->m_xMin, 0);
	m_x -= itemRight->m_xMax - itemRight->m_xMin;
	m_parent->m_subTaskTreeItems[index+1] = this;
	m_parent->m_subTaskTreeItems[index] = itemRight;
      }
    }
  }
}

bool TaskTreeItem::contain(int x, int y) {
  return x >= m_x && x <= m_x+32 && y >= m_y && y <= m_y+32;
}
