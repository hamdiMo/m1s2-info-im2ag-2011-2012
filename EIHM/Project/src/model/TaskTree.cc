#include "TaskTree.hh"
#include <string>

  /** Constructeurs et destructeurs */
  TaskTree::TaskTree(std::string name, Type type) :
    m_index(-1),
    m_name(name),
    m_type(type),
    m_subtrees(10),
    m_in(0),
    m_out(0),
    m_parent(0)
  {}

  TaskTree::TaskTree(std::string name, Type type, std::vector<TaskTree*> subtrees) :
    m_index(-1),
    m_name(name),
    m_type(type),
    m_subtrees(10),
    m_in(0),
    m_out(0),
    m_parent(0)
  {
    for(int i=0; i < (int)subtrees.size(); i++) m_subtrees.push_back(subtrees[i]);
  }

  TaskTree::~TaskTree() {}


  /** Accesseurs */
  int TaskTree::getSize() { return m_subtrees.size(); }

  TaskTree::Type TaskTree::getType() { return m_type; }

  TaskTree* TaskTree::getSubTree(int index) {
    if ( index >= 0 && index < (int)m_subtrees.size()) return m_subtrees[index];
    else return 0; // gestion d'erreur à mettre en place    
  } // rechercher le sous arbre sinon renvoit 0

  Transition* TaskTree::getTransitionIn() {  
    return m_in;
  }  

  Transition* TaskTree::getTransitionOut() {  
    return m_out;
  }  
  
  TaskTree* TaskTree::getParent(){
    return m_parent;
  }
  
  void TaskTree::setType(TaskTree::Type type){
    m_type = type;
  }
  
  void TaskTree::setName(std::string name){
    m_name = name;
  }
  
  
  /** Methodes */
  void TaskTree::addTransitionIn(TaskTree* cible, Transition::Type type){
//     m_transitions.push_back(new Transition(this, cible, type));
  }
  
  
  void TaskTree::addSubtree(TaskTree* son){
    
    m_subtrees.push_back(son);
  }
  
  void TaskTree::swapSubtree(int id1, int id2){  
    if(id1 >= 0 && id1 < (int)m_subtrees.size() && id2 >= 0 && id2 < (int)m_subtrees.size()){
      TaskTree* tmp = m_subtrees[id1];
      m_subtrees[id1] = m_subtrees[id2];
      m_subtrees[id2] = tmp;
    } 
    else std::cout<<"index out of bounds"<< std::endl;
  }
  
  void TaskTree::removeSubtree(int index){
//     int i(m_subtrees.size());
//     if(index >= 0 && index < i){
//       for(int j = index; 
//       m_subtrees[index] = 0;
//       int size = i;
//       i = index;
//       while (i < size-1){
// 	m_subtrees[i] = m_subtrees[i+1];
// 	i++;
//       }
//       m_subtrees.pop_back();
//     } else cout << "index erroné, il doit être compris entre :" << "0 et " << i-1 << endl;
  }