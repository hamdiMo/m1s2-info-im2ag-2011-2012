#ifdef WIN32
#include "..\UserInterface.hh"
#else
#include "UserInterface.hh"
#endif


#include "PropertyBox.hh"



#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>



/** Constructeurs et destructeur */
PropertyBox::PropertyBox(UserInterface* userInterface) :
  m_userInterface(userInterface)
{
  setAccessibleName(tr("Properties"));
    
  m_fulllayout = new QVBoxLayout;
  m_fulllayout->addWidget(createGlobalGroupBox());
  m_fulllayout->addLayout(createControlsLayout());
  m_fulllayout->addStretch();
  m_fulllayout->addWidget(createInfoGroupBox());
  setLayout(m_fulllayout);
 setMaximumSize(400,400);
}


/** Methodes */
void PropertyBox::refresh() {
   m_fulllayout->addWidget(m_infoBox);
}
QLabel* PropertyBox::getInfoBox() {return m_infoBox;}


/** Slots */
void PropertyBox::setTaskTree(TaskTree* taskTree) {
  m_taskTree = taskTree;
  setName(m_taskTree->getName());
  setType(m_taskTree->getType());
}

void PropertyBox::setName(std::string name) {
  m_nameLE->setText(name.c_str());
}

void PropertyBox::setType(TaskTree::Type type) {
  switch (type) {
  case TaskTree::ABSTRACTION:
    m_abstractTypeRB->setChecked(true);
    break;
  case TaskTree::APPLICATION:
    m_appTypeRB->setChecked(true);
    break;
  case TaskTree::INTERACTION:
    m_interactTypeRB->setChecked(true);
    break;
  case TaskTree::USER:
    m_userTypeRB->setChecked(true);
    break;
  }
}


/** Methodes internes */
QGroupBox* PropertyBox::createInfoGroupBox(){
  QGroupBox* groupBox = new QGroupBox(tr("Informations"));
  QVBoxLayout* layout = new QVBoxLayout();
  m_infoBox = new QLabel("");
  layout->addWidget(m_infoBox);
  groupBox->setLayout(layout);
 return groupBox;
}

QGroupBox* PropertyBox::createGlobalGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Global"));
  QVBoxLayout* layout = new QVBoxLayout();
  
  m_nameLE = new QLineEdit(tr("Name"));

  layout->addWidget(m_nameLE);
  layout->addWidget(createTypeGroupBox());
  layout->addWidget(new QTextEdit(tr("Infos")));

  groupBox->setLayout(layout);
  return groupBox;
}

QGroupBox* PropertyBox::createTypeGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Global"));
  QVBoxLayout* layout = new QVBoxLayout();
  
  m_abstractTypeRB = new QRadioButton(tr("Abstraction"));
  m_appTypeRB = new QRadioButton(tr("Application"));
  m_interactTypeRB = new QRadioButton(tr("Interaction"));
  m_userTypeRB = new QRadioButton(tr("User"));

  layout->addWidget(m_abstractTypeRB);
  layout->addWidget(m_appTypeRB);
  layout->addWidget(m_interactTypeRB);
  layout->addWidget(m_userTypeRB);
  groupBox->setLayout(layout);
  return groupBox;
}

QHBoxLayout* PropertyBox::createControlsLayout() {
  QHBoxLayout* layout = new QHBoxLayout();

  QPushButton* pushButtonCancel = new QPushButton(tr("Cancel"));
  QPushButton* pushButtonApply = new QPushButton(tr("Apply"));
  
  connect(pushButtonCancel, SIGNAL(clicked()), this, SLOT(resetOperation()));
  connect(pushButtonApply, SIGNAL(clicked()), this, SLOT(applyOperation()));

  layout->addWidget(pushButtonCancel);
  layout->addWidget(pushButtonApply);
  
  return layout;
}
