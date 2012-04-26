#ifdef WIN32
#include "UserInterface.hh"
#else
#include "UserInterface.hh"
#endif


#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>


// /** Methodes internes */
 void UserInterface::createToolBars() {
   addToolBar(Qt::TopToolBarArea, createFileToolBar());
   addToolBar(Qt::TopToolBarArea, createEditToolBar());
   addToolBar(Qt::TopToolBarArea, createViewToolBar()); 
   addDockWidget(Qt::BottomDockWidgetArea,createTaskToolBar(),Qt::Horizontal);
  
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


QDockWidget* UserInterface::createTaskToolBar(){
  QGroupBox* dockbottom= new QGroupBox();
  QHBoxLayout* m_fulllayout = new QHBoxLayout;
  dockbottom->setLayout(m_fulllayout);
  
 
  
  QGroupBox* t_groupBox = new QGroupBox(tr("Edition des noeuds"));
  QVBoxLayout* t_layout = new QVBoxLayout();
  m_taskToolBar = new QToolBar(tr("&View"), this);
  m_taskToolBar->setFloatable(false);
  m_taskToolBar->addAction(m_addAbstractionTaskAct);
  m_taskToolBar->addAction(m_addApplicationTaskAct);
  m_taskToolBar->addAction(m_addInteractionTaskAct);
  m_taskToolBar->addAction(m_addUserTaskAct);
  
  t_layout->addWidget(m_taskToolBar);
  t_groupBox->setLayout(t_layout);
  

  QGroupBox* t_groupBox2 = new QGroupBox(tr("Edition des transitions"));
  QHBoxLayout* t_layout2 = new QHBoxLayout();
  QToolBar* m_taskToolBar2 = new QToolBar(tr("&view"), this);
  m_taskToolBar2->addAction(m_addChoiceTransitionAct);
  m_taskToolBar2->addAction(m_addOrderIndependenceTransitionAct);
  m_taskToolBar2->addAction(m_addInterleavingTransitionAct);
  m_taskToolBar2->addAction(m_addSynchronizationTransitionAct);
  m_taskToolBar2->addAction(m_addDisablingTransitionAct);
  m_taskToolBar2->addAction(m_addSuspendResumeTransitionAct);
  m_taskToolBar2->addAction(m_addSequentialEnablingTransitionAct);
  m_taskToolBar2->addAction(m_addSequentialEnablingInfoTransitionAct);


 t_layout2->addWidget(m_taskToolBar2);
 t_groupBox2->setLayout(t_layout2);

 QGroupBox* t_groupBox3 = new QGroupBox(tr("Suppression noeud ou transition"));
  QHBoxLayout* t_layout3 = new QHBoxLayout();
  QToolBar* m_taskToolBar3 = new QToolBar(tr("&view"), this);
 

  m_taskToolBar3->addAction(m_deleteTaskAct);  
 //  m_taskToolBar->addAction(m_deleteTransitionAct);
   t_layout3->addWidget(m_taskToolBar3);
 t_groupBox3->setLayout(t_layout3);
 
  
 m_fulllayout->addWidget(t_groupBox);
 m_fulllayout->addWidget(t_groupBox2);
 m_fulllayout->addWidget(t_groupBox3);
 QDockWidget* dockWidget = new QDockWidget(dockbottom->accessibleName());

 dockWidget->setFloating(false);
 dockWidget->setTitleBarWidget(NULL); 


 dockWidget->setWidget(dockbottom);
 dockbottom->setMaximumSize(6000,100);
 
 return dockWidget;
}
