#ifndef PAINTCANVAS_H
#define PAINTCANVAS_H

#include "paintableobject.h"

#include <QWidget>

class PaintCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit PaintCanvas(QWidget *parent, QRect default_canvas, double grid_spacing);

signals:

public slots:
private:
    void resizeImage(QImage *image, const QSize &newSize);

    // Properties that need to be managed by the canvas   
    QPoint lastPoint;
    QRectF lastRect;
    QRectF lastEraserRect;
    QRect wind;
    const QRect default_window;
    int grid_spacing_;
    QRect v;
    int d;
    int wind_min;

    float ratio;

    //! Widget position of the mouse at the start of a pan event
    QPoint pan_start_;

    //! Window Position at the start of a pan event
    QPoint window_start_;

    QVector<PaintableObject *> m_Misc_Paintables;


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:

    void SignalMouseAt(QPoint eventPos );

public:
    void Add_Misc_Paintable( PaintableObject * obj )
    {
        if ( obj != nullptr )
        {
            m_Misc_Paintables.append( obj );
        }
    }
};

#endif // PAINTCANVAS_H
