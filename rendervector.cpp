#include "rendervector.h"

#include <math.h>
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>


RenderVector::RenderVector(QWidget *parent) : QWidget(parent)
{
    Maximum  = 10.0;
    divisions = 5;
    Amplitude = 10.0;
    Phase = 1.0;

    colorVector.setRgb(0,0,250);

    pen.setStyle( Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setColor(QColor(3,3,3));
    pen.setWidth(1);

    penVector.setStyle( Qt::SolidLine);
    penVector.setCapStyle(Qt::FlatCap);
    penVector.setJoinStyle(Qt::MiterJoin);
    penVector.setColor(colorVector);
    penVector.setWidth(3);

    brush.setColor(QColor(250,250,250));
    brush.setStyle(Qt::SolidPattern);



    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);


    // update();

}

void RenderVector::setVector(float a, float p)
{
    if(Amplitude == a && Phase == p) return;
    Amplitude = a;
    Phase = p;
    emit changeVector(a, p);
    update();
}

QSize RenderVector::sizeHint() const
{
    return QSize(251, 251);
}

QSize RenderVector::minimumSizeHint() const
{
    return QSize(101, 101);
}

void RenderVector::_calculateGeometry()
{
    // center coordinates
    xCent = (width() / 2) + (width() % 2);
    yCent = (height() / 2) + (height() % 2);
    // radius dimension
    radius = (std::min(xCent,yCent)-30);

    scale = (float)radius / Maximum;
    return;
}

void RenderVector::paintEvent(QPaintEvent * /* event */)
{
    _calculateGeometry();
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);

    painter.save();
    painter.translate(xCent, yCent);

    int step = radius / divisions;
    int i = step * divisions;
    while(i >= step) {
        painter.drawEllipse(QPoint(0,0), i, i);
        i -= step;
    }

    painter.drawLine(QPoint(0,-radius), QPoint(0,radius));
    painter.drawLine(QPoint(-radius,0), QPoint(radius,0));

    painter.drawLine(QPoint(-(radius),(radius+10)), QPoint((radius),(radius+10)) );
    painter.drawLine(QPoint(-(radius+10),-(radius)), QPoint(-(radius+10),(radius)) );

    painter.setPen(penVector);

    int a,b,c,d;
    _vect2comp(scale * Amplitude,Phase,&b, &a);
    painter.drawLine(QPoint(0,0), QPoint(a,-b) );
    _vect2comp(scale * Amplitude *.9,Phase-0.07,&d, &c);
    painter.drawLine(QPoint(a,-b), QPoint(c,-d) );
    _vect2comp(scale * Amplitude *.9,Phase+0.07,&d, &c);
    painter.drawLine(QPoint(a,-b), QPoint(c,-d) );


    painter.drawLine(QPoint(0,radius+10), QPoint(a,radius+10) );
    painter.drawLine(QPoint(-(radius+10),0), QPoint(-(radius+10),-b) );


    painter.restore();
}

void RenderVector::mousePressEvent(QMouseEvent *event)
{
    float a,p;
    QPointF mouseP = event->localPos();
    if(_positio2vector(mouseP.x() , mouseP.y() , &a, &p))
        setVector(a,p);
}

void RenderVector::mouseMoveEvent(QMouseEvent *event)
{
    float a,p;
    QPointF mouseP = event->localPos();
    if(_positio2vector(mouseP.x() , mouseP.y() , &a, &p))
        setVector(a,p);
}

void RenderVector::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF mouseP = event->localPos();
    qDebug() << "Mouse released " << mouseP.x() << " " << mouseP.y();

}


void RenderVector::_vect2comp(float amplitude, float phase, int *sincomp, int *coscomp)
{
    *sincomp = (int)(amplitude * sin(phase));
    *coscomp = (int)(amplitude * cos(phase));
}

bool RenderVector::_positio2vector(int x, int y, float *amplitude, float *phase)
{
    int rx = x - xCent;
    int ry = y - yCent;
    float cosine = rx / scale;
    float sine = -ry / scale;
    float amp = sqrt(cosine * cosine + sine * sine);
    if(amp>Maximum) return(false);
    float ph =atan( sine / cosine);
    if(cosine<0) ph += atan(1.0)*4;
    else if(sine<0) ph += atan(1.0)*8;

    *phase = ph;
    *amplitude = amp;
    return(true);
}
