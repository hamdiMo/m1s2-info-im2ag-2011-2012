#ifndef _PROPERTYBOX_HH_
#define _PROPERTYBOX_HH_

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QRadioButton>
#include <QSlider>

#include "TaskTree.hh";

class UserInterface;

class PropertyBox : public QWidget { Q_OBJECT

public:

  /** Constructeurs et destructeurs */
  PropertyBox(UserInterface*);
  
  /** Methodes */
  void refresh();

public slots:

  void setTaskTree(TaskTree*);
  void setName(std::string);
  void setType(TaskTree::Type);

signals:

  void nameChanged(std::string);
  void typeChanged(TaskTree::Type);
  
private:

  /** Methodes internes */
  QGroupBox* createGlobalGroupBox();
  QHBoxLayout* createControlsLayout();

  /** Attributs */
  UserInterface* m_userInterface;

};

#endif
