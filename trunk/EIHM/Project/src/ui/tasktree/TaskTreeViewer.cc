#include "TaskTreeViewer.hh"
#include "TaskTreeModifier.hh"


TaskTreeViewer::TaskTreeViewer() 
{
} 

TaskTreeViewer::~TaskTreeViewer() {
  /* m_Scene=new QGraphicsScene(this);
  m_Scene->setBackgroundBrush(QColor(128, 128, 128, 0));
  m_Scene->setForegroundBrush(QColor(255, 255, 255, 0));
  setScene(m_Scene);
  m_pictureViewer = new PictureViewer(p) ;
  m_proxy = m_Scene->addWidget(m_pictureViewer);
  m_selectionTool = new SelectionTool(m_proxy);

  */

}



/** Public Slots **/


using namespace std;
void TaskTreeViewer::keyPressEvent ( QKeyEvent * event ){
  
}

void TaskTreeViewer::keyReleaseEvent ( QKeyEvent * event ) {

}


void TaskTreeViewer::mouseDoubleClickEvent ( QMouseEvent * event ){
 
}

void TaskTreeViewer::mouseMoveEvent ( QMouseEvent * event ){
  cout<<"mouse move Event"<<endl;
  
}

void TaskTreeViewer::mousePressEvent ( QMouseEvent * event ){

}
void TaskTreeViewer::mouseReleaseEvent ( QMouseEvent * event ){
}

void TaskTreeViewer::wheelEvent ( QWheelEvent * event ) {
}



























































// /** Methodes */
// void TaskTreeViewer::scaleImage(double scale){
//   m_qImage=m_qImage.scaled((int)m_qImage.width()*scale,(int)m_qImage.height()*scale);
//   resize(m_qImage.width(), m_qImage.height());
//   setPixmap(QPixmap::fromImage((const QImage&)(m_qImage)));
    
// }

// QImage TaskTreeViewer::getImage(){
//   return m_qImage;
// }


// double TaskTreeViewer::getScale(){
//   return m_scale;
// }
// void TaskTreeViewer::zoomIn() { 
//   double scale=m_scale+m_scaleFactor;
//   if((m_qImage.width()*m_scaleFactor)<100000
//      &&(m_qImage.height()*m_scaleFactor)<10000)
//     m_scale=scale;
//   m_width_translation=m_pictureModifier->getImage()->width()*m_scale;
//   m_height_translation=m_pictureModifier->getImage()->height()*m_scale;
// } 

// double TaskTreeViewer::getWidthTranslation(){
//   return m_width_translation;
// }

// double TaskTreeViewer::getHeightTranslation(){
//   return m_height_translation;
// }

// double TaskTreeViewer::zoomOut() { 
//   double scale=m_scale-m_scaleFactor;
//   if((m_qImage.width()*m_scaleFactor)>10 && 
//      (m_qImage.height()*m_scaleFactor)>10)
//     m_scale=scale;
//   return m_scale;
// }

// double TaskTreeViewer::normalSize(){
//   double t_scale=m_scale;
//   m_scale=1.0;
//   return 1.0/t_scale;
// }
// double TaskTreeViewer::fitToWindow(QSize size){
//   float scaleW=(float)((float)m_pictureModifier->getImage()->width()/((float)size.width()));
//   float scaleH=(float)((float)m_pictureModifier->getImage()->height()/((float)size.height())); 
//   if(scaleH>scaleW)
//     m_scale = 1/scaleH;
//   else 
//     m_scale =1 /scaleW;
//   return double(m_scale);
// }


// void TaskTreeViewer::refresh() {
//   refreshData();
//   scaleImage(m_scale);

// }


// void TaskTreeViewer::refreshData(){
//   m_qImage=m_pictureModifier->getImage()->scaled(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
//   resize(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
// }

