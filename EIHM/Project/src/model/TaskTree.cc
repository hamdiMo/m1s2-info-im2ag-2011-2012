#include "TaskTree.hh"


#include <string>
#include <queue>
using namespace std;

  /** Constructeurs et destructeurs */
  TaskTree::TaskTree(std::string name, Type type) :
    m_index(-1),
    m_name(name),
    m_type(type),
    m_subtrees(0),
    m_in(0),
    m_out(0),
    m_parent(0)
  {}
  
  TaskTree::TaskTree(std::string name, Type type, std::vector<TaskTree*> subtrees) :
    m_index(-1),
    m_name(name),
    m_type(type),
    m_subtrees(0),
    m_in(0),
    m_out(0),
    m_parent(0)
  {
    for(int i=0; i < (int)subtrees.size(); i++) addSubtree(subtrees[i]);
  }
  
  
  // ce constructeur copie l'arbre t SANS le pointeur vers le parent... 
  // A mettre Ã  jour suite Ã  la copie 
  TaskTree::TaskTree(TaskTree* t):
    m_subtrees(0),
    m_in(0),
    m_out(0),
    m_parent(0)
  
  {
    m_index = t->getIndex();
    m_name = string(t->getName());
    m_type = t->getType();
    vector<TaskTree*> subTmp = t->getSubTrees();
    for(int i=0; i < (int)subTmp.size(); i++){
      TaskTree* son = new TaskTree(subTmp[i]);
      addSubtree(son);
      if(subTmp[i]->getTransitionIn() != 0) son->setTransitionIn(subTmp[i]->getTransitionIn()->getType());
    }
  }  

  TaskTree::~TaskTree() {}


  /** Accesseurs */
  int TaskTree::getIndex(){ return m_index; }
  
  int TaskTree::getSize() { return m_subtrees.size(); }

  TaskTree::Type TaskTree::getType() { return m_type; }
  
  std::string TaskTree::getName() { return m_name; }

  TaskTree* TaskTree::getSubTree(int index) {
    if ( index >= 0 && index < (int)m_subtrees.size()) return m_subtrees[index];
    else return 0; // gestion d'erreur Ã  mettre en place    
  } // rechercher le sous arbre sinon renvoit 0

  std::vector<TaskTree*> TaskTree::getSubTrees(){
    return m_subtrees;
  }

  Transition* TaskTree::getTransitionIn() { return m_in; }  

  Transition* TaskTree::getTransitionOut() { return m_out; }  
  
  TaskTree* TaskTree::getParent(){ return m_parent; }
  
  
  // Attention, il ne faut pas set des index Ã  l'arrache, voir swapSubtree
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
      /*if(m_in != 0) delete m_in;*/
      //tout ok, crÃ©ation de la transition
      
      Transition* temp = new Transition(leftNode, this, type);
      m_in = temp;
      leftNode->setTransitionOut(temp);
      return 0;
    } else return -1;
  }
  
  int TaskTree::setTransitionIn(Transition* transition){
    if(m_parent != 0 && m_index > 0){
      /*if (m_in != 0) delete m_in;*/
      m_in = transition;
      return 0;
    } else return -1;
  }
  
   //return -1 en cas d'erreurs
  int TaskTree::setTransitionOut(Transition::Type type){    
    if(m_parent != 0 && m_index < (int)m_parent->m_subtrees.size()-1){ //rightnode OK
      TaskTree* rightNode = m_parent->getSubTree(m_index+1);
      if(rightNode->getTransitionIn() != 0) {
	delete rightNode->getTransitionIn();
      }
      
      /*if(m_out != 0) delete m_out;*/
      
      //tout ok, crÃ©ation de la transition
      Transition* temp = new Transition(this, rightNode, type);
      m_out = temp;
      rightNode->setTransitionIn(temp);
      return 0;
    } else return -1; 
  }
  
  int TaskTree::setTransitionOut(Transition* transition){
    if(m_parent != 0 && m_index < (int)m_parent->getSubTrees().size() - 1){
      
      /*if (m_out != 0) delete m_out;*/
      
      m_out = transition;
      return 0;
    } else return -1;
    
  }

  void TaskTree::setParent(TaskTree* parent){ m_parent = parent; }
  
  void TaskTree::removeTransitionIn(){
    if(m_in != 0){ 
      //delete m_in;
      m_in = 0;
      TaskTree* leftNode = m_parent->getSubTree(m_index-1);   
      if(leftNode->getTransitionOut() != 0) leftNode->removeTransitionOut();
    }  
  }

