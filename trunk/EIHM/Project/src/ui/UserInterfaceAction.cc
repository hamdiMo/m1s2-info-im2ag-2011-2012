#ifdef WIN32
#include "UserInterface.hh"
#include "tasktree\TaskTreeViewer.hh"
#include "tasktree\TaskTreeItem.hh"
#include "toolbox\PropertyBox.hh"
#else
#include "UserInterface.hh"
#include "tasktree/TaskTreeViewer.hh"
#include "tasktree/TaskTreeItem.hh"
#include "PropertyBox.hh"
#endif



#include <QMessageBox>
#include <QFileDialog>
#include <QListIterator>
#include <QApplication>
#include <stack>

using namespace std;

std::stack<TaskTree*> sundo;
std::stack<TaskTree*> sredo;
TaskTree* copyTmp = 0;
int indiceTasktree = 0;

// /** Slots */getPropertyBox() 
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

    // sauvegarde r√©elle

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
      getPropertyBox()->getInfoBox()->setText("<font color=\"green\">Annuler</font>"); 
        TaskTree* t = sundo.top();
        sundo.pop();
        sredo.push(t);
        m_displayedTree = new TaskTreeViewer(t,this);
	setCentralWidget(m_displayedTree);

    } else {
      //getPropertyBox()->getInfoBox()->setText("Il n'y a rien a annuler");
      getPropertyBox()->getInfoBox()->setText("<font color=\"red\">Il n'y a rien a annuler</font>");
    }
}
void UserInterface::redo() {
    if(canRedo()){
      getPropertyBox()->getInfoBox()->setText("<font color=\"green\">Refaire</font>"); 
        TaskTree* t = sredo.top();
        sredo.pop();
        sundo.push(t);
        m_displayedTree = new TaskTreeViewer(t,this);
	setCentralWidget(m_displayedTree);
    } else {
      getPropertyBox()->getInfoBox()->setText("<font color=\"red\">Il n'y a rien a refaire</font>");
    }
}


bool UserInterface::canCopy(){
    return (int)m_displayedTree->getSelectedItems().size() == 1;
}

void UserInterface::copy() {
    if (canCopy()){
        copyTmp = (m_displayedTree->getSelectedItems()).front()->getTaskTree();
	getPropertyBox()->getInfoBox()->setText("<font color=\"green\">La tache a ete copiee.<br>Selectionnez une tache cible pour coller.</font>"); 
    } else getPropertyBox()->getInfoBox()->setText("<font color=\"red\">Vous ne pouvez copier qu'une tache<br>Veuillez selectionner une tache √  copier</font>");
    m_displayedTree->clearSelection();
}

void ClearRedo(){
    while(!sredo.empty()) sredo.pop();
}

void UserInterface::cut() {
    if (canCopy()){
	getPropertyBox()->getInfoBox()->setText("<font color=\"green\">La tache a ete coupee.<br>Selectionnez une tache cible pour coller.</font>"); 
        TaskTree* tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
        copyTmp = new TaskTree(tmp);
        tmp->remove();
	m_displayedTree->clearSelection();
        TaskTree* root = m_displayedTree->getTaskTree();
        TaskTree* tmpUndo = new TaskTree(root);
        sundo.push(tmpUndo);
        ClearRedo();
        m_displayedTree = new TaskTreeViewer(root,this);
	setCentralWidget(m_displayedTree);
    } else getPropertyBox()->getInfoBox()->setText("<font color=\"red\">Vous ne pouvez couper qu'une tache<br>Veuillez selectionner une tache √  couper</font>");
}
void UserInterface::paste(){
  if (copyTmp != 0){
    if (canCopy()){
      getPropertyBox()->getInfoBox()->setText("<font color=\"green\">La tache a ete collee.</font>"); 
        TaskTree* tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
        tmp->copyPaste(copyTmp);
	m_displayedTree->clearSelection();
        TaskTree* root = m_displayedTree->getTaskTree();
        TaskTree* tmpUndo = new TaskTree(root);
        sundo.push(tmpUndo);
        ClearRedo();
        m_displayedTree = new TaskTreeViewer(root,this);
    	setCentralWidget(m_displayedTree);
    } else getPropertyBox()->getInfoBox()->setText("<font color=\"red\">Veuillez selectionner une tache<br> pour sp√©cifier le lieu de collage</font>");
  } else getPropertyBox()->getInfoBox()->setText("<font color=\"green\">Pour coller, vous devez copier<br>ou couper une tache au pr√©alable</font>"); 
}


