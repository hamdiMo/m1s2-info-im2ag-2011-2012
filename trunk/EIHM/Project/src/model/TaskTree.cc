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
    // faire la copie
  }

  TaskTree::~TaskTree() {}


  /** Accesseurs */
  int TaskTree::getSize() { return m_subtrees.size(); }
  
  int TaskTree::getInteractionSize() { return m_transitions.size(); }

  TaskTree::Type TaskTree::getType() { return m_type; }

  TaskTree* TaskTree::getSubTree(int index) {
    if ( index >= 0 && index < m_subtrees.size()) return m_subtrees[index];
    else return 0; // gestion d'erreur à mettre en place    
  } // rechercher le sous arbre sinon renvoit 0

  Transition* TaskTree::getTransition(int index) {
    if ( index >= 0 && index < m_transitions.size()) return m_transitions[index];
    else return 0; // gestion d'erreur à mettre en place    
  }  // rechercher la transition sinon renvoit 0
