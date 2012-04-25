
#include "TaskTreeModifier.hh"
#include "TaskTreeViewer.hh"
#include "RoundedMenu.hh"
#include "TaskTreeItem.hh"
#include "UserInterface.hh"



#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>


/** Constructeurs et destructeurs */
TaskTreeViewer::TaskTreeViewer(TaskTree* taskTree,UserInterface* interface) :
    m_taskTree(taskTree),
    m_userInterface(interface),
    m_taskTreeItems(0),
    p_proxy_roundedMenu(0),
    m_state(IDLE)
{
  m_roundedMenu=NULL;
  m_scene = new QGraphicsScene(this);
  m_scene->setBackgroundBrush(QColor(128, 128, 128, 0));
  m_scene->setForegroundBrush(QColor(255, 255, 255, 0));
  
  setScene(m_scene);
  m_taskTreeItemRoot = createTaskTreeItems(taskTree);
  displayTaskTreeItems();

  m_selectionTool = new SelectionTool(NULL, this);
  p_proxy_selectionTool = getScene()->addWidget(m_selectionTool);
  
  // m_pictureViewer = new PictureViewer(p) ;
  // m_proxy = m_scene->addWidget(m_pictureViewer);
  // m_selectionTool = new SelectionTool(m_proxy);x

} 

TaskTreeViewer::~TaskTreeViewer() {}


/** Accesseur */
std::vector<TaskTreeItem*> TaskTreeViewer::getSelectedItems() {
  return m_selectedItems;
}

TaskTree* TaskTreeViewer::getTaskTree() { return m_taskTree; }

TaskTreeItem* TaskTreeViewer::getRoot() { return m_taskTreeItemRoot; }

QGraphicsScene* TaskTreeViewer::getScene(){return m_scene;}

QGraphicsProxyWidget* TaskTreeViewer::getproxySelectionTool() {return p_proxy_selectionTool;}

std::vector<TaskTreeItem*>* TaskTreeViewer::getRefTaskTreeItems(){return &m_taskTreeItems;}

std::vector<TaskTreeItem*>* TaskTreeViewer::getRefselectedItems(){return &m_selectedItems;}


/** Methodes */
TaskTreeItem* TaskTreeViewer::createTaskTreeItems(TaskTree* t) {
  int xmin = 0, xmax = 0, ymin = 0, ymax = 64;
  TaskTreeItem* item = new TaskTreeItem(t);
  m_taskTreeItems.push_back(item);
  if (t->getSize() > 0) {
    for (int i = 0; i < t->getSize(); i++) {
      TaskTreeItem* tmp = createTaskTreeItems(t->getSubTree(i));
      tmp->setParent(item);
      item->addSubTaskTreeItem(tmp);
      tmp->translate(xmax, 64);
      xmax += tmp->getXMax() - tmp->getXMin();
      if (ymax < tmp->getYMax()) ymax = tmp->getYMax() + 64;
    }
    item->setX((xmax - xmin)/2);
    item->setY(32);
    item->setXMin(xmin); item->setYMin(ymin); item->setXMax(xmax); item->setYMax(ymax);
  }
  return item;
}

void TaskTreeViewer::displayTaskTreeItems() {
  for (unsigned int i = 0 ; i < m_taskTreeItems.size() ; i++) {
    QGraphicsProxyWidget *proxy = m_taskTreeItems[i]->getQGraphicsProxyWidget();
    if (proxy == 0) {
      proxy = m_scene->addWidget(m_taskTreeItems[i]);
      m_taskTreeItems[i]->setQGraphicsProxyWidget(proxy);
    } else {
      if (m_taskTreeItems[i]->getQGraphicsItemCadre() != 0) m_scene->removeItem(m_taskTreeItems[i]->getQGraphicsItemCadre());
      if (m_taskTreeItems[i]->getQGraphicsItemParent() != 0) m_scene->removeItem(m_taskTreeItems[i]->getQGraphicsItemParent());
      if (m_taskTreeItems[i]->getQGraphicsItemTransition() != 0) m_scene->removeItem(m_taskTreeItems[i]->getQGraphicsItemTransition());
    }
    QGraphicsRectItem *cadre = m_scene->addRect(m_taskTreeItems[i]->getX(), m_taskTreeItems[i]->getY(), 32, 32); 
    QGraphicsLineItem *parent = 0, *transition = 0;
    if (m_taskTreeItems[i]->getParent() != 0) {
      parent = m_scene->addLine(m_taskTreeItems[i]->getX()+16, m_taskTreeItems[i]->getY(),
				m_taskTreeItems[i]->getParent()->getX()+16, m_taskTreeItems[i]->getParent()->getY()+32);
    }
    proxy->setPos(m_taskTreeItems[i]->getX(), m_taskTreeItems[i]->getY());
    
    Transition* transOut = m_taskTreeItems[i]->getTaskTree()->getTransitionOut();
    if (transOut != 0) {
      TaskTree* taskTreeOut = transOut->getTo();
      for (unsigned int j = 0 ; j < m_taskTreeItems.size() ; j++) {
	if (taskTreeOut == m_taskTreeItems[j]->getTaskTree()) {
	  transition = m_scene->addLine(m_taskTreeItems[i]->getX()+32, m_taskTreeItems[i]->getY()+16,
					m_taskTreeItems[j]->getX(), m_taskTreeItems[j]->getY()+16);
	}
      }
    }
    m_taskTreeItems[i]->setQGraphicsItemCadre(cadre);
    m_taskTreeItems[i]->setQGraphicsItemParent(parent);
    m_taskTreeItems[i]->setQGraphicsItemTransition(transition);
  }
}

