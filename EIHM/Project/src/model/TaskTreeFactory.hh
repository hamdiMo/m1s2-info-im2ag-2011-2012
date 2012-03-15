#ifndef _TASKTREEFACTORY_HH_
#define _TASKTREEFACTORY_HH_

class TaskTreeFactory {

private:

  std::vector<TaskTree*> m_tasktrees;

protected:

public:

  /** Constructeurs et destructeur */
  TaskTreeFactory();

  ~TaskTreeFactory();

  /** Methodes */
  void save(int id, std::string filename); // sauvegarder dans le fichier

  int load(std::string filename); // charger depuis le fichier
  
};

#endif
