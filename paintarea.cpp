#include "paintarea.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    // Set parent to this so that it applies to the widget
    vbox = new QVBoxLayout(this);

    canvas = new PaintCanvas(this,QRect(-500,-500,1000,1000),100);

    canvas->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    pos_label = new QLabel();

    pos_label->setFrameStyle(QFrame::Panel | QFrame::Raised);
    pos_label->setLineWidth(2);

    vbox->addWidget(canvas);

    pos_label->setText("XY:0.0,0.0");
    pos_label->setAlignment(Qt::AlignRight);

    vbox->addWidget(pos_label);

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
