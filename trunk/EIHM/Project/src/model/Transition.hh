#ifndef _TRANSITION_HH_
#define _TRANSITION_HH_
#include <string>

class TaskTree;

class Transition {
  
public:

  enum Type { CHOICE, ORDERINDEPENDENCE, INTERLEAVING, SYNCHRONIZATION, DISABLING, SUSPENDRESUME, SEQUENTIALENABLING, SEQUENTIALENABLINGINFO };

  /** Constructeurs et destructeurs */
  Transition(TaskTree* from, TaskTree* to, Type type);
  

  ~Transition();


  /** Accesseurs */
  TaskTree* getFrom();

  TaskTree* getTo();
  
  Type getType();

  void setType(Type type);

  std::string getPathIcone();
  
  std::string toString();
  protected:

  
  private:
  Type m_type;
  TaskTree* m_from;
  TaskTree* m_to;
  std::string m_pathIcone;
};

#endif
