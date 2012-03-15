#include "Transition.hh"
#include "TaskTree.hh"


  /** Constructeurs et destructeurs */
  Transition::Transition(TaskTree* from, TaskTree* to, Type type) :
    m_from(from),
    m_to(to),
    m_type(type)
    {}

  Transition::~Transition() {}


  /** Accesseurs */
  TaskTree* Transition::getFrom() { return m_from; }

  TaskTree* Transition::getTo() { return m_to; }
  
  Transition::Type Transition::getType() { return m_type; }
