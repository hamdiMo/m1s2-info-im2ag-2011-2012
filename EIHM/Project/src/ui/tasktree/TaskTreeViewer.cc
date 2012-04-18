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
  m_scene = new QGraphicsScene(this);
  m_scene->setBackgroundBrush(QColor(128, 128, 128, 0));
  m_scene->setForegroundBrush(QColor(255, 255, 255, 0));
  
  setScene(m_scene);
  displayTaskTree(m_taskTree, 0, 0, computeWidth(m_taskTree) * 128, computeHeight(m_taskTree) * 64);
  
  // m_pictureViewer = new PictureViewer(p) ;
  // m_proxy = m_scene->addWidget(m_pictureViewer);
  // m_selectionTool = new SelectionTool(m_proxy);x
} 

TaskTreeViewer::~TaskTreeViewer() {}


/** Methodes */
void TaskTreeViewer::displayTaskTree(TaskTree* t, int xmin, int ymin, int xmax, int ymax) {
  int amplitudeX = xmax - xmin;
  int x1 = xmin + amplitudeX/2, y1 = ymin;
  QGraphicsProxyWidget* proxy = m_scene->addWidget(new QLabel(QString(t->getName().c_str())));
  proxy->setPos(x1-16, y1);
  m_scene->addRect(x1-16, y1, 32, 32);
  for (int i = 0; i < t->getSize(); i++) {
    int x2 = xmin + (2*i+1)*(amplitudeX/t->getSize())/2, y2 = y1 + 64;
    m_scene->addLine(x1, y1 + 32, x2, y2);
    displayTaskTree(t->getSubTree(i), xmin + i*(amplitudeX/t->getSize()), ymin+64, xmin + (i+1)*(amplitudeX/t->getSize()), ymax);
  }
}

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
  // std::cout << "mouse move Event" << std::endl;
}
void TaskTreeViewer::mousePressEvent ( QMouseEvent * event ){
  if (event->button()==Qt::RightButton){
    std::cout<<"rightbutton"<<"x :"<<event->x()<<"  y: " << event->y()<<std::endl;
    RoundedMenu* r = new RoundedMenu();
    QGraphicsProxyWidget* proxy3 = m_scene->addWidget(r);
    QPointF pos = mapToScene(event->x(), event->y());
    computeSceneRect(pos.x(), pos.y(), r->size().width(), r->size().height());
    proxy3->setPos(pos.x()-r->size().width()/2,pos.y()-r->size().height()/2);
  }
}
void TaskTreeViewer::mouseReleaseEvent ( QMouseEvent * event ){}
void TaskTreeViewer::wheelEvent ( QWheelEvent * event ) {}