void UserInterface::zoomIn() {}
void UserInterface::zoomOut() {}
void UserInterface::normalSize() {}
void UserInterface::fitToWindow() {}
void UserInterface::about() {
    QMessageBox::about(this, tr("About TaskTree"), tr("Morigault Thierry,Yasin  Uyar,Cadour Ulysse,Joudrier Hugo"));
}

void UserInterface::addTask(TaskTree::Type type){
  if((int)m_displayedTree->getSelectedItems().size() == 1){
    getPropertyBox()->getInfoBox()->setText("<font color=\"green\">L'ajout d'une tache entraine la<br>creation d'une tache dans le sous arbre <br>de la tache selectionnee<br> un glisse/depose permet la permutation de taches.</font>");
    TaskTree* tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
    string name = "Task "+indiceTasktree;
    indiceTasktree++;
    tmp->addSubtree(new TaskTree(name,type));
    
    //m_displayedTree->clearSelection();
    TaskTree* root = m_displayedTree->getTaskTree();
    TaskTree* tmpUndo = new TaskTree(root);
    sundo.push(tmpUndo);
    ClearRedo();
    m_displayedTree = new TaskTreeViewer(root,this);
    setCentralWidget(m_displayedTree);
  } else {
    getPropertyBox()->getInfoBox()->setText("<font color=\"red\">Pour ajouter une nouvelle tache,<br> veuillez selectionner la tache parente</font>"); 
    //m_displayedTree->clearSelection();
  }
}

void UserInterface::addAbstractionTask(){//ABSTRACTION
  addTask(TaskTree::ABSTRACTION);
}

void UserInterface::addApplicationTask(){
  addTask(TaskTree::APPLICATION);
}

void UserInterface::addInteractionTask(){
    addTask(TaskTree::INTERACTION);
}
void UserInterface::addUserTask(){
  addTask(TaskTree::USER);/*
    TaskTree* tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
    string name = "Task "+indiceTasktree;
    indiceTasktree++;
    tmp->addSubtree(new TaskTree(name,TaskTree::USER));

    m_displayedTree->clearSelection();
    TaskTree* root = m_displayedTree->getTaskTree();
    TaskTree* tmpUndo = new TaskTree(root);
    sundo.push(tmpUndo);
    ClearRedo();
    m_displayedTree = new TaskTreeViewer(root,this);
    setCentralWidget(m_displayedTree);*/
}
void UserInterface::deleteTask(){
  if((int)m_displayedTree->getSelectedItems().size() > 0){
    getPropertyBox()->getInfoBox()->setText("<font color=\"green\">La supression d'une tache entraine la<br>supression des transitions et du <br>sous arbre de cette tache.</font>");
    vector<TaskTree*> tmp;
    for(int i=0;i<(int)m_displayedTree->getSelectedItems().size();i++){
        bool isSon = false;
        for(int j = 0; j < (int)m_displayedTree->getSelectedItems().size();j++)
            isSon |= m_displayedTree->getSelectedItems()[i]->getTaskTree()->isSon(m_displayedTree->getSelectedItems()[j]->getTaskTree());
        if (!isSon) tmp.push_back(m_displayedTree->getSelectedItems()[i]->getTaskTree());
    }
    for(int i=0; i < (int)tmp.size(); i++)
        tmp[i]->remove();

    m_displayedTree->clearSelection();
    TaskTree* root = m_displayedTree->getTaskTree();
    TaskTree* tmpUndo = new TaskTree(root);
    sundo.push(tmpUndo);
    ClearRedo();
    m_displayedTree = new TaskTreeViewer(root,this);
    setCentralWidget(m_displayedTree);
  } else getPropertyBox()->getInfoBox()->setText("<font color=\"red\">Pour supprimer des taches,<br> veuillez en selectionner au moins une.</font>");
}

