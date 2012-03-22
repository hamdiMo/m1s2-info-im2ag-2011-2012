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
  int getSize();
  
  Type getType();

  TaskTree* getSubTree(int); // rechercher le sous arbre sinon renvoit 0

  Transition* getTransitionIn();  // rechercher la transition sinon renvoit 0

  Transition* getTransitionOut();
  
  TaskTree* getParent();
  
  void setType(Type);
  
  void setName(std::string s);
  
  
  //return -1 en cas d'erreurs
  int setTransitionIn(Transition::Type);
  
   //return -1 en cas d'erreurs
  int setTransitionOut(Transition::Type);
  
  /** Methodes */
  
  void addTransitionIn(TaskTree* cible, Transition::Type type);
    
  void addSubtree(TaskTree* son);
  
  void swapSubtree(int index1, int index2);
  
  void removeSubtree(int index);
  
  
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
