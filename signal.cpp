#include "signal.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

Signal::Signal(QWidget *parent) : QWidget(parent)
{

    showComponents = true;
    isDegree = false;
    ScaleRange = 15;

    t0 = 0;
    tend = 1;
    tstep = 0.005;
    theSignalColor.setRgb(5,5,5);

    QLineSeries *segnale = new QLineSeries();
    segnale->setPen(QPen(theSignalColor,3));
    segnale->setName("Signal");
    series.append( segnale );

    chart = new QChart();
     //  chart->legend()->hide();
       chart->addSeries(series.at(0));
       chart->createDefaultAxes();
       chart->setTitle("Signal composition");

    chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->setMinimumSize(QSize(800,400));

    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(chartView,0,0);

}

float Signal::redraw()
{
    int n = series.size(); // number of defined series
    if(showComponents) n = (n-1) / 2 +1;
    int m = sources.size();

    int i,j;
    float newValue, newSignal;
    float t;

    for(i=0;i<n;i++) series.at(i)->clear();
    t = t0;
    while (t<tend) {
        newSignal = 0;
        for(j=0;j<m;j++) {
            if(sources.at(j)->isEnabled()) {
                if(showComponents) {
                    newValue = sources.at(j)->setTick(t);
                    series.at(j*2+1)->append(t,sources.at(j)->getSinValue());
                    series.at(j*2+2)->append(t,sources.at(j)->getCosValue());
                } else {
                    newValue = sources.at(j)->setTick(t);
                    series.at(j+1)->append(t,newValue);
                }
                newSignal += newValue;
            }
        }
        series.at(0)->append(t,newSignal);
        t += tstep;
    }
    Value = newSignal;
    emit changeValue( Value );

   // chart->
    chart->createDefaultAxes();
    chart->axisY()->setRange(-ScaleRange,ScaleRange);
    chartView->repaint();

    return(0);
}

void Signal::setTimeBase(float ts, float te, float tick)
{
    t0 = (ts > te) ? te: ts;
    tend = (ts > te) ? ts : te;
    tstep = ((tend - t0) / 10 ) <= tick ? tick : tstep;
    redraw();
    return;
}



int Signal::addOscillator(QString Name, Oscillator *o)
{
    sources.append(o);
    if(showComponents) {
        QLineSeries *segnale = new QLineSeries();
        segnale->setColor(theSignalColor);
        segnale->setName(Name+" Sin");
        series.append( segnale );
        chart->addSeries(series.at(series.size()-1));

        segnale = new QLineSeries();
        segnale->setColor(theSignalColor);
        segnale->setName(Name+" Cos");
        series.append( segnale );
        chart->addSeries(series.at(series.size()-1));

    } else {
        QLineSeries *segnale = new QLineSeries();
        segnale->setColor(theSignalColor);
        segnale->setName(Name);
        series.append( segnale );
        chart->addSeries(series.at(series.size()-1));
    }
    chart->createDefaultAxes();
    connect(o, SIGNAL(paramChanged(float,float,float,bool)), this, SLOT(redraw(float, float, float, bool)));
    redraw();
    return(sources.size());
}


float Signal::setTick(float aTime)
{
    int i,n;
    float newValue = 0;
    n = sources.size();
    for(i=0;i<n;i++) {
        if(sources.at(i)->isEnabled())
            newValue += sources.at(i)->setTick(aTime);
    }
    Value = newValue;
    emit changeValue( Value );
    return(Value);
}

void Signal::setOscillatorColor(int i, QColor c)
{
    if(showComponents) {
        series.at((i-1)*2+1)->setColor(c);
        QColor c1;
        c1.setHsl(c.hslHue(), c.hslSaturation(), c.lightness()-30);
        series.at((i)*2)->setColor(c1);
    } else {
        series.at(i)->setColor(c);
    }
}
