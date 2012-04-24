#include <QApplication>
#include <QPixmap>

#ifdef WIN32
#include "ui\UserInterface.hh"
#include "model\TaskTree.hh"
#else
#include "ui/UserInterface.hh"
#include "model/TaskTree.hh"
#endif


using namespace std;
int main(int argc, char **argv) {
  QApplication application(argc, argv);
  // application.setWindowIcon(QPixmap("Icon/Logo.png"));
  QClipboard* m_clipboard= QApplication::clipboard();
  UserInterface userInterface(&application ,m_clipboard );
  userInterface.show();
  
  
  
  return application.exec();
}

//NE PAS SUPPRIMER SVP
// //NE PAS SUPPRIMER SVP
//   TaskTree::Type type = TaskTree::USER;
//   TaskTree* t = new TaskTree("coulou", type);
//   TaskTree* t2 = new TaskTree("coulou2", type);
//   TaskTree* t3 = new TaskTree("coulou3", type);
//   TaskTree* t4 = new TaskTree("coulou4", type);
//   TaskTree* t5 = new TaskTree("coulou5", type);
//   TaskTree* t6 = new TaskTree("coulou6", type);
//   TaskTree* t7 = new TaskTree("coulou7", type);
//   TaskTree* t8 = new TaskTree("coulou8", type);
//   TaskTree* t9 = new TaskTree("coulou9", type);
//   TaskTree* t10 = new TaskTree("coulou10", type);  
//   TaskTree* t11 = new TaskTree("coulou11", type);
//   TaskTree* t12 = new TaskTree("coulou12", type);
//   TaskTree* t13 = new TaskTree("coulou13", type);
//   
//   //Transition* tr = new Transition(t2,t3, Transition::CHOICE);
// 
//   t->addSubtree(t2);
//   t->addSubtree(t3);
//   t->addSubtree(t12);
//   t->addSubtree(t13);
//   
//   t2->addSubtree(t4);
//   t2->addSubtree(t5);
//   t2->addSubtree(t6);
//   
//   t5->addSubtree(t8);
//   
//   t3->addSubtree(t7);
//   t7->addSubtree(t9);
//   t9->addSubtree(t10);
//   t9->addSubtree(t11);
//   
//   if(t5->setTransitionOut(Transition::CHOICE) == -1)
//     cout << "err" <<endl;
//   if(t11->setTransitionIn(Transition::ORDERINDEPENDENCE) == -1)
//     cout << "err" <<endl;
//   if(t13->setTransitionIn(Transition::CHOICE) == -1)
//     cout << "err" <<endl;  
//   if(t4->setTransitionOut(Transition::DISABLING) == -1)
//     cout << "err" <<endl;
//   t->printTree();
//   //TaskTree* tbis = new TaskTree(t);
//   //tbis->printSubTree();
//   //tbis->printTree();
//   
//   t10->cutPaste(t2);
//   t->printTree();
//   
//   t->removeSubtree(0);
//   t->printTree();
