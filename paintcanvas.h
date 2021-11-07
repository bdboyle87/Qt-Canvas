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

    //! The window defines the space shown in the viewport
    QRect window;

    //! The default window used for starting the canvas and snapping to original screen
    const QRect default_window;

    //! The spacing used for the drawn grid
    int grid_spacing_;

    //! The view port definition. This informs the widget how to veiw the window
    QRect viewport;

    //! Min dimension for the viewport so that we can maintain the desired aspect ratio
    int d;

    //! Min dimension for the window so that we can maintain the desired aspect ratio
    int wind_min;

    //! Ratio of view port to window used to translate motion on the widget to that of the worl
    float ratio;

    //! Widget position of the mouse at the start of a pan event
    QPoint pan_start_;

    //! Window Position at the start of a pan event
    QPoint window_start_;

    //! Collection of paintable objects that are painted
    QVector<PaintableObject *> m_Misc_Paintables;

protected:
    //! Overide of base widget method
    void mousePressEvent(QMouseEvent *event) override;

    //! Overide of base widget method
    void mouseMoveEvent(QMouseEvent *event) override;

    //! Overide of base widget method
    void mouseReleaseEvent(QMouseEvent *event) override;

    //! Overide of base widget method
    void keyPressEvent(QKeyEvent *event) override;

    //! Overide of base widget method
    void wheelEvent(QWheelEvent *event) override;

    //! Overide of base widget method
    void paintEvent(QPaintEvent *event) override;

    //! Overide of base widget method
    void resizeEvent(QResizeEvent *event) override;

signals:
    //! Signal indicating mouse location
    void SignalMouseAt(QPointF worldPos );

public:
    //! Add misc paintable item to the canvas. Ownership is NOT passed to the canvas
    void Add_Misc_Paintable( PaintableObject * obj )
    {
        if ( obj != nullptr )
        {
            m_Misc_Paintables.append( obj );
        }
    }

    //! Update the canvas
    void UpdateCanvas()
    {
      update();
    }
};

#endif // PAINTCANVAS_H
