#ifndef _TASKTREE_VIEWER_HH_
#define _TASKTREE_VIEWER_HH_

#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QSize>
#include <iostream>
class PictureModifier;

class TaskTreeViewer : public QLabel{ Q_OBJECT

public:
  /** Constructeurs et destructeurs */
  TaskTreeViewer();
  ~TaskTreeViewer();
               
//   /** Methodes */
//   void scaleImage(double);
//   void refresh();
//   void refreshData();
//   QImage getImage();
//   void zoomIn();
//   double getScale();
//   double getWidthTranslation();
//   double getHeightTranslation();
//   double zoomOut();
//   double normalSize();
//   double fitToWindow(QSize);
//   PictureModifier*  getPictureModifier();
// private:

//   /** Methodes internes */
//   /** Attributs */
//   double m_width_translation;
//   double m_height_translation; 
//   double m_scaleFactor;
//   double m_scale;
//   PictureModifier* m_pictureModifier;
//   QImage m_qImage;
   
};

#endif
