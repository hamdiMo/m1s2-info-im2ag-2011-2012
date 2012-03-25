#include "Transition.hh"
#include "TaskTree.hh"


  /** Constructeurs et destructeurs */
  Transition::Transition(TaskTree* from, TaskTree* to, Type type) :
    m_type(type),
    m_from(from),
    m_to(to)
    {}

  Transition::~Transition() {}


  /** Accesseurs */
  TaskTree* Transition::getFrom() { return m_from; }

  TaskTree* Transition::getTo() { return m_to; }
  
  Transition::Type Transition::getType() { return m_type; }

  void Transition::setType(Transition::Type type){
    m_type = type;
  }