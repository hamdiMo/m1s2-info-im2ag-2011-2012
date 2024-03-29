#ifdef WIN32
#include "UserInterface.hh"
#else
#include "UserInterface.hh"
#endif



#include <QMenuBar>



// /** Methodes internes */
void UserInterface::createMenuBar() {
  menuBar()->addMenu(createFileMenu());
  menuBar()->addMenu(createEditMenu());
  menuBar()->addMenu(createViewMenu());
  menuBar()->addMenu(createHelpMenu());
}

QMenu* UserInterface::createFileMenu() {
  m_fileMenu = new QMenu(tr("&File"), this);
  m_fileMenu->addAction(m_openAct);
  m_fileMenu->addAction(m_saveAct);
  m_fileMenu->addSeparator();
  m_fileMenu->addAction(m_exitAct);
  return m_fileMenu;
}

QMenu* UserInterface::createEditMenu() {
  m_editMenu = new QMenu(tr("&Edit"), this);
  m_editMenu->addAction(m_undoAct);
  m_editMenu->addAction(m_redoAct);
  m_fileMenu->addSeparator();
  m_editMenu->addAction(m_copy);
  m_editMenu->addAction(m_paste);
  m_editMenu->addAction(m_cut);
  return m_editMenu;
}

QMenu* UserInterface::createViewMenu() {
  m_viewMenu = new QMenu(tr("&View"), this);
  m_viewMenu->addAction(m_zoomInAct);
  m_viewMenu->addAction(m_zoomOutAct);
  m_viewMenu->addAction(m_normalSizeAct);
  m_viewMenu->addAction(m_fitToWindowAct);
  return m_viewMenu;
}

QMenu* UserInterface::createHelpMenu() {
  m_helpMenu = new QMenu(tr("&Help"), this);
  m_helpMenu->addAction(m_aboutAct);
  m_helpMenu->addAction(m_aboutQtAct);
  return m_helpMenu;
}
