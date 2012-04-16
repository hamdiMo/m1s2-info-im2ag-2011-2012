#include "Transition.hh"
#include "TaskTree.hh"
#include <string>

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
  
  std::string Transition::toString(){
    std::string s;
    switch(m_type){
      case Transition::CHOICE: 
	s = "CHOICE";
	break;
      case Transition::ORDERINDEPENDENCE :
	s = "ORDERINDEPENDENCE";
	break;
      case Transition::INTERLEAVING :
	s = "INTERLEAVING";
	break;	
      case Transition::SYNCHRONIZATION :
	s = "SYNCHRONIZATION";
	break;	
      case Transition::DISABLING :
	s = "DISABLING";
	break;	      
      case Transition::SUSPENDRESUME :
	s = "SUSPENDRESUME";
	break;	      
      case Transition::SEQUENTIALENABLING :
	s = "SEQUENTIALENABLING";
	break;      
      case Transition::SEQUENTIALENABLINGINFO :
	s = "SEQUENTIALENABLINGINFO";
	break;      
      default:;
    }
    return s;
  }