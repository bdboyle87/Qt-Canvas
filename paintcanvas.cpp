#include "paintcanvas.h"
#include<QtGlobal>
#include <QPainter>
#include <QMouseEvent>

//******************************************************************************
//! PaintCanvas() -- PaintCanvas
//!
//!
//!
//! - 21Nov04 bdb Created
//******************************************************************************
PaintCanvas::PaintCanvas(QWidget *parent, QRect default_canvas, double grid_spacing) : QWidget(parent),
  window(default_canvas),
  default_window(default_canvas),
  grid_spacing_(grid_spacing)
{
  // Create Leave Off Space from the Edge of teh widget to start.
  window+= QMargins( grid_spacing/4,  grid_spacing/4,  grid_spacing/4,  grid_spacing/4);

  // Turn on mouse tracking so that we get motion without a mouse button press
  setMouseTracking(true);
}

//******************************************************************************
//! PaintCanvas() -- resizeImage
//!
//!
//!
//! - 21Nov04 bdb Created
//******************************************************************************
void PaintCanvas::resizeImage(QImage *image, const QSize &newSize)
{

}

//******************************************************************************
//! PaintCanvas() -- mousePressEvent
//!
//!
//!
//! - 21Nov04 bdb Created
//******************************************************************************
void PaintCanvas::mousePressEvent(QMouseEvent *event)
{
  // Set focus - focus is needed to process subsequent key strokes
  setFocus();

  // Set drawing true based on button press
  if (event->button() == Qt::LeftButton) {
    // USEFUL DEBUG LOGIC FOR ODD MOTION
    /*qDebug() << "Left Mouse Press " << event->pos();
        qDebug() << "viewport: " << v;
        qDebug() << "window: " << wind;
        qDebug() << "d: " << d << " wind min: " << wind_min << " ratio: " << ratio;*/

    // Set Pan Active and Capture the Start position
    pan_start_ = event->pos();

    //Capture the start location of the top left
    // We move this in the Pan method
    window_start_ = window.topLeft();
  }
  else if(event->button() == Qt::RightButton){
    // Reset Wind size
    window = default_window + QMargins( grid_spacing_/4,  grid_spacing_/4,  grid_spacing_/4,  grid_spacing_/4);
  }
  update();
}

//******************************************************************************
//! PaintCanvas() -- mouseMoveEvent
//!
//!
//!
//! - 21Nov04 bdb Created
//******************************************************************************
void PaintCanvas::mouseMoveEvent(QMouseEvent *event)
{
  QPoint epos = event->pos();

  if ((event->buttons() & Qt::LeftButton)){

    // Calculate delta from start psotion
    QPoint delta = epos - pan_start_;

    // Move the top left by the delta amount
    // Ratio is a mearue of the viewport size relative to the  window.
    window.moveTopLeft(-(delta)/ratio + window_start_);
  }


  //World Loc - Where in the world are we.
  QPointF world_loc = QPointF(epos-QPoint(viewport.width()/2,viewport.height()/2))/ratio + QPointF(window.center());

  emit SignalMouseAt( world_loc );
  update();
}

//******************************************************************************
//! PaintCanvas() -- mouseReleaseEvent
//!
//!
//!
//! - 21Nov04 bdb Created
//******************************************************************************
void PaintCanvas::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {

  }

}

//******************************************************************************
//! PaintCanvas() -- keyPressEvent
//!
//!
//!
//! - 21Nov04 bdb Created
//******************************************************************************
void PaintCanvas::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Up)
  {
    qDebug() << "Key Up";
    window.moveTop(window.top()+10);
  }
  else if(event->key() == Qt::Key_Down)
  {
    qDebug() << "Key Down";
    window.moveBottom(window.bottom()-10);
  }
  else if(event->key() == Qt::Key_Left)
  {
    qDebug() << "Key Left";
    window.moveLeft(window.left()-10);
  }
  else if(event->key() == Qt::Key_Right)
  {
    qDebug() << "Key Right";
    window.moveRight(window.right()+10);
  }

  QWidget::keyPressEvent(event);
  update();
}

//******************************************************************************
//! PaintCanvas() -- wheelEvent
//!
//!
//!
//! - 21Nov04 bdb Created
//******************************************************************************
void PaintCanvas::wheelEvent( QWheelEvent * event)
{
  // Angle Roll
  QPoint angle_delta = event->angleDelta();

  int zoom_change = grid_spacing_ * 0.1;

  if(angle_delta.y() > 0)
  {
    window-=QMargins( zoom_change,  zoom_change,  zoom_change,  zoom_change);
  }
  else
  {
    window+=QMargins( zoom_change,  zoom_change,  zoom_change,  zoom_change);
  }
  update();
}

//******************************************************************************
//! PaintCanvas() -- paintEvent
//!
//!
//!
//! - 21Nov04 bdb Created
//******************************************************************************
void PaintCanvas::paintEvent(QPaintEvent *event)
{
  // See window viewport details
  // 1. https://flylib.com/books/en/2.18.1/painting_with_qpainter.html
  // 2. https://web.mit.edu/~firebird/arch/sun4x_59/doc/html/coordsys.html

  QPen pen;  // creates a default pen
  QBrush brush;
  QPainter painter(this);

  //Set the render hint for the canvas
  painter.setRenderHint(QPainter::Antialiasing);

  // Set the window
  painter.setWindow( window );
  viewport = painter.viewport();

  // Create non distorted view port of the logical space
  // Keep the aspect ratio
  d = qMin( viewport.width(), viewport.height() );
  painter.setViewport( viewport.left() + (viewport.width()-d)/2,
                       viewport.top() + (viewport.height()-d)/2, d, d );

  //Capture Min Wind dimension
  wind_min = qMin( window.width(), window.height() );

  // Create ratio of viewport and window. This is needed to pan the world and the view port and the window are differencet sizes.
  ratio = static_cast<float>(d) / static_cast<float>(wind_min);

  // Draw Grid & Space
  QRectF rectToDraw(default_window);
  pen.setStyle(Qt::SolidLine);
  pen.setWidthF((grid_spacing_ * 0.04));
  pen.setCapStyle(Qt::RoundCap);
  pen.setJoinStyle(Qt::RoundJoin);

  // Draw Space
  pen.setBrush(Qt::white);
  painter.setPen(pen);
  painter.setBrush(Qt::white);
  painter.drawRect(rectToDraw);

  // Draw Grid
  pen.setBrush(Qt::gray);
  painter.setPen(pen);
  for (int x = default_window.left(); x <= default_window.right(); x+=grid_spacing_) {
    painter.drawLine(x,default_window.top(),x,default_window.bottom());
  }
  for (int y = default_window.top(); y <= default_window.bottom(); y+=grid_spacing_) {
    painter.drawLine(default_window.left(),y,default_window.right(),y);
  }

  pen.setBrush(Qt::black);
  pen.setWidthF((grid_spacing_ * 0.08));
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(rectToDraw);

  // Draw Origin Elipse
  painter.drawEllipse(QPointF(0.0,0.0),grid_spacing_/5.0,grid_spacing_/5.0);

  // Paint items handed to the canvas
  foreach( PaintableObject * p, m_Misc_Paintables )
  {
    painter.save();

    p->UIPaint( painter );

    painter.restore();
  }
}

//******************************************************************************
//! PaintCanvas() -- resizeEvent
//!
//!
//!
//! - 21Nov04 bdb Created
//******************************************************************************
void PaintCanvas::resizeEvent(QResizeEvent *event)
{
  // Call the base update
  update();

  QWidget::resizeEvent(event);
}
