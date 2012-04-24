#include "UserInterface.hh"

#include <QMessageBox>
#include <QFileDialog>
#include <QListIterator>
#include <QApplication>



// /** Slots */
void UserInterface::open() {
  QFileDialog *t_fileDialog = new QFileDialog(this, windowFlags());
  t_fileDialog->setViewMode(QFileDialog::List);
  t_fileDialog->setNameFilter(tr("Fichiers TaskTree(*.tt);; Tous les Fichiers(*)"));
  t_fileDialog->setFileMode(QFileDialog::ExistingFiles);

  QStringList fileNames;
  if (t_fileDialog->exec()) fileNames = t_fileDialog->selectedFiles();
  t_fileDialog->setNameFilterDetailsVisible(true);

  QListIterator <QString> t_listIterator (fileNames);
  while (t_listIterator.hasNext()){

    /******************************* OUVERTURE***********************/
  }
}

void UserInterface::save() {
    
    /******************************GET CURRENT TREE ********************/
  //permet de definir le bon path 
  QString path = QFileDialog::getSaveFileName(this, 
					      "Enregistrer le fichier", 
					      NULL , 
						"All files *.* ;; TaskTree() ;;TaskTree *.tt" );

  // sauvegarde réelle 
   
  // tasktreeTool->saveTree(path,*m_tasktree);
    
    
}
// void UserInterface::close(QWidget* q) {
//   m_pictureManager->removePictureModifier((PictureModifier*) q);
// }
void UserInterface::exit() {
  
}

void UserInterface::undo() {}
void UserInterface::redo() {}
void UserInterface::copy() {}
void UserInterface::cut() {}
void UserInterface::paste(){}


void UserInterface::zoomIn() {}
void UserInterface::zoomOut() {}
void UserInterface::normalSize() {}
void UserInterface::fitToWindow() {}
void UserInterface::about() {
QMessageBox::about(this, tr("About TaskTree"), tr("Morigault Thierry,Yasin  Uyar,Cadour Ulysse,Joudrier Hugo"));
}
void UserInterface::addAbstractionTask(){}
void UserInterface::addApplicationTask(){}
void UserInterface::addInteractionTask(){}
void UserInterface::addUserTask(){}
void UserInterface::deleteTask(){
	for(int i=0;i<getDisplayedTree().getSelectedItems.size();i++){
		
	}
	
	
}
void UserInterface::addChoiceTransition(){}
void UserInterface::addOrderIndependenceTransition(){}
void UserInterface::addInterleavingTransition(){}
void UserInterface::addSynchronizationTransition(){}
void UserInterface::addDisablingTransition(){}
void UserInterface::addSuspendResumeTransition(){}
void UserInterface::addSequentialEnablingTransition(){}
void UserInterface::addSequentialEnablingInfoTransition(){}
void UserInterface::deleteTransition(){}



/** Methodes internes */
void UserInterface::updateActions() {
  m_openAct->setEnabled(false);
  m_saveAct->setEnabled(false);
  m_exitAct->setEnabled(false);
  
  m_undoAct->setEnabled(false);
  m_redoAct->setEnabled(false);
  m_copy->setEnabled(false);
  m_cut->setEnabled(false);
  m_paste->setEnabled(false);
  m_zoomInAct->setEnabled(false);
  m_zoomOutAct->setEnabled(false);
  m_normalSizeAct->setEnabled(false);
  m_fitToWindowAct->setEnabled(false);
  
  m_aboutAct->setEnabled(true);
  m_aboutQtAct->setEnabled(true);
  
  m_addAbstractionTaskAct->setEnabled(false);
  m_addApplicationTaskAct->setEnabled(false);
  m_addInteractionTaskAct->setEnabled(false);
  m_addUserTaskAct->setEnabled(false);
  m_deleteTaskAct->setEnabled(false);
  m_addChoiceTransitionAct->setEnabled(false);
  m_addOrderIndependenceTransitionAct->setEnabled(false);
  m_addInterleavingTransitionAct->setEnabled(false);
  m_addSynchronizationTransitionAct->setEnabled(false);
  m_addDisablingTransitionAct->setEnabled(false);
  m_addSuspendResumeTransitionAct->setEnabled(false);
  m_addSequentialEnablingTransitionAct->setEnabled(false);
  m_addSequentialEnablingInfoTransitionAct->setEnabled(false);
  m_deleteTransitionAct->setEnabled(false);
}

void UserInterface::createActions() {
  createFileAction();
  createEditAction();
  createViewAction();
  createHelpAction();
  createTaskAction();
}
void UserInterface::createFileAction() {
  m_openAct = new QAction(tr("&Open..."), this);
  m_openAct->setShortcut(tr("Ctrl+O"));
  connect(m_openAct, SIGNAL(triggered()), this, SLOT(open()));
  
  m_saveAct = new QAction(tr("&Save..."), this);
  m_saveAct->setShortcut(tr("Ctrl+S"));
  connect(m_saveAct, SIGNAL(triggered()), this, SLOT(save()));

  m_exitAct = new QAction(tr("E&xit"), this);
  m_exitAct->setShortcut(tr("Ctrl+Q"));
  connect(m_exitAct, SIGNAL(triggered()), this, SLOT(exit()));
}

