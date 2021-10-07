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
    // Set focus - focus
    setFocus();

    // Set drawing true based on button press
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Left Mouse Press " << rect();
        wind = QRect(300,300,400,400);
    }
    else if(event->button() == Qt::RightButton){
        qDebug() << "Left Mouse Press " << rect();
        wind = QRect(-500,-500,1000,1000);
    }
    update();
}

void PaintCanvas::mouseMoveEvent(QMouseEvent *event)
{
    // If drawing is active and there is a move then draw
    if ((event->buttons() & Qt::LeftButton)){
        qDebug() << "Left Mouse Move Event";
    }
}

void PaintCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Left Mouse Relese";
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
    // https://web.mit.edu/~firebird/arch/sun4x_59/doc/html/coordsys.html
    QPen pen;  // creates a default pen
    QBrush brush;
    QPainter painter(this);


   /* QRect cur_rect = rect();
    int cur_width = cur_rect.width();
    int cur_height = cur_rect.height();
    painter.setWindow( -cur_height,-cur_height/2, cur_width,cur_height );*/
    painter.setWindow( wind );


    QRect v = painter.viewport();
    int d = qMin( v.width(), v.height() );
    painter.setViewport( v.left() + (v.width()-d)/2,
                       v.top() + (v.height()-d)/2, d, d );


    QRectF rectToDraw(QPointF(-500.0,-500.0),QSizeF(1000.0,1000.0));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(3);
    pen.setBrush(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(Qt::white);

    painter.drawRect(rectToDraw);

    QRectF testRect(QPointF(450.0,450.0),QSizeF(100.0,150.0));
    painter.drawRect(testRect);

    painter.setPen(Qt::gray);
    for (int x = -500; x < 500; x+=100) {
        painter.drawLine(x,-500,x,500);
    }
    for (int y = -500; y < 500; y+=100) {
        painter.drawLine(-500,y,500,y);
    }

    painter.drawEllipse(QPoint(0,0),10,10);
}

void PaintCanvas::resizeEvent(QResizeEvent *event)
{
    update();
    qDebug() << "Resize Event";

    QWidget::resizeEvent(event);
}
