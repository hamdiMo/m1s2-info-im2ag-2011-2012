#ifdef WIN32
#include "UserInterface.hh"
#include "tasktree\TaskTreeViewer.hh"
#include "tasktree\TaskTreeItem.hh"
#else
#include "UserInterface.hh"
#include "tasktree/TaskTreeViewer.hh"
#include "tasktree/TaskTreeItem.hh"
#endif



#include <QMessageBox>
#include <QFileDialog>
#include <QListIterator>
#include <QApplication>
#include <stack>

using namespace std;

std::stack<TaskTree*> sundo;
std::stack<TaskTree*> sredo;
TaskTree* copyTmp;
int indiceTasktree = 0;

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
void UserInterface::exit() {} 

bool UserInterface::canUndo(){
    return !sundo.empty();
}

bool UserInterface::canRedo() {
    return !sredo.empty();
}

void UserInterface::undo() {
    if(canUndo()){
        TaskTree* t = sundo.top();
        sundo.pop();
        sredo.push(t);
        m_displayedTree = new TaskTreeViewer(t,this);
	setCentralWidget(m_displayedTree);

    } else cout << "rien a annuler" << endl;
}
void UserInterface::redo() {
    if(canRedo()){
        TaskTree* t = sredo.top();
        sredo.pop();
        sundo.push(t);
        m_displayedTree = new TaskTreeViewer(t,this);
	setCentralWidget(m_displayedTree);
    } else cout << "rien a  refaire" << endl;
}

bool UserInterface::canCopy(){
    return (int)m_displayedTree->getSelectedItems().size() == 1;
}

void UserInterface::copy() {
    if (canCopy()){
        copyTmp = (m_displayedTree->getSelectedItems()).front()->getTaskTree();
    }
}

void ClearRedo(){
    while(!sredo.empty()) sredo.pop();
}

void UserInterface::cut() {
    if (true || canCopy()){
        TaskTree* tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
        copyTmp = new TaskTree(tmp);
        tmp->remove();

        TaskTree* root = m_displayedTree->getTaskTree();
        TaskTree* tmpUndo = new TaskTree(root);
        sundo.push(tmpUndo);
        ClearRedo();
        m_displayedTree = new TaskTreeViewer(root,this);
	setCentralWidget(m_displayedTree);
    }
}
void UserInterface::paste(){
    if (canCopy()){
        TaskTree* tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
        tmp->copyPaste(copyTmp);

        TaskTree* root = m_displayedTree->getTaskTree();
        TaskTree* tmpUndo = new TaskTree(root);
        sundo.push(tmpUndo);
        ClearRedo();
        m_displayedTree = new TaskTreeViewer(root,this);
    	setCentralWidget(m_displayedTree);
    }
}


void UserInterface::zoomIn() {}
void UserInterface::zoomOut() {}
void UserInterface::normalSize() {}
void UserInterface::fitToWindow() {}
void UserInterface::about() {
    QMessageBox::about(this, tr("About TaskTree"), tr("Morigault Thierry,Yasin  Uyar,Cadour Ulysse,Joudrier Hugo"));
}

void UserInterface::addAbstractionTask(){
    TaskTree* tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
    string name = "Task "+indiceTasktree;
    indiceTasktree++;
    tmp->addSubtree(new TaskTree(name,TaskTree::ABSTRACTION));

    TaskTree* root = m_displayedTree->getTaskTree();
    TaskTree* tmpUndo = new TaskTree(root);
    sundo.push(tmpUndo);
    ClearRedo();
    m_displayedTree = new TaskTreeViewer(root,this);
    setCentralWidget(m_displayedTree);
}

void UserInterface::addApplicationTask(){
    TaskTree* tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
    string name = "Task "+indiceTasktree;
    indiceTasktree++;
    tmp->addSubtree(new TaskTree(name,TaskTree::APPLICATION));

    TaskTree* root = m_displayedTree->getTaskTree();
    TaskTree* tmpUndo = new TaskTree(root);
    sundo.push(tmpUndo);
    ClearRedo();
    m_displayedTree = new TaskTreeViewer(root,this);
    setCentralWidget(m_displayedTree);
}

void UserInterface::addInteractionTask(){
    TaskTree* tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
    string name = "Task "+indiceTasktree;
    indiceTasktree++;
    tmp->addSubtree(new TaskTree(name,TaskTree::INTERACTION));

    TaskTree* root = m_displayedTree->getTaskTree();
    TaskTree* tmpUndo = new TaskTree(root);
    sundo.push(tmpUndo);
    ClearRedo();
    m_displayedTree = new TaskTreeViewer(root,this);
    setCentralWidget(m_displayedTree);
}
void UserInterface::addUserTask(){
    TaskTree* tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
    string name = "Task "+indiceTasktree;
    indiceTasktree++;
    tmp->addSubtree(new TaskTree(name,TaskTree::USER));

    TaskTree* root = m_displayedTree->getTaskTree();
    TaskTree* tmpUndo = new TaskTree(root);
    sundo.push(tmpUndo);
    ClearRedo();
    m_displayedTree = new TaskTreeViewer(root,this);
    setCentralWidget(m_displayedTree);
}
void UserInterface::deleteTask(){
    vector<TaskTree*> tmp;
    for(int i=0;i<(int)m_displayedTree->getSelectedItems().size();i++){
        bool isSon = false;
        for(int j = 0; j < (int)m_displayedTree->getSelectedItems().size();j++)
            isSon |= m_displayedTree->getSelectedItems()[i]->getTaskTree()->isSon(m_displayedTree->getSelectedItems()[j]->getTaskTree());
        if (!isSon) tmp.push_back(m_displayedTree->getSelectedItems()[i]->getTaskTree());
    }
    for(int i=0; i < (int)tmp.size(); i++)
        tmp[i]->remove();

    TaskTree* root = m_displayedTree->getTaskTree();
    TaskTree* tmpUndo = new TaskTree(root);
    sundo.push(tmpUndo);
    ClearRedo();
    m_displayedTree = new TaskTreeViewer(root,this);
    setCentralWidget(m_displayedTree);
}

