#include "TaskTreeViewer.hh"
#include "TaskTreeModifier.hh"
#include "RoundedMenu.hh"
#include <QLabel>
#include <QGraphicsProxyWidget>
#include "TaskTreeItem.hh"

/** Constructeurs et destructeurs */
TaskTreeViewer::TaskTreeViewer(TaskTree* taskTree) :
  m_taskTree(taskTree),
  m_taskTreeItems(0)
{
  m_roundedMenu=NULL;
  m_scene = new QGraphicsScene(this);
  m_scene->setBackgroundBrush(QColor(128, 128, 128, 0));
  m_scene->setForegroundBrush(QColor(255, 255, 255, 0));
  
  setScene(m_scene);
  createTaskTreeItems(taskTree);
  displayTaskTreeItems();
  // initTaskTreeItems();

  // displayTaskTree(m_taskTree, 0, 0, computeWidth(m_taskTree) * 128, computeHeight(m_taskTree) * 64);
  
  // m_pictureViewer = new PictureViewer(p) ;
  // m_proxy = m_scene->addWidget(m_pictureViewer);
  // m_selectionTool = new SelectionTool(m_proxy);x
} 

TaskTreeViewer::~TaskTreeViewer() {}


/** Accesseur */
std::vector<TaskTreeItem*> TaskTreeViewer::getSelectedItems() {
  return m_selectedItems;
}


/** Methodes */
TaskTreeItem* TaskTreeViewer::createTaskTreeItems(TaskTree* t) {
  int xmin = 0, xmax = 0, ymin = 0, ymax = 32;
  TaskTreeItem* item = new TaskTreeItem(t, 16, 16);
  m_taskTreeItems.push_back(item);
  if (t->getSize() > 0) {
    for (int i = 0; i < t->getSize(); i++) {
      TaskTreeItem* tmp = createTaskTreeItems(t->getSubTree(i));
      tmp->setParent(item);
      tmp->translate(xmax, ymax);
      xmax += tmp->getXMax() - tmp->getXMin();
    }
    item->setX((xmax - xmin)/2);
    item->setY(16);
    item->setXMin(xmin); item->setYMin(ymin); item->setXMax(xmax); item->setYMax(ymax);
  }
  return item;
}

void TaskTreeViewer::displayTaskTreeItems() {
  for (int i = 0 ; i < m_taskTreeItems.size() ; i++) {
    QGraphicsProxyWidget* proxy = m_scene->addWidget(m_taskTreeItems[i]);
    proxy->setPos(m_taskTreeItems[i]->getX(), m_taskTreeItems[i]->getY());
  }
}

// void TaskTreeViewer::displayTaskTree(TaskTree* t, int xmin, int ymin, int xmax, int ymax) {
//   int amplitudeX = xmax - xmin;
//   int x1 = xmin + amplitudeX/2, y1 = ymin;
//   QGraphicsProxyWidget* proxy = m_scene->addWidget(new QLabel(QString(t->getName().c_str())));
//   proxy->setPos(x1-16, y1);
//   m_scene->addRect(x1-16, y1, 32, 32);
	
//   m_taskTreeItems.push_back(new TaskTreeItem(t, x1-16, y1));
	
//   for (int i = 0; i < t->getSize(); i++) {
//     int x2 = xmin + (2*i+1)*(amplitudeX/t->getSize())/2, y2 = y1 + 64;
//     m_scene->addLine(x1, y1 + 32, x2, y2);
//     displayTaskTree(t->getSubTree(i), xmin + i*(amplitudeX/t->getSize()), ymin+64, xmin + (i+1)*(amplitudeX/t->getSize()), ymax);
//   }
// }

int TaskTreeViewer::computeWidth(TaskTree* t) {
  if (t->getSize() == 0) return 1;
  int res = 0;
  for (int i = 0; i < t->getSize(); i++) res += computeWidth(t->getSubTree(i));
  return res;
}

