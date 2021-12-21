#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QFrame>

#include <QVBoxLayout>
#include <QLabel>

#include "paintcanvas.h"

class PaintArea : public QFrame
{
    Q_OBJECT
        public:
                 explicit PaintArea(QWidget *parent, QRect default_canvas, double grid_spacing);

    PaintCanvas * GetCanvas(){
        return(canvas);
    }

signals:

public slots:
    void UpdatePosLabel(QPointF point);

public:
    QVBoxLayout * vbox;

    PaintCanvas * canvas;

    QLabel * pos_label;

};

#endif // PAINTAREA_H
