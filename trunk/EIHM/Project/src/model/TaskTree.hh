#ifndef _TASKTREE_HH_
#define _TASKTREE_HH_
#include <string>
#include <vector>

#include "Transition.hh"


class TaskTree {
  
public:

  enum Type { ABSTRACTION, APPLICATION, INTERACTION, USER };

  /** Constructeurs et destructeurs */
  TaskTree(std::string name, Type);

  TaskTree(std::string name, Type, std::vector<TaskTree*> subtrees);

  ~TaskTree();


  /** Accesseurs */
  int getSize();

  int getInteractionSize();
  
  Type getType();

  TaskTree* getSubTree(int); // rechercher le sous arbre sinon renvoit 0

  Transition* getTransition(int);  // rechercher la transition sinon renvoit 0

  /** Methodes */
  
  void addTransition(TaskTree* cible, Transition::Type type);
  
  void addTransitions(std::vector<TaskTree*> cibles, Transition::Type type);
  
  void addSubtree(TaskTree* son);
  
  void swapSubtree(int index1, int index2);
  
  void removeSubtree(int index);
  
  
  protected:

  
  private:
  std::string m_name;
  Type m_type;
  std::vector<TaskTree*> m_subtrees;
  std::vector<Transition*> m_transitions;
};

#endif
