#include "Transition.hh"
#include "TaskTree.hh"




#include <string>

  /** Constructeurs et destructeurs */
  Transition::Transition(TaskTree* from, TaskTree* to, Type type) :
    m_type(type),
    m_from(from),
    m_to(to)
    {
      switch(m_type){
      case Transition::CHOICE: 
    m_pathIcone = "images/choice.gif";
	break;
      case Transition::ORDERINDEPENDENCE :
    m_pathIcone = "images/cut.gif";
	break;
      case Transition::INTERLEAVING :
    m_pathIcone = "images/interleave.gif";
	break;	
      case Transition::SYNCHRONIZATION :
    m_pathIcone = "images/fullsincro.gif";
	break;	
      case Transition::DISABLING :
    m_pathIcone = "images/disabling.gif";
	break;	      
      case Transition::SUSPENDRESUME :
    m_pathIcone = "images/suspend.gif";
	break;	      
      case Transition::SEQUENTIALENABLING :
    m_pathIcone = "images/enabling.gif";
	break;      
      case Transition::SEQUENTIALENABLINGINFO :
    m_pathIcone = "images/enablinginfo.gif";
	break;      
      }
      
      
      
    }
    
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
    m_pathIcone = "images/choice.gif";
	break;
      case Transition::ORDERINDEPENDENCE :
	s = "ORDERINDEPENDENCE";
    m_pathIcone = "images/cut.gif";
	break;
      case Transition::INTERLEAVING :
	s = "INTERLEAVING";
    m_pathIcone = "images/order.gif";
	break;	
      case Transition::SYNCHRONIZATION :
	s = "SYNCHRONIZATION";
    m_pathIcone = "images/sincro.gif";
	break;	
      case Transition::DISABLING :
	s = "DISABLING";
    m_pathIcone = "images/disabling.gif";
	break;	      
      case Transition::SUSPENDRESUME :
	s = "SUSPENDRESUME";
    m_pathIcone = "images/suspend.gif";
	break;	      
      case Transition::SEQUENTIALENABLING :
	s = "SEQUENTIALENABLING";
    m_pathIcone = "images/enabling.gif";
	break;      
      case Transition::SEQUENTIALENABLINGINFO :
	s = "SEQUENTIALENABLINGINFO";
    m_pathIcone = "images/enablinginfo.gif";
	break;      
      default:;
    }
    return s;
  }

  std::string Transition::getPathIcone(){
      return m_pathIcone;
  }
