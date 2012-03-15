#ifndef _TRANSITION_HH_
#define _TRANSITION_HH_

class TaskTree;

class Transition {
  
public:

  enum Type { T1, T2 };

  /** Constructeurs et destructeurs */
  Transition(TaskTree* from, TaskTree* to, Type type);

  ~Transition();


  /** Accesseurs */
  TaskTree* getFrom();

  TaskTree* getTo();
  
  Type getType();

  
  protected:

  
  private:
  Type m_type;
  TaskTree* m_from;
  TaskTree* m_to;
};

#endif
