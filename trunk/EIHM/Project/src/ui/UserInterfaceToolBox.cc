#ifdef WIN32
#include "UserInterface.hh"
#include "toolbox\PropertyBox.hh"
#else
#include "UserInterface.hh"
#include "PropertyBox.hh"
#endif


// /** Accesseurs */
PropertyBox* UserInterface::getPropertyBox() { return m_propertyBox; }


// /** Methodes */
PropertyBox* UserInterface::createPropertyBox() { return new PropertyBox(this); }


// /** Methodes internes */
void UserInterface::createToolBoxDocks() {
  addDockWidget(Qt::RightDockWidgetArea, m_propertyBoxDock = createPropertyBoxDock());
  m_infoBox=getPropertyBox()->getInfoBox();
 
  
}

QDockWidget* UserInterface::createPropertyBoxDock() {
  return createDockWidget(m_propertyBox = createPropertyBox()); 
}

