#ifndef _TASKTREE_HH_
#define _TASKTREE_HH_
#include <string>
#include <vector>
#include <iostream>

#ifdef WIN32
#include "Transition.hh"
#else
#include "Transition.hh"
#endif


class TaskTree {
  
public:

  enum Type { ABSTRACTION, APPLICATION, INTERACTION, USER };

  /** Constructeurs et destructeurs */
  TaskTree(std::string name, Type);

  TaskTree(std::string name, Type, std::vector<TaskTree*> subtrees);
  
  TaskTree(TaskTree*);

  ~TaskTree();


  /** Accesseurs */
  int getIndex();
  
  int getSize();
  
  Type getType();
  
  std::string getName();

  TaskTree* getSubTree(int); // rechercher le sous arbre sinon renvoit 0

  std::vector<TaskTree*> getSubTrees();
  
  Transition* getTransitionIn();  // rechercher la transition sinon renvoit 0

  Transition* getTransitionOut();
  
  TaskTree* getParent();
  
  
  
  void setIndex(int);
  
  void setType(Type);
  
  void setName(std::string);
  
  
  
  /* ATTENTION pour l'affectation des transtions, 
   * les méthodes prenant en paramètre une transition, la Out 
   * ne met pas �  jour la In du voisin
   * les méthodes prenant en paramètre un type, la out met �  jour celle du voisin
   */
  
  //return -1 en cas d'erreurs
  int setTransitionIn(Transition::Type);
  
  //return -1 en cas d'erreurs 
  int setTransitionIn(Transition*);
  
  //return -1 en cas d'erreurs
  int setTransitionOut(Transition::Type);
  
  //return -1 en cas d'erreurs
  int setTransitionOut(Transition*);
    
  
  
  /********************************************************************/
  void setParent(TaskTree*);

  void removeTransitionIn();

  void removeTransitionOut();

  void removeTransitions();
  
  /** Methodes */
    
  void addSubtree(TaskTree* son);
  
  void insertSubtree(TaskTree* son, int index);
  
  void swapSubtree(int index1, int index2);
 
  void remove();
  
  void removeSubtree(int index);
  
  void removeSubtree();
  
  std::vector<TaskTree*> getLevel(TaskTree* t, int level);
  
  void getLevelTemp(TaskTree* t, int level, std::vector<std::vector<TaskTree*> >* vect);
  
  void rec(TaskTree*, int, int, std::vector<std::vector <TaskTree*> >*);
  
  
  void copyPaste(TaskTree* t);
  
  void cutPaste(TaskTree* t);
 
  void printSubTree();
  
  void printTree();
  
  bool isSon(TaskTree* parent);
   
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
