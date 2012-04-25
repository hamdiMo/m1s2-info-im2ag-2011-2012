#include "SelectionTool.hh"
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QColor>
#include <QWidget>
#include <iostream>

using namespace std;

SelectionTool::SelectionTool(QWidget *_parent, TaskTreeViewer *_ttv)
    : QWidget(_parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    m_leftButtonActive = false;
    m_taskTreeViewer = _ttv;
    setHidden(true);
}

SelectionTool::~SelectionTool()
{}

void SelectionTool::paintEvent(QPaintEvent * /* event */){
  QPainter painter(this);
  QPen pen = QPen(Qt::DashLine);
  pen.setColor(QColor(0, 150, 0, 255));
  painter.setPen(pen);
  painter.drawRect(0, 0, width()-1, height()-1);
  //painter.setBrush(*p_gradient);
}


void  SelectionTool::keyPressEvent ( QKeyEvent * event ){

}

void  SelectionTool::keyReleaseEvent ( QKeyEvent * event ){

}

void  SelectionTool::mouseDoubleClickEvent ( QMouseEvent * event ){

}

void  SelectionTool::mouseMoveEvent ( QMouseEvent * event ){
    if (m_leftButtonActive == true){
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
        m_taskTreeViewer->getproxySelectionTool()->setPos(pos.x(),pos.y());
        setHidden(false);
    }
}

void  SelectionTool::mousePressEvent ( QMouseEvent * event ){
    if (event->button() == Qt::LeftButton){
        m_dragBeginX = event->x();
        m_dragBeginY = event->y();
        m_leftButtonActive = true;
    }
}

void  SelectionTool::mouseReleaseEvent ( QMouseEvent * event ){
    m_leftButtonActive = false;
    setHidden(true);
    // on efface la sélection
    m_taskTreeViewer->getRefselectedItems()->clear();
    // clic : un item sélectionné
    if (event->x() == m_dragBeginX || event->y() == m_dragBeginY) {
      // puis on ajoute dans la nouvelle sélection tous les items dans le cadre de sélection
        std::vector<TaskTreeItem*>::iterator it;
        QPointF pos = m_taskTreeViewer->mapToScene(event->x(), event->y());

        for(it = m_taskTreeViewer->getRefTaskTreeItems()->begin();it != m_taskTreeViewer->getRefTaskTreeItems()->end();++it){

            if ((*it)->contain(pos.x(), pos.y())){
                m_taskTreeViewer->getRefselectedItems()->push_back(*it);
                break;
            }
        }
    }
    else{
        std::vector<TaskTreeItem*>::iterator it;
        QPointF posTopLeft = m_taskTreeViewer->mapToScene(xLeft, yTop);
        QPointF posBottomRight = m_taskTreeViewer->mapToScene(xRight, yBottom);
        for(it = m_taskTreeViewer->getRefTaskTreeItems()->begin();it != m_taskTreeViewer->getRefTaskTreeItems()->end();++it){
            // si un des angles du cadre est dans un des items
            if ((*it)->contain(posTopLeft.x(), posTopLeft.y())
            || (*it)->contain(posBottomRight.x(), posBottomRight.y())
            || (*it)->contain(posBottomRight.x(), posTopLeft.y())
            || (*it)->contain(posTopLeft.x(), posBottomRight.y())) {
                m_taskTreeViewer->getRefselectedItems()->push_back((*it));
            } // sinon, si une des arrêtes du cadre passe dans un item
            else if ((posTopLeft.x() >= (*it)->getX()
              && posTopLeft.x() <= (*it)->getX()+32
              && posBottomRight.y() >= (*it)->getY()+32
              && posTopLeft.y() <= (*it)->getY())
                || (posBottomRight.x() >= (*it)->getX()
                && posBottomRight.x() <= (*it)->getX()+32
                && posBottomRight.y() >= (*it)->getY()+32
                && posTopLeft.y() <= (*it)->getY())
                || (posTopLeft.y() >= (*it)->getY()
                && posTopLeft.y() <= (*it)->getY()+32
                && posBottomRight.x() >= (*it)->getX()+32
                && posTopLeft.x() <= (*it)->getX())
                || (posBottomRight.y() >= (*it)->getY()
                && posBottomRight.y() <= (*it)->getY()+32
                && posBottomRight.x() >= (*it)->getX()+32
                && posTopLeft.x() <= (*it)->getX())) {
                    m_taskTreeViewer->getRefselectedItems()->push_back((*it));
            }
             // si l'item est contenu dans le cadre (i.e si les coins haut/droite et bas/gauche sont contenus dans le cadre)
             else if ((*it)->getX() >= posTopLeft.x() && (*it)->getX() <= posBottomRight.x()
                && (*it)->getX()+32 >= posTopLeft.x() && (*it)->getX()+32 <= posBottomRight.x()
                && (*it)->getY() >= posTopLeft.y() && (*it)->getY() <= posBottomRight.y()
                && (*it)->getY()+32 >= posTopLeft.y() && (*it)->getY()+32 <= posBottomRight.y())
             {
                    m_taskTreeViewer->getRefselectedItems()->push_back((*it));
             }
        }
    }

    selectedItemsChanged();
}

void  SelectionTool::wheelEvent ( QWheelEvent * event ){

}
