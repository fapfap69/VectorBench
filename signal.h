#ifndef SIGNAL_H
#define SIGNAL_H

#include <QWidget>
#include <Oscillator.h>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QLayout>

QT_CHARTS_USE_NAMESPACE

class Signal : public QWidget
{
    Q_OBJECT

struct Source {
    QString Name;
    Oscillator *Osc;
    QColor Color;
    QColor Color2;

};

public:
    explicit Signal(QWidget *parent = 0);

    void setSignalColor(QColor c) { theSignalColor=c; series.at(0)->setColor(c);}
    int addOscillator(QString Name, Oscillator *o);
    void setOscillatorColor(int i, QColor c);
    void setOscillatorEnabled(int i, bool e) {sources.at(i-1)->Osc->setEnabled(e);}

signals:
    void changeValue(float newValue);

public slots:
    float setTick(float aTime);
    float redraw();
    void setTimeBase(float ts, float te, float tick=0.001);
    void redraw(float f, float a, float p, bool e) { redraw(); }
    void setScaleRange(int s) { ScaleRange = s; redraw(); }
    void setDegrees(bool d) { isDegree = d; }
    void setShowComponents(int c) { showComponents = c==Qt::Unchecked ?  false : true ; redraw(); }

private:
//    QList<Oscillator*> sources;

    QList<Source *>sources;

    float Time;
    float Value;

    float t0;
    float tend;
    float tstep;

    QColor theSignalColor;

    QList<QLineSeries*> series;

    QChart *chart;
    QChartView *chartView;
    QGridLayout* gridLayout;


    bool isDegree;
    bool showComponents;
    float ScaleRange;


};

#endif // SIGNAL_H
