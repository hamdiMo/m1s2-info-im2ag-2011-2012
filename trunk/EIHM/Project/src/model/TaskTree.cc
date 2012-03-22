#include "TaskTree.hh"
#include <string>

  /** Constructeurs et destructeurs */
  TaskTree::TaskTree(std::string name, Type type) :
    m_name(name),
    m_type(type),
    m_subtrees(10),
    m_transitions(2)
  {}

  TaskTree::TaskTree(std::string name, Type type, std::vector<TaskTree*> subtrees) :
    m_name(name),
    m_type(type),
    m_subtrees(10),
    m_transitions(2)
  {
    for(int i=0; i < (int)subtrees.size(); i++) m_subtrees.push_back(subtrees[i]);
  }

  TaskTree::~TaskTree() {}


  /** Accesseurs */
  int TaskTree::getSize() { return m_subtrees.size(); }
  
  int TaskTree::getInteractionSize() { return m_transitions.size(); }

  TaskTree::Type TaskTree::getType() { return m_type; }

  TaskTree* TaskTree::getSubTree(int index) {
    if ( index >= 0 && index < (int)m_subtrees.size()) return m_subtrees[index];
    else return 0; // gestion d'erreur à mettre en place    
  } // rechercher le sous arbre sinon renvoit 0

  Transition* TaskTree::getTransition(int index) {
    if ( index >= 0 && index < (int)m_transitions.size()) return m_transitions[index];
    else return 0; // gestion d'erreur à mettre en place    
  }  // rechercher la transition sinon renvoit 0

  void TaskTree::addTransition(TaskTree* cible, Transition::Type type){
    m_transitions.push_back(new Transition(this, cible, type));
  }
  
  void TaskTree::addTransitions(std::vector<TaskTree*> cibles, Transition::Type type){
    std::vector<TaskTree*>::iterator it;
    for ( it=cibles.begin() ; it < cibles.end(); it++ ) addTransition(*it, type);
  }
  
  void TaskTree::addSubtree(TaskTree* son){
    m_subtrees.push_back(son);
  }
  
  void TaskTree::swapSubtree(int id1, int id2){  
    if(id1 >= 0 && id1 < m_subtrees.size() && id2 >= 0 && id2 < m_subtrees.size()){
      TaskTree* tmp = m_subtrees[id1];
      m_subtrees[id1] = m_subtrees[id2];
      m_subtrees[id2] = tmp;
    } 
    else std::cout<<"index out of bounds"<< std::endl;
  }
  
  void TaskTree::removeSubtree(int index){
    int i(m_subtrees.size());
    if(index >= 0 && index < i){
      for(int j = index; 
      m_subtrees[index] = 0;
      int size = i;
      i = index;
      while (i < size-1){
	m_subtrees[i] = m_subtrees[i+1];
	i++;
      }
      m_subtrees.pop_back();
    } else cout << "index erroné, il doit être compris entre :" << "0 et " << i-1 << endl;
  }