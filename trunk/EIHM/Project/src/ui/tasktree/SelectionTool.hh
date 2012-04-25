#ifndef _SELECTION_TOOL_HH
#define _SELECTION_TOOL_HH
#include <QWidget>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>

#include "TaskTreeViewer.hh"
#include "TaskTreeItem.hh"

class TaskTreeViewer;

class SelectionTool : public QWidget { Q_OBJECT
public:
    SelectionTool (QWidget *_parent, TaskTreeViewer *_ttv);
    ~SelectionTool();



    void  keyPressEvent ( QKeyEvent * event );
    void  keyReleaseEvent ( QKeyEvent * event );
    void  mouseDoubleClickEvent ( QMouseEvent * event );
    void  mouseMoveEvent ( QMouseEvent * event );
    void  mousePressEvent ( QMouseEvent * event );
    void  mouseReleaseEvent ( QMouseEvent * event );
    void  wheelEvent ( QWheelEvent * event );

signals:

    void selectedItemsChanged();

protected:
    void paintEvent(QPaintEvent *event);

private :
    QGraphicsRectItem* m_selectionRect;
    int m_dragBeginX;
    int m_dragBeginY;
    bool m_leftButtonActive;
    TaskTreeViewer* m_taskTreeViewer;
    int xLeft, yTop, xRight, yBottom;
};
#endif
