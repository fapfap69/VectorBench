#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signal.h"
#include "Oscillator.h"
#include "oscillatorcontrol.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QBoxLayout>
#include <QLabel>
#include <QList>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent)
{
    theScaleRange = 15;
    showSinCosComponents = false;

    colorTable.append(QColor(10,10,10));
    colorTable.append(QColor(200,0,0));
    colorTable.append(QColor(0,200,0));
    colorTable.append(QColor(0,0,200));
    colorTable.append(QColor(200,200,0));
    colorTable.append(QColor(200,0,200));
    colorTable.append(QColor(0,200,200));


    QFont theFont("Arial",13);
    QColor theColor(0,0,60);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Background, theColor);


    // -----------------------
    QWidget *centralW = new QWidget(parent);
    QGridLayout *centralL = new QGridLayout(centralW);

    this->setWindowTitle("Oscillators Work Bench  v.0  - inFrAnto Software (CopyLeft)");
    QHBoxLayout *maincontrol = new QHBoxLayout();
    maincontrol->setSpacing(0);
    maincontrol->setMargin(0);
    maincontrol->setContentsMargins(5,0,0,0);

    QLabel *l = new QLabel("Range ");
    l->setFont(theFont);
    l->setAutoFillBackground(true);
    l->setPalette(palette);
    l->setMaximumWidth(90);
    maincontrol->addWidget(l);
    QSpinBox *sp = new QSpinBox();
    sp->setFont(theFont);
    sp->setRange(1,30);
    sp->setValue(theScaleRange);
    sp->setMaximumWidth(90);
    maincontrol->addWidget(sp);
    QCheckBox *co = new QCheckBox("Show sin() cos() components");
    co->setFont(theFont);
    co->setCheckState(Qt::Unchecked);
    maincontrol->addWidget(co);
    centralL->addLayout(maincontrol,0,1);

    primo = new Signal(this);
    _setUpOneOscillator("Primo",1,10,0,parent);
    _setUpOneOscillator("Secondo",1,10,0,parent);
    _setUpOneOscillator("Terzo",1,10,0,parent);
    _setUpOneOscillator("Quarto",1,10,0,parent);
    _setUpOneOscillator("Quinto",1,10,0,parent);

    centralL->addWidget(primo,1,1);

    QHBoxLayout *b2 = new QHBoxLayout();
    for(int i=0;i<Oscillators.size();i++)
        b2->addWidget(Oscillators.at(i));
    centralL->addLayout( b2,2,1);

    primo->show();
    for(int i=0;i<Oscillators.size();i++)
        Oscillators.at(i)->show();

    centralW->setLayout(centralL);
    setCentralWidget(centralW);

    connect(sp, SIGNAL(valueChanged(int)), primo, SLOT(setScaleRange(int)));
    connect(co, SIGNAL(stateChanged(int)), primo, SLOT(setShowComponents(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::__changeTheRange(int range)
{
    primo->setScaleRange(range);
}

void MainWindow::__changeTheShow(int)
{

}

void MainWindow::_setUpOneOscillator(QString Name, float freq, float ampl, float phas, QWidget *parent)
{
    Oscillator *osc;
    OscillatorControl *oscont;
    int i;
    osc = new Oscillator(freq,ampl,phas);
    i = primo->addOscillator(Name,osc);
    primo->setOscillatorColor(i,colorTable.at(i));
    primo->setOscillatorEnabled(i,false);
    oscont = new OscillatorControl(Name,parent);
    oscont->setColor(colorTable.at(i));
    oscont->setParam(freq,ampl,phas,false);
    connect(oscont, SIGNAL(changeParam(float,float,float,bool)),osc, SLOT(setParam(float,float,float,bool)));
    Oscillators.append(oscont);
}
