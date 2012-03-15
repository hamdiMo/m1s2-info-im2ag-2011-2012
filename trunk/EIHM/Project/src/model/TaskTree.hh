#ifndef _TASKTREE_HH_
#define _TASKTREE_HH_

class TaskTree {

private:

  Type m_type;
  std::string m_name;
  std::vector<TaskTree*> m_subtrees;
  std::vector<Transition*> m_transitions;
  
protected:

public:

  enum Type { ABSTRACTION, APPLICATION, INTERACTION, USER };

  /** Constructeurs et destructeurs */
  TaskTree(std::string name, Type type) :
    m_name(name),
    m_type(type)
    m_subtrees(10),
    m_transition(2)
  {}

  TaskTree(std::string name, Type type, std::vector<TaskTree*> subtrees) :
    m_name(name),
    m_type(type),
    m_subtrees(10),
    m_transition(2)
  {
    // faire la copie
  }

  ~TaskTree() {}


  /** Accesseurs */
  int getSize() { return m_subtrees.size(); }

  Type getType() { return m_type; }

  TaskTree* getSubTree(int index) {} // rechercher le sous arbre sinon renvoit 0

  Transition* getTransition(int index) {}  // rechercher la transition sinon renvoit 0

};

#endif