void UserInterface::addTransition(Transition::Type type){
  TaskTree* tmp;
  TaskTree* tmp2;
  if((int)m_displayedTree->getSelectedItems().size() == 0){
    getPropertyBox()->getInfoBox()->setText("<font color=\"red\">Pour l'ajout de transitions,<br> veuillez selectionner au moins une tache.</font>");
  }else if((int)m_displayedTree->getSelectedItems().size() == 1){
    tmp = m_displayedTree->getSelectedItems().front()->getTaskTree();
    tmp->setTransitionOut(type);
      m_displayedTree->clearSelection();
  TaskTree* root = m_displayedTree->getTaskTree();
  TaskTree* tmpUndo = new TaskTree(root);
  sundo.push(tmpUndo);
  ClearRedo();
  m_displayedTree = new TaskTreeViewer(root,this);
  setCentralWidget(m_displayedTree);
  getPropertyBox()->getInfoBox()->setText("<font color=\"green\">La selection de deux taches voisines<br>ajoute la transition entre ces deux noeuds.<br>La selection de plus de deux noeuds <br>ajoute des transitions sortantes pour<br> chacuns de ces noeuds.</font>");
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
      m_displayedTree->clearSelection();
  TaskTree* root = m_displayedTree->getTaskTree();
  TaskTree* tmpUndo = new TaskTree(root);
  sundo.push(tmpUndo);
  ClearRedo();
  m_displayedTree = new TaskTreeViewer(root,this);
  setCentralWidget(m_displayedTree);
  getPropertyBox()->getInfoBox()->setText("<font color=\"green\">La selection de deux taches voisines<br>ajoute la transition entre ces deux noeuds.<br>La selection de plus de deux noeuds <br>ajoute des transitions sortantes pour<br> chacuns de ces noeuds.</font>");
  } else {
    for(int i=0; i < (int)m_displayedTree->getSelectedItems().size(); i++)
      m_displayedTree->getSelectedItems()[i]->getTaskTree()->setTransitionOut(type);
      m_displayedTree->clearSelection();
  TaskTree* root = m_displayedTree->getTaskTree();
  TaskTree* tmpUndo = new TaskTree(root);
  sundo.push(tmpUndo);
  ClearRedo();
  m_displayedTree = new TaskTreeViewer(root,this);
  setCentralWidget(m_displayedTree);
  getPropertyBox()->getInfoBox()->setText("<font color=\"green\">La selection de deux taches voisines<br>ajoute la transition entre ces deux noeuds.<br>La selection de plus de deux noeuds <br>ajoute des transitions sortantes pour<br> chacuns de ces noeuds.</font>");
  }
  
}

void UserInterface::deleteTransition(){
  if((int)m_displayedTree->getSelectedItems().size() == 0){
    getPropertyBox()->getInfoBox()->setText("<font color=\"red\">Pour supprimer des transitions sortantes,<br> veuillez selectionner au moins une tache.</font>");
  } else {
    for(int i=0; i < (int)m_displayedTree->getSelectedItems().size(); i++)
      m_displayedTree->getSelectedItems()[i]->getTaskTree()->removeTransitionOut();
    getPropertyBox()->getInfoBox()->setText("<font color=\"green\">Supression effectuee</font>");
  }
  m_displayedTree->clearSelection();
  TaskTree* root = m_displayedTree->getTaskTree();
  TaskTree* tmpUndo = new TaskTree(root);
  sundo.push(tmpUndo);
  ClearRedo();
  m_displayedTree = new TaskTreeViewer(root,this);
  setCentralWidget(m_displayedTree);
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
    m_openAct = new QAction(QIcon("images/open.png"),tr("&Open..."), this);
    m_openAct->setShortcut(tr("Ctrl+O"));
    connect(m_openAct, SIGNAL(triggered()), this, SLOT(open()));

    m_saveAct = new QAction(QIcon("images/save.png"),tr("&Save..."), this);
    m_saveAct->setShortcut(tr("Ctrl+S"));
    connect(m_saveAct, SIGNAL(triggered()), this, SLOT(save()));

    m_exitAct = new QAction(QIcon("images/exit.png"),tr("E&xit"), this);
    m_exitAct->setShortcut(tr("Ctrl+Q"));
    connect(m_exitAct, SIGNAL(triggered()), this, SLOT(exit()));
}

