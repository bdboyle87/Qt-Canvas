#include "paintcanvas.h"
#include<QtGlobal>
#include <QPainter>
#include <QMouseEvent>

PaintCanvas::PaintCanvas(QWidget *parent) : QWidget(parent),
    lastRect(QRectF(0,0,0,0)),
    lastEraserRect(QRectF(0,0,0,0)),
    wind(-500,-500, 1000,1000 )
{
    QPainter painter(this);
}

void PaintCanvas::resizeImage(QImage *image, const QSize &newSize)
{

}

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
        window_start_ = wind.topLeft();
    }
    else if(event->button() == Qt::RightButton){
        // Reset Wind size
        wind = QRect(-500,-500,1000,1000);
    }
    update();
}

void PaintCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton)){

        // Calculate delta from start psotion
        QPoint delta = event->pos() - pan_start_;

        // Move the top left by the delta amount
        // Ratio is a mearue of the viewport size relative to the  window.
        wind.moveTopLeft(-(delta)/ratio + window_start_);
    }
    update();
}

void PaintCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

    }

}

void PaintCanvas::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        qDebug() << "Key Up";
        wind.moveTop(wind.top()+10);
    }
    else if(event->key() == Qt::Key_Down)
    {
        qDebug() << "Key Down";
        wind.moveBottom(wind.bottom()-10);
    }
    else if(event->key() == Qt::Key_Left)
    {
        qDebug() << "Key Left";
        wind.moveLeft(wind.left()-10);
    }
    else if(event->key() == Qt::Key_Right)
    {
        qDebug() << "Key Right";
        wind.moveRight(wind.right()+10);
    }
    else if(event->key() == Qt::Key_Z)
    {
        qDebug() << "Zoom";
        wind-=QMargins( 10,  10,  10,  10);
    }
    QWidget::keyPressEvent(event);
    update();
}

void PaintCanvas::paintEvent(QPaintEvent *event)
{
    // See window viewport details
    // 1. https://flylib.com/books/en/2.18.1/painting_with_qpainter.html
    // 2. https://web.mit.edu/~firebird/arch/sun4x_59/doc/html/coordsys.html

    QPen pen;  // creates a default pen
    QBrush brush;
    QPainter painter(this);


    // Set the window
    painter.setWindow( wind );
    v = painter.viewport();

    // Create non distorted view port of the logical space
    // Keep the aspect ratio
    d = qMin( v.width(), v.height() );
    painter.setViewport( v.left() + (v.width()-d)/2,
                        v.top() + (v.height()-d)/2, d, d );

    //Capture Min Wind dimension
    wind_min = qMin( wind.width(), wind.height() );

    // Create ratio of viewport and window. This is needed to pan the world and the view port and the window are differencet sizes.
    ratio = static_cast<float>(d) / static_cast<float>(wind_min);

    // Draw Space
    QRectF rectToDraw(QPointF(-500.0,-500.0),QSizeF(1000.0,1000.0));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(3);
    pen.setBrush(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawRect(rectToDraw);

    // Draw Grid
    painter.setPen(Qt::gray);
    for (int x = -500; x < 500; x+=100) {
        painter.drawLine(x,-500,x,500);
    }
    for (int y = -500; y < 500; y+=100) {
        painter.drawLine(-500,y,500,y);
    }

    // Draw Origin Elipse
    painter.drawEllipse(QPoint(0,0),10,10);

    // Additional Objects
    QRectF testRect(QPointF(450.0,450.0),QSizeF(100.0,150.0));
    painter.drawRect(testRect);
}

void PaintCanvas::resizeEvent(QResizeEvent *event)
{
    update();
    qDebug() << "Resize Event";

    QWidget::resizeEvent(event);
}
