#include "SelectionTool.hh"
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QColor>
#include <QWidget>

SelectionTool::SelectionTool( qreal _x, qreal _y, qreal _width, qreal _height, QWidget *_parent, TaskTreeViewer *_ttv)
    : QWidget(_parent)
{
    m_selectionRect = new QGraphicsRectItem(_x, _y, _width, _height);
    m_leftButtonActive = false;
    m_taskTreeViewer = _ttv;
}

SelectionTool::~SelectionTool()
{}

QSize SelectionTool::minimumSizeHint() const{
    return QSize(m_selectionRect->boundingRect().width(), m_selectionRect->boundingRect().height());
}

QSize SelectionTool::sizeHint() const{
  return QSize(m_selectionRect->boundingRect().width(), m_selectionRect->boundingRect().height());
}

void SelectionTool::setRect(qreal _x, qreal _y, qreal _w, qreal _h){
    m_selectionRect->setRect(_x, _y, _w, _h);
}

void  SelectionTool::keyPressEvent ( QKeyEvent * event ){

}

void  SelectionTool::keyReleaseEvent ( QKeyEvent * event ){

}

void  SelectionTool::mouseDoubleClickEvent ( QMouseEvent * event ){

}

void  SelectionTool::mouseMoveEvent ( QMouseEvent * event ){
    if (m_leftButtonActive == true){
        int xLeft, yTop, xRight, yBottom;
        if (m_dragBeginX > event->x()){
          xLeft = event->x();
          xRight = m_dragBeginX;
        }
        else{
          xRight = event->x();
          xLeft = m_dragBeginX;
        }
        if (m_dragBeginY > event->y()){
          yTop = event->y();
          yBottom = m_dragBeginY;
        }
        else{
          yBottom = event->y();
          yTop = m_dragBeginY;
        }
        move(xRight, xLeft);
        resize(xRight-xLeft, yBottom-yTop);
        QPointF pos = m_taskTreeViewer->mapToScene(xLeft, yTop);
        m_taskTreeViewer->computeSceneRect(0, 0, xRight-xLeft, yBottom-yTop);
        m_taskTreeViewer->computeSceneRect(pos.x(), pos.y(), xRight-xLeft, yBottom-yTop);
        p_proxy_selectionTool->setPos(pos.x(),pos.y());
    }
}

void  SelectionTool::mousePressEvent ( QMouseEvent * event ){
    if (event->button() == Qt::LeftButton){
        m_dragBeginX = event->x();
        m_dragBeginY = event->y();
        m_selectionRect = new QGraphicsRectItem(m_dragBeginX, m_dragBeginX, 0, 0);
        p_proxy_selectionTool = m_taskTreeViewer->getScene()->addWidget(this);
        QPointF pos = m_taskTreeViewer->mapToScene(0, 0);
        m_taskTreeViewer->computeSceneRect(0, 0, 0, 0);
        m_taskTreeViewer->computeSceneRect(pos.x(), pos.y(), 0, 0);
        p_proxy_selectionTool->setPos(pos.x(),pos.y());
        m_leftButtonActive = true;
    }
}

void  SelectionTool::mouseReleaseEvent ( QMouseEvent * event ){
    m_leftButtonActive = false;
}

void  SelectionTool::wheelEvent ( QWheelEvent * event ){

}
