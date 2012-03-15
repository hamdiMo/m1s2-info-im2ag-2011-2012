#include "TaskTreeViewer.hh"
//#include "PictureModifier.hh"


TaskTreeViewer::TaskTreeViewer() 
  // m_pictureModifier(pictureModifier)
{ 
  // m_scale=1.0;
  // m_scaleFactor=0.25;
  // m_width_translation=0.0;
  // m_height_translation=0.0;
  // refreshData();
  // refresh();
} 

TaskTreeViewer::~TaskTreeViewer() {}

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

