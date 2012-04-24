#ifndef _TASKTREE_VIEWER_HH_
#define _TASKTREE_VIEWER_HH_

#include <iostream>
#include <QMouseEvent>
#include <QGraphicsView>

#ifdef WIN32
#include "..\..\model\TaskTree.hh"
#include "SelectionTool.hh"
#else
#include "TaskTree.hh"
#include "SelectionTool.hh"
#endif

class TaskTreeItem;
class RoundedMenu;
class SelectionTool;
class TaskTreeViewer : public QGraphicsView { Q_OBJECT

public:

  /** Constructeurs et destructeurs */
  TaskTreeViewer(TaskTree* taskTree);
  ~TaskTreeViewer();

  /** Accesseur */
  std::vector<TaskTreeItem*> getSelectedItems();
  TaskTree* getTaskTree();
  TaskTreeItem* getRoot();
  QGraphicsScene* getScene();

  /** Methodes */
  TaskTreeItem* createTaskTreeItems(TaskTree* t);
  void displayTaskTreeItems();
  void computeSceneRect(int x, int y, int xSize, int ySize);

public slots:

  /** Slots */
  void  keyPressEvent ( QKeyEvent * event );
  void  keyReleaseEvent ( QKeyEvent * event );
  void  mouseDoubleClickEvent ( QMouseEvent * event );
  void  mouseMoveEvent ( QMouseEvent * event );
  void  mousePressEvent ( QMouseEvent * event );
  void  mouseReleaseEvent ( QMouseEvent * event );    
  void  wheelEvent ( QWheelEvent * event );

signals:

  void selectedItemsChanged();

private:
  RoundedMenu *m_roundedMenu;
  TaskTree* m_taskTree;
  QGraphicsScene* m_scene; 
  bool m_personal_menu;
  TaskTreeItem* m_taskTreeItemRoot;
  std::vector<TaskTreeItem*> m_taskTreeItems;
  std::vector<TaskTreeItem*> m_selectedItems;
  SelectionTool* m_selectionTool;
  QGraphicsProxyWidget* p_proxy_roundedMenu;
};

#endif
