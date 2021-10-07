#ifndef PAINTCANVAS_H
#define PAINTCANVAS_H

#include <QWidget>

class PaintCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit PaintCanvas(QWidget *parent = nullptr);

signals:

public slots:
private:
    void resizeImage(QImage *image, const QSize &newSize);

    // Properties that need to be managed by the canvas   
    QPoint lastPoint;
    QRectF lastRect;
    QRectF lastEraserRect;
    QRect wind;



    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // PAINTCANVAS_H