int TaskTreeViewer::computeHeight(TaskTree* t) {
  if (t->getSize() == 0) return 1;
  int res = 0;
  for (int i = 0; i < t->getSize(); i++) {
    int tmp = computeWidth(t->getSubTree(i));
    if (tmp > res) res = tmp;
  }
  return res;
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
}
void TaskTreeViewer::mousePressEvent ( QMouseEvent * event ){
  if (event->button()==Qt::RightButton){
    std::cout<<"rightbutton"<<"x :"<<event->x()<<"  y: " << event->y()<<std::endl;
    m_roundedMenu = new RoundedMenu(NULL,event->x(),event->y());
    QGraphicsProxyWidget* proxy3 = m_scene->addWidget(m_roundedMenu);
    QPointF pos = mapToScene(event->x(), event->y());
    computeSceneRect(pos.x(), pos.y(), m_roundedMenu->size().width(), m_roundedMenu->size().height());
    proxy3->setPos(pos.x()-m_roundedMenu->size().width()/2,pos.y()-m_roundedMenu->size().height()/2);
  }
  if (event->button() == Qt::LeftButton){
    m_dragBeginX = event->x();
    m_dragBeginY = event->y();
  }
}
void TaskTreeViewer::mouseReleaseEvent ( QMouseEvent * event ){
  // on efface la sélection
  m_selectedItems.clear();
  // clic
  if (event->x() == m_dragBeginX || event->y() == m_dragBeginY) {
    // puis on ajoute dans la nouvelle sélection tous les items dans le cadre de sélection
    for(int i=0;i<m_taskTreeItems.size();i++){
      if (m_taskTreeItems[i]->contain(event->x(), event->y())){
	m_selectedItems.push_back(m_taskTreeItems[i]);
	break;
      }
    }
  }
  // drag => cadre de sélection
  else {
    int xLeft, yTop, xRight, yBottom;
    if (m_dragBeginX > event->x()){
      xLeft = event->x();
      xRight = m_dragBeginX;
    }
    else{
      xRight = event->x();
      xLeft = m_dragBeginX;
    }
    if (m_dragBeginY > event->y()){
      yTop = event->y();
      yBottom = m_dragBeginY;
    }
    else{
      yBottom = event->y();
      yTop = m_dragBeginY;
    }
  
    for (int i=0 ; i<m_taskTreeItems.size() ; i++) {
    
      // si un des angles du cadre est dans un des items
      if (m_taskTreeItems[i]->contain(xLeft, yBottom)
	  || m_taskTreeItems[i]->contain(xRight, yBottom)
	  || m_taskTreeItems[i]->contain(xRight, yTop)
	  || m_taskTreeItems[i]->contain(xLeft, yTop)) {
	m_selectedItems.push_back(m_taskTreeItems[i]);
      } // sinon, si une des arrêtes du cadre passe dans un item
      else if ((xLeft >= m_taskTreeItems[i]->getX()-16
		&& xLeft <= m_taskTreeItems[i]->getX()+16
		&& yBottom >= m_taskTreeItems[i]->getY()+32
		&& yTop <= m_taskTreeItems[i]->getY())
	       || (xRight >= m_taskTreeItems[i]->getX()-16 
		   && xRight <= m_taskTreeItems[i]->getX()+16 
		   && yBottom >= m_taskTreeItems[i]->getY()+32 
		   && yTop <= m_taskTreeItems[i]->getY())
	       || (yTop >= m_taskTreeItems[i]->getY()
		   && yTop <= m_taskTreeItems[i]->getY()+32
		   && xRight >= m_taskTreeItems[i]->getX()+16
		   && xLeft <= m_taskTreeItems[i]->getX()-16)
	       || (yBottom >= m_taskTreeItems[i]->getY()
		   && yBottom <= m_taskTreeItems[i]->getY()+32
		   && xRight >= m_taskTreeItems[i]->getX()+16
		   && xLeft <= m_taskTreeItems[i]->getX()-16)) {
	m_selectedItems.push_back(m_taskTreeItems[i]);
      }
    }
  
    selectedItemsChanged();
  }
}

void TaskTreeViewer::wheelEvent ( QWheelEvent * event ) {}