void TaskTreeViewer::computeSceneRect(int x, int y, int xSize, int ySize) {
  QRectF rect = m_scene->sceneRect();
  int xmin = rect.x(), ymin = rect.y();
  int xmax = xmin + rect.width(), ymax = ymin + rect.height();
  int amplitudeX = 0, amplitudeY = 0;
  if (x-xSize/2 < xmin) amplitudeX = xmin-x+xSize/2;
  if (x+xSize/2 > xmax && x+xSize/2-xmax > amplitudeX) amplitudeX = x+xSize/2-xmax;
  if (y-ySize/2 < ymin) amplitudeY = ymin-y+ySize/2;
  if (y+ySize/2 > ymax && y+ySize/2-ymax > amplitudeY) amplitudeY = y+ySize/2-ymax;
  if (amplitudeX != 0 || amplitudeY != 0) {
    xmin -= amplitudeX;
    xmax += amplitudeX;
    ymin -= amplitudeY;
    ymax += amplitudeY;
    m_scene->setSceneRect(xmin, ymin, xmax-xmin, ymax-ymin);
  }
}

/** Slots */
void TaskTreeViewer::keyPressEvent ( QKeyEvent * event ){}
void TaskTreeViewer::keyReleaseEvent ( QKeyEvent * event ) {}
void TaskTreeViewer::mouseDoubleClickEvent ( QMouseEvent * event ){}
void TaskTreeViewer::mouseMoveEvent ( QMouseEvent * event ){
  QPointF pos = mapToScene(event->x(), event->y());
  switch (m_state) {
  case IDLE:
    {}
    break;
  case SELECTION: 
    {
      if (m_selectedItems.size() > 0) {
	TaskTreeItem* item = m_selectedItems[0];
	item->translate(pos.x()-m_beginX, pos.y()-m_beginY);
	m_beginX = pos.x();
	m_beginY = pos.y();
	displayTaskTreeItems();
      }
      else m_selectionTool->mouseMoveEvent(event);
    }
    break;
  case PROPERTIES:
    {
      m_roundedMenu->mouseMoveEvent(event);
    }
    break;
  default:
    {
      
    }
    break;
  }
}

void TaskTreeViewer::mousePressEvent ( QMouseEvent * event ) {
  QPointF pos = mapToScene(event->x(), event->y());
  switch (m_state) {
  case IDLE:
    {
      m_selectedItems.clear();
      for (unsigned int i = 0; i < m_taskTreeItems.size(); i++)
	if (m_taskTreeItems[i]->contain(pos.x(), pos.y())) {
	  m_selectedItems.push_back(m_taskTreeItems[i]);
	}
      if (m_selectedItems.size() > 0) {
	if (event->button() == Qt::LeftButton) {
	  m_beginX = pos.x();
	  m_beginY = pos.y();
	  m_state = SELECTION; 
	}
	else if (event->button() == Qt::RightButton) {
	  std::vector<QAction*> *m_vector =new std::vector<QAction*>();
	  m_vector->push_back(m_userInterface->m_addAbstractionTaskAct);
	  m_vector->push_back(m_userInterface->m_addApplicationTaskAct);
	  m_vector->push_back(m_userInterface->m_addInteractionTaskAct);
	  m_vector->push_back(m_userInterface->m_addUserTaskAct);
	  m_vector->push_back(m_userInterface->m_deleteTaskAct);
	  
	  m_roundedMenu = new RoundedMenu(NULL, event->x(), event->y(), m_vector);
	  p_proxy_roundedMenu = m_scene->addWidget(m_roundedMenu);
	  computeSceneRect(0, 0, m_roundedMenu->size().width(), m_roundedMenu->size().height());
	  computeSceneRect(pos.x(), pos.y(), m_roundedMenu->size().width(), m_roundedMenu->size().height());
	  p_proxy_roundedMenu->setPos(pos.x()-m_roundedMenu->size().width()/2,pos.y()-m_roundedMenu->size().height()/2);
	  m_state = PROPERTIES;
	}
      }
      else {
	if (event->button() == Qt::LeftButton) {
	  m_selectionTool->mousePressEvent(event);
	  m_state = SELECTION; 
	}
      }
    }
    break;
  case SELECTION:
    {}
    break;
  case PROPERTIES:
    {}
    break;
  default:
    {}
    break;
  }
}

void TaskTreeViewer::clearSelection() {
  m_selectedItems.clear();
}

void TaskTreeViewer::mouseReleaseEvent ( QMouseEvent * event ){
  QPointF pos = mapToScene(event->x(), event->y());
  switch (m_state) {
  case IDLE:
    {}
    break;
  case SELECTION:
    {
      if (m_selectedItems.size() == 0) m_selectionTool->mouseReleaseEvent(event);
      m_state = IDLE;
    }
    break;
  case PROPERTIES:
    {
      m_roundedMenu->mouseReleaseEvent(event);
      if (p_proxy_roundedMenu) m_scene->removeItem(p_proxy_roundedMenu);
      m_state = IDLE;
    }
    break;
  default:
    {}
    break;
  }
}

void TaskTreeViewer::wheelEvent ( QWheelEvent * event ) {}
