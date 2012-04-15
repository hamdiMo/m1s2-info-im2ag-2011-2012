#include "TaskTreeViewer.hh"
#include "TaskTreeModifier.hh"
#include "RoundedMenu.hh"
#include <QLabel>
#include <QGraphicsProxyWidget>

/** Constructeurs et destructeurs */
TaskTreeViewer::TaskTreeViewer() 
{
  m_scene = new QGraphicsScene(this);
  m_scene->setBackgroundBrush(QColor(128, 128, 128, 0));
  m_scene->setForegroundBrush(QColor(255, 255, 255, 0));
  setScene(m_scene);
  
  QGraphicsProxyWidget* proxy1 = m_scene->addWidget(new QLabel(tr("Task Tree Display1")));
  QGraphicsProxyWidget* proxy2 = m_scene->addWidget(new QLabel(tr("Task Tree Display2")));
  proxy1->setPos(-20, -20);
  proxy2->setPos(20, 20);
  // m_pictureViewer = new PictureViewer(p) ;
  // m_proxy = m_scene->addWidget(m_pictureViewer);
  // m_selectionTool = new SelectionTool(m_proxy);x
} 

TaskTreeViewer::~TaskTreeViewer() {}


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
    RoundedMenu* r =new RoundedMenu();
    QGraphicsProxyWidget* proxy3 = m_scene->addWidget(r);
    proxy3->setPos(event->x()-r->size().width()/2,event->y()-r->size().height()/2);
  }
}
void TaskTreeViewer::mouseReleaseEvent ( QMouseEvent * event ){}
void TaskTreeViewer::wheelEvent ( QWheelEvent * event ) {}
