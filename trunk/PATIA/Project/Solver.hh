#ifndef _SOLVER_HH_
#define _SOLVER_HH_

#include <list>
#include <stack>

#include "Expression.hh"

class Solver {

public:

  class Clause {
  public:
    
    Clause(Expression::Node*) {
      
    }
    ~Clause();
    
    Expression::Value getValue() {
      Expression::Value res = FALSE;
      std::list<Expression::Node*>::iterator iter = m_cur.begin();
      while (iter != m_cur.end() && res != TRUE) {
	Expression::Value v = (*iter)->eval();
	if (v == TRUE || v == UNDEFINE) res = v;
	iter++;
      }
      return res;
    }
    
    void propagate(Expression::Var* var, int id) {
      std::list<Expression::Node*>::iterator iter = m_cur.begin();
      while (iter != m_cur.end() && res != TRUE) {
	Expression::Value v = (*iter)->eval(); // donner la tabSym en param
	if (v == TRUE || v == UNDEFINE) res = v;
	iter++;
      }
    }

    std::list<Expression::Node*> m_cur;
    std::list<std::pair<int id, Expression::Node*> > m_del;

  };

  Solver(Expression e) {
    e.toCnf();
    
  }

  ~Solver();

protected:

private:

  bool isUnsatisfiable() {
    
  }

  void init();

  void solve() {
    if (!isUnsatisfiable()) {
    }
  }

  std::stack<Expression::Var> m_choices;
  std::list<Clause*> m_todo, m_done;

};

#endif
