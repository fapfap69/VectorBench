#ifndef RENDERVECTOR_H
#define RENDERVECTOR_H

#include <QWidget>
#include <QPen>

class RenderVector : public QWidget
{
    Q_OBJECT
public:
    explicit RenderVector(QWidget *parent = 0);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void setColor(QColor c) { colorVector = c; update(); }

signals:
    void changeVector(float a, float p);

public slots:
    void setVector(float a, float p);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void _vect2comp(float amplitude, float phase, int *sincomp, int *coscomp);
    void _calculateGeometry();
    bool _positio2vector(int x, int y, float *ampitude, float *phase);

private:
    QPen pen;
    QPen penVector;
    QBrush brush;
    QPixmap pixmap;
    QColor colorVector;


    float Amplitude;
    float Phase;

    int xCent;
    int yCent;
    int radius;
    float scale;
    float Maximum;
    int divisions;


};

#endif // RENDERVECTOR_H