void TaskTree::removeTransitionOut(){
  if(m_out != 0){
    //delete m_out;
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
      m_subtrees[id1]->setIndex(id1);
      m_subtrees[id2] = tmp;
      m_subtrees[id2]->setIndex(id2);
    } 
    else std::cout<<"index out of bounds"<< std::endl;
  }

  void TaskTree::remove(){
    TaskTree* t = getParent();
    if(t != 0){
      t->removeSubtree(getIndex());
    }
  }
  
  void TaskTree::removeSubtree(int index){
    int size = (int)m_subtrees.size();
    if (index >=0 && index < size){
      m_subtrees[index]->removeSubtree();
      for(int j = index; j < size-1; j++){
	m_subtrees[j] = m_subtrees[j+1];
	m_subtrees[j]->setIndex(j);
      }
      m_subtrees.pop_back();
    }
  }
  
  
  void TaskTree::removeSubtree(){
    removeTransitions();
    int size = (int)m_subtrees.size();
    size--;
    while(size >= 0){
      m_subtrees[size]->removeSubtree();
      m_subtrees.pop_back();
      size--;
    }
  }
  
  std::vector<TaskTree*> TaskTree::getLevel(TaskTree* t, int level){
    std::vector<std::vector <TaskTree*> > vect; 
    std::vector<TaskTree*> result;
    std::vector<TaskTree*> cur;
    
    if (level == 0){
      result.push_back(t);
    } else {
      getLevelTemp(t, level, &vect);
    
      std::vector<std::vector<TaskTree*> >::iterator it;
      std::vector<TaskTree*>::iterator itCur;

      for (it=vect.begin() ; it != vect.end(); it++ ){
	cur = *it;
	for (itCur = cur.begin() ; itCur != cur.end(); itCur++ )
	  result.push_back(*itCur);
      }
    }
    return result;
  }
  
  void TaskTree::getLevelTemp(TaskTree* t, int level, std::vector<std::vector<TaskTree*> >* vect){
    if(level >= 0){
     rec(t, 0, level, vect);
    } else {
      std::cout << "level must be positive"<< std::endl;
    }
  }

  void TaskTree::rec(TaskTree* t, int n, int level, std::vector<std::vector <TaskTree*> >* vect){
    if(n == level-1){
      vect->push_back(t->getSubTrees());

    } else {
      for(int i = 0; i < (int)t->getSubTrees().size(); i++){
	rec(t->getSubTrees()[i], n+1, level, vect);
      }
    }
  }
  
  void TaskTree::printSubTree(){
    cout << endl;
    for(int i = 0; i < (int)m_subtrees.size(); i++){
      cout << m_subtrees[i]->getName() + " ";
    }
    cout << endl;
  }
  
  void TaskTree::copyPaste(TaskTree* t){
    addSubtree(new TaskTree(t));
  }
  
  void TaskTree::cutPaste(TaskTree* t){
    copyPaste(t);
    if(t->getIndex() != -1){
      TaskTree* parent = t->getParent();
      int index = t->getIndex();
      parent->removeSubtree(index);
    }
  } 
  
  void TaskTree::printTree(){
    queue<TaskTree*> q;
    queue<TaskTree*> q2;
    q.push(this);
    cout << endl;
    std::vector<TaskTree*>::iterator it;
    while(!q.empty() || !q2.empty()){
      while(!q.empty()){
	cout << q.front()->getName()<< " ";
	if(q.front()->getTransitionOut() != 0){
	  cout << q.front()->getTransitionOut()->toString() + " " ;
	}
// 	if(q.front()->getTransitionIn() != 0){
// 	  cout << q.front()->getTransitionIn()->toString() + " " ;
// 	}
// 	cout << q.front()->getName()<< " ";
	vector<TaskTree*> subTree = (q.front())->getSubTrees();
	for(int i = 0; i < (int)subTree.size(); i++){
	  //cout << subTree[i]->getName() + " ";
	  q2.push(subTree[i]);
	}
	q.pop();     
      }
      cout <<endl;
      while(!q2.empty()){
	q.push(q2.front());
	q2.pop();
      }
    }
    cout << endl;
  }

  bool TaskTree::isSon(TaskTree* t){
    bool b = false;
    if (this == t) return b;
    vector<TaskTree*> subTree = t->getSubTrees();
    for(int i = 0; i < (int)subTree.size(); i++){
      b |= (this == subTree[i] || isSon(subTree[i]));
    }
    return b;
  }
  
