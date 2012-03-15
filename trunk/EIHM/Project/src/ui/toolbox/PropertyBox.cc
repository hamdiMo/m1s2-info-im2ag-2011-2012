#include "PropertyBox.hh"

#include <QVBoxLayout>
#include <QPushButton>

#include "UserInterface.hh"


/** Constructeurs et destructeur */
PropertyBox::PropertyBox(UserInterface* userInterface) :
  m_userInterface(userInterface)
{
  setAccessibleName(tr("Properties"));
    
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(createGlobalGroupBox());
  layout->addLayout(createControlsLayout());
  layout->addStretch();

  setLayout(layout);
}


/** Methodes */
void PropertyBox::refresh() {}


/** Slots */
void PropertyBox::setTaskTree(TaskTree* taskTree) {}

void PropertyBox::setName(std::string name) {}

void PropertyBox::setType(TaskTree::Type type) {}


/** Methodes internes */
QGroupBox* PropertyBox::createGlobalGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Global"));
  QVBoxLayout* layout = new QVBoxLayout();
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
