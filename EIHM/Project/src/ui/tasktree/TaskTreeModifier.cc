#include "TaskTreeModifier.hh"

// #include "UserInterface.hh"
// #include "TracingManager.hh"
// #include "PictureViewer.hh"
// #include "Histogram.hh"
// #include "Previewer.hh"
// #include "Picture.hh"
// #include "Matrix.hh"
// #include "ToolBoxChooser.hh"
// #include "AffineOperationChooser.hh"
// #include "ConvolveOperationChooser.hh"
// #include "ColorConvertOperationChooser.hh"
// #include "PictureArea.hh"

/** Constructeurs et destructeur */
TaskTreeModifier::TaskTreeModifier() 
  // TabPanel(userInterface),
  // m_picture(picture),
  // m_image(new QImage(m_picture->getWidth(), m_picture->getHeight(), QImage::Format_ARGB32))
{
  // m_userInterface=userInterface;
  // setTabName(m_picture->getName());
  // refreshData();
  // m_pictureArea = new PictureArea(this,userInterface);
  // setWidget(m_pictureArea);
  // refresh();
}

TaskTreeModifier::~TaskTreeModifier() {}


// /** Accesseurs */
// QImage* TaskTreeModifier::getImage() { return m_image; }

// Picture* TaskTreeModifier::getPicture() { return m_picture;}

// QClipboard* TaskTreeModifier::getClipBoard(){return m_userInterface->getClipBoard();}

// PictureArea * TaskTreeModifier::getPictureArea(){return m_pictureArea;}

// /** Mutateurs */
// void TaskTreeModifier::notifyCurrent() {
//   getUserInterface()->getPreviewer()->setTaskTreeModifier(this);
//   getUserInterface()->getToolBoxChooser()->setTaskTreeModifier(this);
//   getUserInterface()->getAffineOperationChooser()->setTaskTreeModifier(this);
//   getUserInterface()->getConvolveOperationChooser()->setTaskTreeModifier(this);
//   getUserInterface()->getColorConvertOperationChooser()->setTaskTreeModifier(this);
//   getUserInterface()->getHistogram()->setTaskTreeModifier(this);
//   getUserInterface()->getTracingManager()->setTaskTreeModifier(this);
//   getUserInterface()->update();
// }


// /** Methodes */
// Picture* TaskTreeModifier::getSelectedPicture() { return getPicture(); }

// void TaskTreeModifier::refreshData() {
//   Matrix<unsigned int>* pictureData = m_picture->getData();
//   if (pictureData->getWidth() != m_image->width() || pictureData->getHeight() != m_image->height()) {
//     delete m_image;
//     m_image = new QImage(pictureData->getWidth(), pictureData->getHeight(), QImage::Format_ARGB32);
//   }
//   for (int i = 0; i < pictureData->getWidth(); i++)
//     for (int j = 0; j < pictureData->getHeight(); j++)
//       m_image->setPixel(i, j, (uint)pictureData->getValue(i, j));

// }

// void TaskTreeModifier::refresh() {
//   refreshData();
//   m_pictureArea->refresh();
//   getUserInterface()->getHistogram()->refresh();
//   getUserInterface()->getPreviewer()->refresh();
//   getUserInterface()->getTracingManager()->refresh();
//   getUserInterface()->getToolBoxChooser()->refresh();

// }

// void TaskTreeModifier::keyPressEvent(QKeyEvent* event){
//   m_pictureArea->keyPressEvent(event);
// } 

// void TaskTreeModifier::keyReleaseEvent ( QKeyEvent * event ) {
//   m_pictureArea->keyReleaseEvent(event);
// }



// void TaskTreeModifier::zoomIn(){
//   m_pictureArea->zoomIn();
//   refresh();
// }
// void TaskTreeModifier::zoomOut(){
//   m_pictureArea->zoomOut();
//   refresh();
// }  
// void TaskTreeModifier::normalSize(){
//   m_pictureArea->normalSize();
//   refresh();
// }
// void TaskTreeModifier::fitToWindow(){
//   m_pictureArea->fitToWindow();
//   refresh();
// }


// void TaskTreeModifier:: copy(){
//   m_pictureArea->copy();
// }		
// void TaskTreeModifier:: paste(){
//   m_pictureArea->paste();
// }
// void TaskTreeModifier:: cut(){
//   m_pictureArea->cut();
//   this->refresh();
// }

// void TaskTreeModifier::crop(){
//   m_pictureArea->crop();
//   this->refresh();
// }

// bool TaskTreeModifier::enableMove(){
//   m_pictureArea->enableMove();
 
//   return true;
// }
// void TaskTreeModifier::disableMove(){
//   m_pictureArea->disableMove();
// }

// bool TaskTreeModifier::enableSelection(){
//   m_pictureArea->enableSelection();
//   return true;
// }
// void TaskTreeModifier::disableSelection(){
//   m_pictureArea->disableSelection();
// }