void UserInterface::createEditAction() {
    m_undoAct = new QAction(QIcon("images/undo.png"),tr("&Undo"), this);
    m_undoAct->setShortcut(tr("Ctrl+Z"));
    connect(m_undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    m_redoAct = new QAction(QIcon("images/redo.png"),tr("&Redo"), this);
    m_redoAct->setShortcut(tr("Ctrl+E"));
    connect(m_redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    m_copy=  new QAction(QIcon("images/copy.png"),tr("&Copy"), this);
    m_copy->setShortcut(tr("Ctrl+C"));

    connect(m_copy, SIGNAL(triggered()), this, SLOT(copy()));

    m_paste=  new QAction(QIcon("images/paste.png"),tr("&Paste"), this);
    m_paste->setShortcut(tr("Ctrl+V"));
    connect(m_paste, SIGNAL(triggered()), this, SLOT(paste()));

    m_cut= new QAction(QIcon("images/cut.png"),tr("&Cut"), this);
    m_cut->setShortcut(tr("Ctrl+X"));
    connect(m_cut, SIGNAL(triggered()), this, SLOT(cut()));



}

void UserInterface::createViewAction() {
    m_zoomInAct = new QAction(QIcon("images/zoomin.png"),tr("Zoom &In"), this);
    m_zoomInAct->setShortcut(tr("Ctrl++"));
    m_zoomInAct->setEnabled(false);
    connect(m_zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    m_zoomOutAct = new QAction(QIcon("images/zoomout.png"),tr("Zoom &Out"), this);
    m_zoomOutAct->setShortcut(tr("Ctrl+-"));
    m_zoomOutAct->setEnabled(false);
    connect(m_zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    m_normalSizeAct = new QAction(QIcon("images/normalsize.png"),tr("&Normal Size"), this);
    m_normalSizeAct->setEnabled(false);
    connect(m_normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    m_fitToWindowAct = new QAction(QIcon("images/fit.png"),tr("&Fit to Window"), this);
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
    m_addAbstractionTaskAct = new QAction(QIcon("images/abstraction.png"),tr("Add Abstraction Task"), this);
    connect(m_addAbstractionTaskAct, SIGNAL(triggered()), this, SLOT(addAbstractionTask()));

    m_addApplicationTaskAct = new QAction(QIcon("images/application.png"),tr("Add Application Task"), this);
    connect(m_addApplicationTaskAct, SIGNAL(triggered()), this, SLOT(addApplicationTask()));

    m_addInteractionTaskAct = new QAction(QIcon("images/interaction.gif"),tr("Add Interaction Task"), this);
    connect(m_addInteractionTaskAct, SIGNAL(triggered()), this, SLOT(addInteractionTask()));

    m_addUserTaskAct = new QAction(QIcon("images/user.png"),tr("Add User Task"), this);
    connect(m_addUserTaskAct, SIGNAL(triggered()), this, SLOT(addUserTask()));

    m_deleteTaskAct = new QAction(QIcon("images/delete.png"),tr("Delete Task"), this);
    connect(m_deleteTaskAct, SIGNAL(triggered()), this, SLOT(deleteTask()));

    m_addChoiceTransitionAct = new QAction(QIcon("images/choice.gif"),tr("Add Choice Transition"), this);
    connect(m_addChoiceTransitionAct, SIGNAL(triggered()), this, SLOT(addChoiceTransition()));

    m_addOrderIndependenceTransitionAct = new QAction(QIcon("images/order.gif"),tr("Add Order Independence Transition"), this);
    connect(m_addOrderIndependenceTransitionAct, SIGNAL(triggered()), this, SLOT(addOrderIndependenceTransition()));

    m_addInterleavingTransitionAct = new QAction(QIcon("images/interleave.gif"),tr("Add Interleaving Transition"), this);
    connect(m_addInterleavingTransitionAct, SIGNAL(triggered()), this, SLOT(addInterleavingTransition()));

    m_addSynchronizationTransitionAct = new QAction(QIcon("images/fullsincro.gif"),tr("Add Synchronization Transition"), this);
    connect(m_addSynchronizationTransitionAct, SIGNAL(triggered()), this, SLOT(addSynchronizationTransition()));

    m_addDisablingTransitionAct = new QAction(QIcon("images/disabling.gif"),tr("Add Disabling Transition"), this);
    connect(m_addDisablingTransitionAct, SIGNAL(triggered()), this, SLOT(addDisablingTransition()));

    m_addSuspendResumeTransitionAct = new QAction(QIcon("images/suspend.gif"),tr("Add Suspend Resume Transition"), this);
    connect(m_addSuspendResumeTransitionAct, SIGNAL(triggered()), this, SLOT(addSuspendResumeTransition()));

    m_addSequentialEnablingTransitionAct = new QAction(QIcon("images/enabling.gif"),tr("Add Sequential Enabling Transition"), this);
    connect(m_addSequentialEnablingTransitionAct, SIGNAL(triggered()), this, SLOT(addSequentialEnablingTransition()));

    m_addSequentialEnablingInfoTransitionAct = new QAction(QIcon("images/enablinginfo.gif"),tr("Add Sequential Enabling Info Transition"), this);
    connect(m_addSequentialEnablingInfoTransitionAct, SIGNAL(triggered()), this, SLOT(addSequentialEnablingInfoTransition()));

    m_deleteTransitionAct = new QAction(tr("Delete Transition"), this);
    connect(m_deleteTransitionAct, SIGNAL(triggered()), this, SLOT(deleteTransition()));
}
