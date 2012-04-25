#ifdef WIN32
#include "UserInterface.hh"
#include "..\model\TaskTree.hh"
#include "tasktree\TaskTreeModifier.hh"
#include "tasktree\TaskTreeViewer.hh"
#else
#include "UserInterface.hh"
#include "TaskTree.hh"
#include "TaskTreeModifier.hh"
#include "TaskTreeViewer.hh"
#endif





using namespace std;

/** Constructeurs et Destructeurs */
UserInterface::UserInterface(QApplication* qapplication,QClipboard* clipboard) :
  m_QApplication(qapplication){ 
  m_clipboard = clipboard;
  createActions();
  createMenuBar();
  createToolBoxDocks();
  createToolBars();

  TaskTree::Type type = TaskTree::USER;
  TaskTree* t = new TaskTree("1", type);
  TaskTree* t2 = new TaskTree("2", type);
  TaskTree* t3 = new TaskTree("3", type);
  TaskTree* t4 = new TaskTree("4", type);
  TaskTree* t5 = new TaskTree("5", type);
  TaskTree* t6 = new TaskTree("6", type);
  TaskTree* t7 = new TaskTree("7", type);
  TaskTree* t8 = new TaskTree("8", type);
  TaskTree* t9 = new TaskTree("9", type);
  TaskTree* t10 = new TaskTree("10", type);  
  TaskTree* t11 = new TaskTree("11", type);
  TaskTree* t12 = new TaskTree("12", type);
  TaskTree* t13 = new TaskTree("13", type);
  
  t->addSubtree(t2);
  t->addSubtree(t3);
  t->addSubtree(t12);
  t->addSubtree(t13);
  
  t2->addSubtree(t4);
  t2->addSubtree(t5);
  t2->addSubtree(t6);
  
  t5->addSubtree(t8);
  
  t3->addSubtree(t7);

  t7->addSubtree(t9);

  t9->addSubtree(t10);
  t9->addSubtree(t11);
  
  TaskTreeViewer* m_taskTreeViewer = new TaskTreeViewer(t,this);
  m_displayedTree = m_taskTreeViewer;
  // TaskTreeModifier* m_taskTreeModifier=new TaskTreeModifier();
  //m_viewTabWidget = createTabWidget();
  // m_pictureManager = new PictureManager(this);
  // setCentralWidget((QTabWidget*)m_taskTreeViewer);

  setCentralWidget(m_taskTreeViewer);
  m_infoBox=new QLabel("");
  setWindowTitle(tr("Task Tree Creator"));
  resize(1024, 768);
  update();
  this->statusBar()->showMessage("ready");
 
  
}
    
UserInterface::~UserInterface() {
 
}
// TabWidget* tabWidget = new TabWidget(this);
  // tabWidget->addTab((TabPanel*)m_pictureManager);
  // QObject::connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(resetEditionTool(int)));
  // return tabWidget;
// }
  
TaskTreeViewer* UserInterface::getDisplayedTree() {
  return m_displayedTree;
}

QDockWidget* UserInterface::createDockWidget(QWidget* widget) {
  QDockWidget* dockWidget = new QDockWidget(widget->accessibleName());
  dockWidget->setWidget(widget);
  return dockWidget;
}



void UserInterface::print(QString string){
  statusBar()->showMessage(string, 10000);
}
