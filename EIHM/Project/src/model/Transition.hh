#ifndef _TRANSITION_HH_
#define _TRANSITION_HH_

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
  
  protected:

  
  private:
  Type m_type;
  TaskTree* m_from;
  TaskTree* m_to;
};

#endif
