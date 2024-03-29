#ifndef _PROPERTYBOX_HH_
#define _PROPERTYBOX_HH_

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <string>

#ifdef WIN32
#include "..\..\model\TaskTree.hh"
#else
#include "TaskTree.hh"
#endif


class UserInterface;

class PropertyBox : public QWidget { Q_OBJECT

public:

  /** Constructeurs et destructeurs */
  PropertyBox(UserInterface*);
  
  /** Methodes */
  void refresh();
  QLabel* getInfoBox();
public slots:

  void setTaskTree(TaskTree*);
  void setName(std::string);
  void setType(TaskTree::Type);

signals:

  void nameChanged(std::string);
  void typeChanged(TaskTree::Type);
  
private:

  /** Methodes internes */
  QGroupBox* createInfoGroupBox();
  QGroupBox* createGlobalGroupBox();
  QGroupBox* createTypeGroupBox();
  QHBoxLayout* createControlsLayout();
  QVBoxLayout * m_fulllayout;
  /** Attributs */
  QLineEdit* m_nameLE;
  QRadioButton *m_abstractTypeRB, *m_appTypeRB, *m_interactTypeRB, *m_userTypeRB;
  UserInterface* m_userInterface;
  TaskTree* m_taskTree;
public :
  QLabel* m_infoBox;
};

#endif