void UserInterface::addTransition(Transition::Type type){
  TaskTree* tmp;
  TaskTree* tmp2;
  if((int)m_displayedTree->getSelectedItems().size() == 1){
    tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
    tmp->setTransitionOut(type);
  } else if ((int)m_displayedTree->getSelectedItems().size() == 2){
    
    tmp = m_displayedTree->getSelectedItems()[0]->getTaskTree();
    tmp2 = m_displayedTree->getSelectedItems()[1]->getTaskTree();
    if(((tmp->getIndex() + 1) == tmp2->getIndex()) && tmp->getParent() == tmp2->getParent()){
      tmp->setTransitionOut(type);
    } else if ((tmp->getIndex() == tmp2->getIndex() + 1) && tmp->getParent() == tmp2->getParent()){
      tmp->setTransitionIn(type);
    } else{
      tmp->setTransitionOut(type);
      tmp2->setTransitionOut(type);
    }
  } else {
    for(int i=0; i < (int)m_displayedTree->getSelectedItems().size(); i++)
      m_displayedTree->getSelectedItems()[i]->getTaskTree()->setTransitionOut(type);
  }
  TaskTree* root = m_displayedTree->getTaskTree();
  TaskTree* tmpUndo = new TaskTree(root);
  sundo.push(tmpUndo);
  ClearRedo();
  m_displayedTree = new TaskTreeViewer(root,this);
  setCentralWidget(m_displayedTree);
}

void UserInterface::deleteTransition(){
  for(int i=0; i < (int)m_displayedTree->getSelectedItems().size(); i++)
      m_displayedTree->getSelectedItems()[i]->getTaskTree()->removeTransitionOut();
}


void UserInterface::addChoiceTransition(){
  addTransition(Transition::CHOICE);
}

void UserInterface::addOrderIndependenceTransition(){
  addTransition(Transition::ORDERINDEPENDENCE);
}

void UserInterface::addInterleavingTransition(){
  addTransition(Transition::INTERLEAVING);
}

void UserInterface::addSynchronizationTransition(){
  addTransition(Transition::SYNCHRONIZATION);
}
void UserInterface::addDisablingTransition(){
  addTransition(Transition::DISABLING);
}
void UserInterface::addSuspendResumeTransition(){
  addTransition(Transition::SUSPENDRESUME);
}
void UserInterface::addSequentialEnablingTransition(){
  addTransition(Transition::SEQUENTIALENABLING);
}
void UserInterface::addSequentialEnablingInfoTransition(){
  addTransition(Transition::SEQUENTIALENABLINGINFO);
}




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
    m_addAbstractionTaskAct = new QAction(QIcon("images/abstraction.gif"),tr("Add Abstraction Task"), this);
    connect(m_addAbstractionTaskAct, SIGNAL(triggered()), this, SLOT(addAbstractionTask()));

    m_addApplicationTaskAct = new QAction(QIcon("images/abstraction.gif"),tr("Add Application Task"), this);
    connect(m_addApplicationTaskAct, SIGNAL(triggered()), this, SLOT(addApplicationTask()));

    m_addInteractionTaskAct = new QAction(QIcon("images/abstraction.gif"),tr("Add Interaction Task"), this);
    connect(m_addInteractionTaskAct, SIGNAL(triggered()), this, SLOT(addInteractionTask()));

    m_addUserTaskAct = new QAction(QIcon("images/abstraction.gif"),tr("Add User Task"), this);
    connect(m_addUserTaskAct, SIGNAL(triggered()), this, SLOT(addUserTask()));

    m_deleteTaskAct = new QAction(QIcon("images/abstraction.gif"),tr("Delete Task"), this);
    connect(m_deleteTaskAct, SIGNAL(triggered()), this, SLOT(deleteTask()));

    m_addChoiceTransitionAct = new QAction(QIcon("images/abstraction.gif"),tr("Add Choice Transition"), this);
    connect(m_addChoiceTransitionAct, SIGNAL(triggered()), this, SLOT(addChoiceTransition()));

    m_addOrderIndependenceTransitionAct = new QAction(QIcon("images/abstraction.gif"),tr("Add Order Independence Transition"), this);
    connect(m_addOrderIndependenceTransitionAct, SIGNAL(triggered()), this, SLOT(addOrderIndependenceTransition()));

    m_addInterleavingTransitionAct = new QAction(QIcon("images/abstraction.gif"),tr("Add Interleaving Transition"), this);
    connect(m_addInterleavingTransitionAct, SIGNAL(triggered()), this, SLOT(addInterleavingTransition()));

    m_addSynchronizationTransitionAct = new QAction(QIcon("images/abstraction.gif"),tr("Add Synchronization Transition"), this);
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
