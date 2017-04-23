#include "signal.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

Signal::Signal(QWidget *parent) : QWidget(parent)
{

    showComponents = false;
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
    int nSources = sources.size();
    chart->removeAllSeries();

  //  while(series.size() > 1) series.removeLast();
  //  series.at(0)->clear();

    QLineSeries *sourSignal;
    series.clear();

    sourSignal = new QLineSeries();
    sourSignal->setColor(theSignalColor);
    sourSignal->setName("Signal");
    series.append(sourSignal);


    for(int i=0;i<nSources;i++) {
        if(showComponents) {
            sourSignal = new QLineSeries();
            sourSignal->setColor(sources.at(i)->Color);
            sourSignal->setName(sources.at(i)->Name+" Sin");
            series.append( sourSignal );
            sourSignal = new QLineSeries();
            sourSignal->setColor(sources.at(i)->Color2);
            sourSignal->setName(sources.at(i)->Name+" Cos");
            series.append( sourSignal );
        } else {
            sourSignal = new QLineSeries();
            sourSignal->setColor(sources.at(i)->Color);
            sourSignal->setName(sources.at(i)->Name);
            series.append( sourSignal );
        }
    }

//    chart->removeAllSeries();
/*    for(int i = 0; i< chart->series().size(); ++i) {
        auto s = chart->series().last();
        chart->removeSeries(s);
        s->deleteLater();
    }
    */

    // --------
    int j;
    float newValue, newSignal;
    float t, si, co;

    t = t0;
    while (t<tend) {
        newSignal = 0;
        for(j=0;j<nSources;j++) {
            if(sources.at(j)->Osc->isEnabled()) {
                if(showComponents) {
                    newValue = sources.at(j)->Osc->setTick(t, &si, &co);
                    series.at(j*2+1)->append(t,si);
                    series.at(j*2+2)->append(t,co);
                } else {
                    newValue = sources.at(j)->Osc->setTick(t);
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

    for(int k=0;k<series.size();k++) {
        chart->addSeries(series.at(k));
    }
    chart->createDefaultAxes();
    chart->axisY()->setRange(-ScaleRange,ScaleRange);
    chartView->repaint();

    /*
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
*/
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
    Source *s= new Source;
    s->Name = Name;
    s->Color = theSignalColor;
    s->Color2 = theSignalColor;
    s->Osc = o;
    sources.append(s);
    connect(o, SIGNAL(paramChanged(float,float,float,bool)), this, SLOT(redraw(float, float, float, bool)));
    redraw();
    return(sources.size());
}
 /*
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
*/

float Signal::setTick(float aTime)
{
    int i,n;
    float newValue = 0;
    n = sources.size();
    for(i=0;i<n;i++) {
        if(sources.at(i)->Osc->isEnabled())
            newValue += sources.at(i)->Osc->setTick(aTime);
    }
    Value = newValue;
    emit changeValue( Value );
    return(Value);
}

void Signal::setOscillatorColor(int i, QColor c)
{
    sources.at(i-1)->Color = c;
    QColor c1;
    c1.setHsl(c.hslHue(), c.hslSaturation(), c.lightness()-30);
    sources.at(i-1)->Color2 = c1;

/*    if(showComponents) {
        series.at((i-1)*2+1)->setColor(c);
        QColor c1;
        c1.setHsl(c.hslHue(), c.hslSaturation(), c.lightness()-30);
        series.at((i)*2)->setColor(c1);
    } else {
        series.at(i)->setColor(c);
    }
    */
}
