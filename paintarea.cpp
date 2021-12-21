#include "paintarea.h"

PaintArea::PaintArea(QWidget *parent, QRect default_canvas, double grid_spacing) : QFrame(parent)
{
  // draw outline around the paint area
  setStyleSheet("PaintArea{border: 2px solid black;border-radius: 4px;padding: 2px;}");

  // Set parent to this so that it applies to the widget
  vbox = new QVBoxLayout(this);

  // paint area includes a canvas
  canvas = new PaintCanvas(this,default_canvas,grid_spacing);
  canvas->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  // paint area includes a label that holds the position of the cursor
  pos_label = new QLabel();
  pos_label->setLineWidth(2);
  pos_label->setText("XY:0.0,0.0");
  pos_label->setAlignment(Qt::AlignRight);

  // Add widgets to teh paint area
  vbox->addWidget(canvas);
  vbox->addWidget(pos_label);

  // Connect the signal move event of the canvas to the position label
  connect(canvas,SIGNAL(SignalMouseAt(QPointF)),this,SLOT(UpdatePosLabel(QPointF)));
}

void PaintArea::UpdatePosLabel(QPointF point)
{
  if(pos_label != nullptr)
  {
    QString world_pos_str = "XY:" + QString::number(point.x(),'g',5) + "," + QString::number(point.y(),'g',5);
    pos_label->setText(world_pos_str);
  }

}
