#ifndef PAINTABLEOBJECT_H
#define PAINTABLEOBJECT_H

#include <QPainter>

class PaintableObject
{
public:
    PaintableObject();
protected:
    QColor color_;

    bool should_paint_;

public:
    explicit PaintableObject( QColor color = Qt::white, bool should_paint = true ) :
        color_( color ),
        should_paint_( should_paint )
    {}

    virtual ~PaintableObject() {}

    void SetColor( QColor c ) { color_ = c; }

    bool ShouldPaint()
    {
        return ( should_paint_ );
    }

    void SetShouldPaint( bool should_paint ) { should_paint_ = should_paint; }

    //! Paint the object's representation using the supplied QPainter
    virtual void UIPaint( QPainter & painter ) = 0;

    //! Make a snapshot of information needed for the upcoming paint
    //! so that all painting will be at essentially the same relative time
    //virtual void UIPaintPrepare() = 0;
};


class PaintableCircle : public PaintableObject
{
public:
    QPointF m_PointF;
    double  m_Radius;
    bool    m_Filled;

    PaintableCircle( QPointF p1, double radius, QColor color = Qt::blue, bool filledI = true ):
    PaintableObject( color )
    {
        Set( p1, radius, color, filledI );
    }

    void Set( QPointF p1, double radius, QColor color = Qt::white, bool filledI = true )
    {
        m_PointF = p1;
        m_Radius = radius;
        m_Filled = filledI;

        SetColor( color );
    }

    virtual ~PaintableCircle() {}

    void UIPaint( QPainter & painter, double penWidth )
    {
        painter.setBrush( m_Filled ? QBrush( color_ ) : QBrush( color_ ) );
        painter.setPen( QPen( QBrush( color_ ), penWidth, Qt::SolidLine, Qt::FlatCap ) );

        QBrush brush(Qt::blue,Qt::SolidPattern);
        painter.setBrush(brush);

        if(painter.brush().style() == Qt::NoBrush)
        {
            painter.drawArc( QRectF( m_PointF.x() - m_Radius, m_PointF.y() - m_Radius, m_Radius * 2, m_Radius * 2 ),
                            0,
                            360 * 16 );
        }
        else
        {
            painter.drawPie( QRectF( m_PointF.x() - m_Radius, m_PointF.y() - m_Radius, m_Radius * 2, m_Radius * 2 ),
                            0,
                            360 * 16 );
        }

    }

    virtual void UIPaint( QPainter & painter ) Q_DECL_OVERRIDE { UIPaint( painter, 0 ); }
};

#endif // PAINTABLEOBJECT_H