void UserInterface::createEditAction() {
  m_undoAct = new QAction(tr("&Undo"), this);
  m_undoAct->setShortcut(tr("Ctrl+Z"));
  connect(m_undoAct, SIGNAL(triggered()), this, SLOT(undo()));
  
  m_redoAct = new QAction(tr("&Redo"), this);
  m_redoAct->setShortcut(tr("Ctrl+E"));
  connect(m_redoAct, SIGNAL(triggered()), this, SLOT(redo()));

  m_copy=  new QAction(tr("&Copy"), this);
  m_copy->setShortcut(tr("Ctrl+C"));
 
  connect(m_copy, SIGNAL(triggered()), this, SLOT(copy()));

  m_paste=  new QAction(tr("&Paste"), this);
  m_paste->setShortcut(tr("Ctrl+V"));
  connect(m_paste, SIGNAL(triggered()), this, SLOT(paste()));

  m_cut= new QAction(tr("&Cut"), this);
  m_cut->setShortcut(tr("Ctrl+X"));
  connect(m_cut, SIGNAL(triggered()), this, SLOT(cut()));
  
  

}

void UserInterface::createViewAction() {
  m_zoomInAct = new QAction(tr("Zoom &In"), this);
  m_zoomInAct->setShortcut(tr("Ctrl++"));
  m_zoomInAct->setEnabled(false);
  connect(m_zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
  
  m_zoomOutAct = new QAction(tr("Zoom &Out"), this);
  m_zoomOutAct->setShortcut(tr("Ctrl+-"));
  m_zoomOutAct->setEnabled(false);
  connect(m_zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
  
  m_normalSizeAct = new QAction(tr("&Normal Size"), this);
  m_normalSizeAct->setEnabled(false);
  connect(m_normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));
  
  m_fitToWindowAct = new QAction(tr("&Fit to Window"), this);
  m_fitToWindowAct->setEnabled(false);
  connect(m_fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow())); 
}

void UserInterface::createHelpAction() {
  m_aboutAct = new QAction(tr("&About"), this);
  connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(about()));
  
  m_aboutQtAct = new QAction(tr("About &Qt"), this);
  connect(m_aboutQtAct, SIGNAL(triggered()),m_QApplication, SLOT(aboutQt()));
}

void UserInterface::createTaskAction(){
  m_addAbstractionTaskAct = new QAction(tr("Add Abstraction Task"), this);
  connect(m_addAbstractionTaskAct, SIGNAL(triggered()), this, SLOT(addAbstractionTask()));
  
  m_addApplicationTaskAct = new QAction(tr("Add Application Task"), this);
  connect(m_addApplicationTaskAct, SIGNAL(triggered()), this, SLOT(addApplicationTask()));
  
  m_addInteractionTaskAct = new QAction(tr("Add Interaction Task"), this);
  connect(m_addInteractionTaskAct, SIGNAL(triggered()), this, SLOT(addInteractionTask()));
  
  m_addUserTaskAct = new QAction(tr("Add User Task"), this);
  connect(m_addUserTaskAct, SIGNAL(triggered()), this, SLOT(addUserTask()));
  
  m_deleteTaskAct = new QAction(tr("Delete Task"), this);
  connect(m_deleteTaskAct, SIGNAL(triggered()), this, SLOT(deleteTask()));
  
  m_addChoiceTransitionAct = new QAction(tr("Add Choice Transition"), this);
  connect(m_addChoiceTransitionAct, SIGNAL(triggered()), this, SLOT(addChoiceTransition()));
  
  m_addOrderIndependenceTransitionAct = new QAction(tr("Add Order Independence Transition"), this);
  connect(m_addOrderIndependenceTransitionAct, SIGNAL(triggered()), this, SLOT(addOrderIndependenceTransition()));
  
  m_addInterleavingTransitionAct = new QAction(tr("Add Interleaving Transition"), this);
  connect(m_addInterleavingTransitionAct, SIGNAL(triggered()), this, SLOT(addInterleavingTransition()));
  
  m_addSynchronizationTransitionAct = new QAction(tr("Add Synchronization Transition"), this);
  connect(m_addSynchronizationTransitionAct, SIGNAL(triggered()), this, SLOT(addSynchronizationTransition()));
  
  m_addDisablingTransitionAct = new QAction(tr("Add Disabling Transition"), this);
  connect(m_addDisablingTransitionAct, SIGNAL(triggered()), this, SLOT(addDisablingTransition()));
  
  m_addSuspendResumeTransitionAct = new QAction(tr("Add Suspend Resume Transition"), this);
  connect(m_addSuspendResumeTransitionAct, SIGNAL(triggered()), this, SLOT(addSuspendResumeTransition()));
  
  m_addSequentialEnablingTransitionAct = new QAction(tr("Add Sequential Enabling Transition"), this);
  connect(m_addSequentialEnablingTransitionAct, SIGNAL(triggered()), this, SLOT(addSequentialEnablingTransition()));
  
  m_addSequentialEnablingInfoTransitionAct = new QAction(tr("Add Sequential Enabling Info Transition"), this);
  connect(m_addSequentialEnablingInfoTransitionAct, SIGNAL(triggered()), this, SLOT(addSequentialEnablingInfoTransition()));
  
  m_deleteTransitionAct = new QAction(tr("Delete Transition"), this);
  connect(m_deleteTransitionAct, SIGNAL(triggered()), this, SLOT(deleteTransition()));
}