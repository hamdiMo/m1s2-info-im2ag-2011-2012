#ifndef _EXPRESSION_HH_
#define _EXPRESSION_HH_


#include <list>


class Expression {

public:
  
  enum Value { TRUE , FALSE , UNDEFINE };
  struct Var {
    unsigned int m_id;
    Value m_value;
  };

  class Node {
  public:
    enum Type { AND , OR , NOT , VAR };

    Node(Type type, Var* var, Node* left, Node* right) :
      m_type(type),
      m_var(var),
      m_left(left),
      m_right(right)
    {}

    Var* getVar() { return m_var; }
    Type getType() { return m_type; } 
    Node* getLeft() { return m_left; }
    Node* getRight() { return m_right; }

    Value eval() {
      switch (m_type) {
      case AND:
	if (m_left->eval() == FALSE || m_right->eval() == FALSE) return FALSE;
	if (m_left->eval() == TRUE && m_right->eval() == TRUE) return TRUE;
	return UNDEFINE;
      case OR:
	if (m_left->eval() == TRUE || m_right->eval() == TRUE) return TRUE;
	if (m_left->eval() == FALSE && m_right->eval() == FALSE) return FALSE;
	return UNDEFINE;
      case NOT:
	if (m_left->eval() == TRUE) return FALSE;
	if (m_left->eval() == FALSE) return TRUE;
	return UNDEFINE;
      case VAR:
	return m_var->m_value;
      }
    }

    static Node* createConjonction(Node* e1, Node* e2) { return new Node(AND, 0, e1, e2); }
    static Node* createDisjonction(Node* e1, Node* e2) { return new Node(OR, 0, e1, e2); }
    static Node* createNegation(Node* e1) { return new Node(NOT, 0, e1, e1); }
    static Node* createVar(Var* v) { return new Node(VAR, v, 0, 0); }

  private:

    Type m_type;
    Var* m_var;
    Node* m_right, m_left;
  };
  
  Expression() {
    // lire le nombre de variables
    int n ;
    std::cout << "Nombre de variables " << std::endl;
    std::cin >> n;

    Var* v = new Var();
    v->m_id;
    v->m_value;
    m_root = Node.createVar();
  }

  ~Expression();

  void createVariables(int nbVar) {
    Var** m_variables = new Var*[nbVar];
    for (int i = 0; i < nbVar; i++) {
      m_variables[i]->m_id = i+1;
      m_variables[i]->m_value = UNDEFINE;
    }
  }

  Node* getRoot() { return m_root; }
  Var* getVar(int id) { return m_variables[id]; }

protected:
  
private:
  
  Var** m_variables;
  Node* m_root;

};

#endif
