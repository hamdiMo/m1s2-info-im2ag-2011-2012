
#include "TaskTreeModifier.hh"
#include "TaskTreeViewer.hh"
#include "RoundedMenu.hh"
#include "TaskTreeItem.hh"
#include "..\UserInterface.hh"



#include <QLabel>
#include <QGraphicsProxyWidget>


/** Constructeurs et destructeurs */
TaskTreeViewer::TaskTreeViewer(TaskTree* taskTree,UserInterface* interface) :
    m_taskTree(taskTree),
    m_userInterface(interface),
    m_taskTreeItems(0),
    p_proxy_roundedMenu(0)
{
  m_roundedMenu=NULL;
  m_scene = new QGraphicsScene(this);
  m_scene->setBackgroundBrush(QColor(128, 128, 128, 0));
  m_scene->setForegroundBrush(QColor(255, 255, 255, 0));
  
  setScene(m_scene);
  m_taskTreeItemRoot = createTaskTreeItems(taskTree);
  displayTaskTreeItems();

  m_selectionTool = new SelectionTool(0, 0, 0, 0, NULL, this);
  
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
  for (int i = 0 ; i < m_taskTreeItems.size() ; i++) {
    QGraphicsProxyWidget* proxy = m_scene->addWidget(m_taskTreeItems[i]);
    proxy->setPos(m_taskTreeItems[i]->getX(), m_taskTreeItems[i]->getY());
    m_scene->addRect(m_taskTreeItems[i]->getX(), m_taskTreeItems[i]->getY(), 32, 32);
    if (m_taskTreeItems[i]->getParent() != 0) {
      m_scene->addLine(m_taskTreeItems[i]->getX()+16, m_taskTreeItems[i]->getY(),
		       m_taskTreeItems[i]->getParent()->getX()+16, m_taskTreeItems[i]->getParent()->getY()+32);
    }
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
  if (m_roundedMenu!=NULL) 
    m_roundedMenu->mouseMoveEvent(event);
  m_selectionTool->mouseMoveEvent(event);
}

void TaskTreeViewer::mousePressEvent ( QMouseEvent * event ){
  m_selectionTool->mousePressEvent(event);
  if (event->button()==Qt::RightButton){
    //std::cout<<"rightbutton"<<"x :"<<event->x()<<"  y: " << event->y()<<std::endl;
    //ajout des differentes actions...

      std::vector<QAction*> *m_vector =new std::vector<QAction*>();
      m_vector->push_back(m_userInterface->m_addAbstractionTaskAct);

      m_vector->push_back(m_userInterface->m_addApplicationTaskAct);
      m_vector->push_back(m_userInterface->m_addInteractionTaskAct);
      m_vector->push_back(m_userInterface->m_addUserTaskAct);
      m_vector->push_back(m_userInterface->m_deleteTaskAct);
      m_vector->push_back(m_userInterface->m_addChoiceTransitionAct);
    m_roundedMenu = new RoundedMenu(NULL,event->x(),event->y(),m_vector);
    p_proxy_roundedMenu = m_scene->addWidget(m_roundedMenu);
    QPointF pos = mapToScene(event->x(), event->y());
    computeSceneRect(0, 0, m_roundedMenu->size().width(), m_roundedMenu->size().height());
    computeSceneRect(pos.x(), pos.y(), m_roundedMenu->size().width(), m_roundedMenu->size().height());
    p_proxy_roundedMenu->setPos(pos.x()-m_roundedMenu->size().width()/2,pos.y()-m_roundedMenu->size().height()/2);
  }
}

void TaskTreeViewer::mouseReleaseEvent ( QMouseEvent * event ){
  m_selectionTool->mouseReleaseEvent(event);
  /*
  // on efface la s�lection
  m_selectedItems.clear();
  // clic
  if (event->x() == m_dragBeginX || event->y() == m_dragBeginY) {
    // puis on ajoute dans la nouvelle s�lection tous les items dans le cadre de s�lection
      std::vector<TaskTreeItem*>::iterator it;
      for(it = m_taskTreeItems.begin();it != m_taskTreeItems.end();++it){
        if ((*it)->contain(event->x(), event->y())){
          m_selectedItems.push_back(*it);
          break;
        }
      }
  }
  */


  /*
    std::vector<TaskTreeItem*>::iterator it;
    for(it = m_taskTreeItems.begin();it != m_taskTreeItems.end();++it){

        // si un des angles du cadre est dans un des items
        if ((*it)->contain(xLeft, yBottom)
        || (*it)->contain(xRight, yBottom)
        || (*it)->contain(xRight, yTop)
        || (*it)->contain(xLeft, yTop)) {
            m_selectedItems.push_back((*it));
        } // sinon, si une des arr�tes du cadre passe dans un item
        else if ((xLeft >= (*it)->getX()-16
          && xLeft <= (*it)->getX()+16
          && yBottom >= (*it)->getY()+32
          && yTop <= (*it)->getY())
            || (xRight >= (*it)->getX()-16
            && xRight <= (*it)->getX()+16
            && yBottom >= (*it)->getY()+32
            && yTop <= (*it)->getY())
            || (yTop >= (*it)->getY()
            && yTop <= (*it)->getY()+32
            && xRight >= (*it)->getX()+16
            && xLeft <= (*it)->getX()-16)
            || (yBottom >= (*it)->getY()
            && yBottom <= (*it)->getY()+32
            && xRight >= (*it)->getX()+16
            && xLeft <= (*it)->getX()-16)) {
            m_selectedItems.push_back((*it));
       }
    }

    selectedItemsChanged();
  }
*/

  if (m_roundedMenu!=NULL) {
    m_roundedMenu->mouseReleaseEvent(event);
    if(p_proxy_roundedMenu)
      m_scene->removeItem(p_proxy_roundedMenu);
    
  }

}

void TaskTreeViewer::wheelEvent ( QWheelEvent * event ) {}
