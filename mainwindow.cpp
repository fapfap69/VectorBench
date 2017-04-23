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

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent)
{
    theScaleRange = 15;
    showSinCosComponents = false;


    QFont theFont("Arial",13);
    QColor theColor(0,0,60);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Background, theColor);

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
    Oscillator *osc;

    int i;
    osc = new Oscillator(1,10,0);
    i = primo->addOscillator("Primo",osc);
    primo->setOscillatorColor(i,QColor(180,0,0));
    primo->setOscillatorEnabled(i,true);
    OscillatorControl *osco1 = new OscillatorControl("Primo",parent);
    osco1->setColor(QColor(180,0,0));
    osco1->setParam(1,10,0, true);
    connect(osco1, SIGNAL(changeParam(float,float,float,bool)),
                 osc, SLOT(setParam(float,float,float,bool)));


    osc = new Oscillator(1,10,Oscillator::PIh);
    i = primo->addOscillator("Secondo",osc);
    primo->setOscillatorColor(i,QColor(0,180,0));
    OscillatorControl *osco2 = new OscillatorControl("Seondo",parent);
    osco2->setColor(QColor(0,180,0));
    osco2->setParam(1,10,Oscillator::PIh, false);
    connect(osco2, SIGNAL(changeParam(float,float,float,bool)),
                     osc, SLOT(setParam(float,float,float,bool)));

    osc = new Oscillator(4,0.1,0);
    i = primo->addOscillator("Terzo",osc);
    primo->setOscillatorColor(i,QColor(0,0,180));
    OscillatorControl *osco3 = new OscillatorControl("Terzo",parent);
    osco3->setColor(QColor(0,0,180));
    osco3->setParam(4,0.1,0, false);
    connect(osco3, SIGNAL(changeParam(float,float,float,bool)),
                     osc, SLOT(setParam(float,float,float,bool)));

    osc = new Oscillator(8,0.1,0);
    i = primo->addOscillator("Quarto",osc);
    primo->setOscillatorColor(i,QColor(140,0,140));
    OscillatorControl *osco4 = new OscillatorControl("Quarto",parent);
    osco4->setColor(QColor(140,0,140));
    osco4->setParam(8,0.1,0, false);
    connect(osco4, SIGNAL(changeParam(float,float,float,bool)),
                     osc, SLOT(setParam(float,float,float,bool)));

    centralL->addWidget(primo,1,1);

    QHBoxLayout *b2 = new QHBoxLayout();
    b2->addWidget(osco1);
    b2->addWidget(osco2);
    b2->addWidget(osco3);
    b2->addWidget(osco4);
    centralL->addLayout( b2,2,1);

    primo->show();
    osco1->show();
    osco2->show();
    osco3->show();
    osco4->show();

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
