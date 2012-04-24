#ifdef WIN32
#include "UserInterface.hh"
#else
#include "UserInterface.hh"
#endif





// /** Methodes internes */
 void UserInterface::createToolBars() {
   addToolBar(Qt::TopToolBarArea, createFileToolBar());
   addToolBar(Qt::TopToolBarArea, createEditToolBar());
   addToolBar(Qt::TopToolBarArea, createViewToolBar());
   addToolBar(Qt::LeftToolBarArea, createTaskToolBar());
 }
QToolBar* UserInterface::createFileToolBar() {
  m_fileToolBar = new QToolBar(tr("&File"), this);
  m_fileToolBar->addAction(m_openAct);
  m_fileToolBar->addAction(m_saveAct);
  return m_fileToolBar;
}

 QToolBar* UserInterface::createEditToolBar() {
   m_editToolBar = new QToolBar(tr("&Edit"), this);
   m_editToolBar->addAction(m_undoAct);
   m_editToolBar->addAction(m_redoAct);
   m_editToolBar->addAction(m_copy);
   m_editToolBar->addAction(m_paste);
   m_editToolBar->addAction(m_cut);
   return m_editToolBar;
 }

QToolBar* UserInterface::createViewToolBar() {
  m_viewToolBar = new QToolBar(tr("&View"), this);
  m_viewToolBar->addAction(m_zoomInAct);
  m_viewToolBar->addAction(m_zoomOutAct);
  m_viewToolBar->addAction(m_normalSizeAct);
  m_viewToolBar->addAction(m_fitToWindowAct);
  return m_viewToolBar;
}

// QToolBar* UserInterface::createHelpToolBar() {
//   m_helpToolBar = new QToolBar(tr("&Help"), this);
//   m_helpToolBar->addAction(m_aboutAct);
//   m_helpToolBar->addAction(m_aboutQtAct);
//   return m_helpToolBar;
// }

QToolBar* UserInterface::createTaskToolBar(){
  m_taskToolBar = new QToolBar(tr("&Tasks"), this);
  m_taskToolBar->addAction(m_addAbstractionTaskAct);
  m_taskToolBar->addAction(m_addApplicationTaskAct);
  m_taskToolBar->addAction(m_addInteractionTaskAct);
  m_taskToolBar->addAction(m_addUserTaskAct);
  m_taskToolBar->addAction(m_deleteTaskAct);
  m_taskToolBar->addAction(m_addChoiceTransitionAct);
  m_taskToolBar->addAction(m_addOrderIndependenceTransitionAct);
  m_taskToolBar->addAction(m_addInterleavingTransitionAct);
  m_taskToolBar->addAction(m_addSynchronizationTransitionAct);
  m_taskToolBar->addAction(m_addDisablingTransitionAct);
  m_taskToolBar->addAction(m_addSuspendResumeTransitionAct);
  m_taskToolBar->addAction(m_addSequentialEnablingTransitionAct);
  m_taskToolBar->addAction(m_addSequentialEnablingInfoTransitionAct);
  m_taskToolBar->addAction(m_deleteTransitionAct);
  return m_taskToolBar;
}
