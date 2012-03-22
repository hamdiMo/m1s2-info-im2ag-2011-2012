#ifndef _TASKTREE_MODIFIER_HH_
#define _TASKTREE_MODIFIER_HH_

#include <QScrollArea>
#include <QClipboard>
class TaskTreeViewer;

class TaskTreeModifier: public QScrollArea { Q_OBJECT 
public :
  /** Constructeurs et destructeur */
  TaskTreeModifier(TaskTreeViewer*); 
  ~TaskTreeModifier();
private :
  TaskTreeViewer* m_taskTreeViewer;

};

#endif




  /** Accesseurs */
//   QImage* getImage();
//   Picture* getPicture();
//   QClipboard* getClipBoard();
//   PictureArea * getPictureArea();
//   /** Methodes */
//   Picture* getSelectedPicture();
//   void notifyCurrent();
//   void refreshData();
//   void refresh();
//   void zoomIn();
//   void zoomOut();  
//   void normalSize();
//   void fitToWindow();
//   void copy();	
//   void paste();
//   void cut();
//   void crop();
//   bool enableSelection();
//   void disableSelection();
//   bool enableMove();
//   void disableMove();



// private slots:
//   /** SLOTS**/
//   void 	keyPressEvent ( QKeyEvent * event );
//   void 	keyReleaseEvent ( QKeyEvent * event );



//   /** Attributs */
//   Picture* m_picture;
//   QImage* m_image;
//   PictureArea* m_pictureArea;
//   UserInterface* m_userInterface;
