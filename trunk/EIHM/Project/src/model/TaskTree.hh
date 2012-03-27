#ifndef _TASKTREE_HH_
#define _TASKTREE_HH_
#include <string>
#include <vector>
#include <iostream>

#include "Transition.hh"


class TaskTree {
  
public:

  enum Type { ABSTRACTION, APPLICATION, INTERACTION, USER };

  /** Constructeurs et destructeurs */
  TaskTree(std::string name, Type);

  TaskTree(std::string name, Type, std::vector<TaskTree*> subtrees);

  ~TaskTree();


  /** Accesseurs */
  int getIndex();
  
  int getSize();
  
  Type getType();
  
  std::string getName();

  TaskTree* getSubTree(int); // rechercher le sous arbre sinon renvoit 0

  Transition* getTransitionIn();  // rechercher la transition sinon renvoit 0

  Transition* getTransitionOut();
  
  TaskTree* getParent();
  
  
  
  void setIndex(int);
  
  void setType(Type);
  
  void setName(std::string);
  
  //return -1 en cas d'erreurs
  int setTransitionIn(Transition::Type);
  
  //return -1 en cas d'erreurs
  int setTransitionIn(Transition*);
  
  //return -1 en cas d'erreurs
  int setTransitionOut(Transition::Type);
  
  //return -1 en cas d'erreurs
  int setTransitionOut(Transition*);
    
  void setParent(TaskTree*);

  void removeTransitionIn();

  void removeTransitionOut();

  void removeTransitions();
  
  /** Methodes */
    
  void addSubtree(TaskTree* son);
  
  void insertSubtree(TaskTree* son, int index);
  
  void swapSubtree(int index1, int index2);
  
  void removeSubtree(int index);
  
  void remove();
  
  protected:

  
  private:
  int m_index;
  std::string m_name;
  Type m_type;
  std::vector<TaskTree*> m_subtrees;
  Transition* m_in;
  Transition* m_out;
  TaskTree* m_parent;

};

#endif