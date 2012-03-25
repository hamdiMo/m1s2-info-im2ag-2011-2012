#include "TaskTree.hh"
#include <string>

  /** Constructeurs et destructeurs */
  TaskTree::TaskTree(std::string name, Type type) :
    m_index(-1),
    m_name(name),
    m_type(type),
    m_subtrees(10),
    m_in(0),
    m_out(0),
    m_parent(0)
  {}

  TaskTree::TaskTree(std::string name, Type type, std::vector<TaskTree*> subtrees) :
    m_index(-1),
    m_name(name),
    m_type(type),
    m_subtrees(10),
    m_in(0),
    m_out(0),
    m_parent(0)
  {
    for(int i=0; i < (int)subtrees.size(); i++) m_subtrees.push_back(subtrees[i]);
  }

  TaskTree::~TaskTree() {}


  /** Accesseurs */
  int TaskTree::getSize() { return m_subtrees.size(); }

  TaskTree::Type TaskTree::getType() { return m_type; }
  
  std::string TaskTree::getName() { return m_name; }

  TaskTree* TaskTree::getSubTree(int index) {
    if ( index >= 0 && index < (int)m_subtrees.size()) return m_subtrees[index];
    else return 0; // gestion d'erreur à mettre en place    
  } // rechercher le sous arbre sinon renvoit 0

  Transition* TaskTree::getTransitionIn() { return m_in; }  

  Transition* TaskTree::getTransitionOut() { return m_out; }  
  
  TaskTree* TaskTree::getParent(){ return m_parent; }
  
  
  
  void TaskTree::setIndex(int index){ m_index = index; }
  
  void TaskTree::setType(TaskTree::Type type){ m_type = type; }
  
  void TaskTree::setName(std::string name){ m_name = name; }
  
  //return -1 en cas d'erreurs
  int TaskTree::setTransitionIn(Transition::Type type){
    if (m_parent != 0 && m_index > 0){ // j'ai un leftnode
      TaskTree* leftNode = m_parent->getSubTree(m_index-1);
      if(leftNode->getTransitionOut() != 0) {
	delete leftNode->getTransitionOut();
      }
      if(m_in != 0) delete m_in;
      //tout ok, création de la transition
      
      Transition* temp = new Transition(leftNode, this, type);
      m_in = temp;
      leftNode->setTransitionOut(temp);
      return 0;
    } else return -1;
  }
  
  int TaskTree::setTransitionIn(Transition* transition){
    if(m_parent != 0 && m_index > 0){
      if (m_in != 0) delete m_in;
      m_in = transition;
      return 0;
    } else return -1;
  }
  
   //return -1 en cas d'erreurs
  int TaskTree::setTransitionOut(Transition::Type type){
    if(m_parent != 0 && m_index < (int)m_subtrees.size()-1){ //rightnode OK
      TaskTree* rightNode = m_parent->getSubTree(m_index+1);
      if(rightNode->getTransitionIn() != 0) {
	delete rightNode->getTransitionIn();
      }
      if(m_out != 0) delete m_out;
      //tout ok, création de la transition
      Transition* temp = new Transition(this, rightNode, type);
      m_out = temp;
      rightNode->setTransitionIn(temp);
      return 0;
    } else return -1; 
  }
  
  int TaskTree::setTransitionOut(Transition* transition){
    if(m_parent != 0 && m_index < (int)m_subtrees.size() - 1){
      if (m_out != 0) delete m_out;
      m_out = transition;
      return 0;
    } else return -1;
    
  }

  void TaskTree::setParent(TaskTree* parent){ m_parent = parent; }
  
  void TaskTree::removeTransitionIn(){
    if(m_in != 0){ 
      delete m_in;
      m_in = 0;
      TaskTree* leftNode = m_parent->getSubTree(m_index-1);   
      if(leftNode->getTransitionOut() != 0) leftNode->removeTransitionOut();
    }  
  }

void TaskTree::removeTransitionOut(){
  if(m_out != 0){
    delete m_out;
    m_out = 0;
    TaskTree* rightNode = m_parent->getSubTree(m_index+1);   
    if(rightNode->getTransitionIn() != 0) rightNode->removeTransitionIn();
  }
}  

void TaskTree::removeTransitions(){
  removeTransitionIn();
  removeTransitionOut();
}  
  
  /** Methodes */
  
  void TaskTree::addSubtree(TaskTree* son){
    son->setParent(this);
    son->setIndex(m_subtrees.size());
    m_subtrees.push_back(son);
  }
  
  void TaskTree::insertSubtree(TaskTree* son, int index){
    int size = (int)m_subtrees.size();
    if(index >=0 && index < size){
      son->setParent(this);
      son->setIndex(index);
      m_subtrees.push_back(son);
      if(index > 0) m_subtrees[index-1]->removeTransitionOut();
      while(size > index){
	m_subtrees[size]= m_subtrees[size-1];
	m_subtrees[size]->setIndex(size);
	size--;
      }
      m_subtrees[size] = son;
    } else std::cout<<"index out of bounds"<< std::endl;
  }
  
  void TaskTree::swapSubtree(int id1, int id2){  
    if(id1 >= 0 && id1 < (int)m_subtrees.size() && id2 >= 0 && id2 < (int)m_subtrees.size()){
      TaskTree* tmp = m_subtrees[id1];
      tmp->removeTransitions();
      TaskTree* tmp2 = m_subtrees[id2];
      tmp2->removeTransitions();
      m_subtrees[id1] = tmp2;
      m_subtrees[id2] = tmp;
    } 
    else std::cout<<"index out of bounds"<< std::endl;
  }
  
  void TaskTree::removeSubtree(int index){
    int size = (int)m_subtrees.size();
    if (index >=0 && index < size){
      m_subtrees[index]->remove();
      for(int j = index; j < size-1; j++)
	m_subtrees[j] = m_subtrees[j+1];
      m_subtrees.pop_back();
    }
  }
  
  void TaskTree::remove(){
    removeTransitions();
    if((int)m_subtrees.size() > 0){
      std::vector<TaskTree*>::iterator it;
      for (it=m_subtrees.end()-1; it < m_subtrees.begin(); it--){
    	(*it)->remove();
	m_subtrees.pop_back();
      }
      // vider m_subtrees
    }
  }
