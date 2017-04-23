#include "oscillatorcontrol.h"
#include "rendervector.h"
#include <math.h>
#include <QLabel>
#include <QBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableWidget>

OscillatorControl::OscillatorControl(QString aName,QWidget *parent) : QWidget(parent)
{
    theFrequency = 1; // default values
    theFont = new QFont("Arial",11);
    theColor.setRgb(140,0,0);

    QVBoxLayout *main = new QVBoxLayout(this);
    main->setSpacing(0);
    main->setMargin(0);
    main->setContentsMargins(0,0,0,0);

    theName = aName;

    QHBoxLayout *title = new QHBoxLayout();
    l1 = new QLabel(parent);
    __setUptheLabel();
    title->addWidget(l1);

    ckEnabled = new QCheckBox("Enabled", parent);
    ckEnabled->setFont((*theFont));
    title->addWidget(ckEnabled);

    main->addLayout(title);

    QHBoxLayout *freq = new QHBoxLayout();
    freq->setSpacing(0);
    freq->setMargin(0);
    freq->setContentsMargins(0,0,0,0);
    QLabel *l2 = new QLabel(parent);
    l2->setText("Freq.");
    l2->setFont(*theFont);
    freq->addWidget(l2);

    InputFreq = new QLineEdit(parent);
    InputFreq->setFont(*theFont);
    InputFreq->setText(QString::number(theFrequency));
    InputFreq->setMaximumWidth(40);
    InputFreq->setFixedWidth(50);
    freq->addWidget(InputFreq);

    l2 = new QLabel(parent);
    l2->setText("Ampl.");
    l2->setFont(*theFont);
    freq->addWidget(l2);
    InputAmpl = new QLineEdit(parent);
    InputAmpl->setFont(*theFont);
    InputAmpl->setText(QString::number(theAmplitude));
    InputAmpl->setMaximumWidth(40);
    InputAmpl->setFixedWidth(50);
    freq->addWidget(InputAmpl);

    l2 = new QLabel(parent);
    l2->setText("Phase");
    l2->setFont(*theFont);
    freq->addWidget(l2);

  /*  InputPhas = new QLineEdit(parent);
    InputPhas->setFont(*theFont);
    InputPhas->setText(QString::number(thePhase));
    InputPhas->setMaximumWidth(40);
    InputPhas->setFixedWidth(50);
    freq->addWidget(InputPhas);
    */
    spinPhase = new QDoubleSpinBox(parent);
    spinPhase->setFont(*theFont);
    spinPhase->setRange(0.0, atan(1)*8 );
    spinPhase->setDecimals(2);
    spinPhase->setSingleStep(0.1);
    spinPhase->setValue(thePhase);
    spinPhase->setMaximumWidth(40);
    spinPhase->setFixedWidth(50);
    freq->addWidget(spinPhase);

    main->addLayout(freq);

    rend = new RenderVector(parent);
    main->addWidget(rend);
    main->addStretch();

    connect(ckEnabled, SIGNAL(stateChanged(int)), this, SLOT(__changeTheEnable(int)) );
    connect(InputFreq, SIGNAL(editingFinished()), this, SLOT(__changeTheParams()) );
    connect(InputAmpl, SIGNAL(editingFinished()), this, SLOT(__changeTheParams()) );
  //  connect(InputPhas, SIGNAL(editingFinished()), this, SLOT(__changeTheParams()) );
    connect(spinPhase, SIGNAL(valueChanged(double)), this, SLOT(__changeThePhase(double)) );
    connect(rend, SIGNAL(changeVector(float, float)), this, SLOT(__changeTheVector(float, float)) );

}

void OscillatorControl::__setUptheLabel()
{
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Background, theColor);

    l1->setText(theName);
    l1->setFont(QFont("Arial",10,3));
    l1->setAutoFillBackground(true);
    l1->setPalette(palette);
    return ;
}

void OscillatorControl::__changeThePhase(double p)
{
    __changeTheParams();
}

void OscillatorControl::__changeTheParams()
{
    bool isChanged =false;
    float fr = InputFreq->text().toFloat();
    float am = InputAmpl->text().toFloat();
 //   float ph = InputPhas->text().toFloat();
    float ph = spinPhase->value();
    if(theFrequency != fr) {
        theFrequency = fr;
        isChanged = true;
    }
    if(theAmplitude != am) {
        theAmplitude = am;
        isChanged = true;
    }
    if(thePhase != ph) {
        thePhase = ph;
        isChanged = true;
    }
    if(isChanged) {
        rend->setVector(theAmplitude, thePhase);
        __redraw();
    }
}

void OscillatorControl::__changeTheEnable(int e)
{
    bool en = (e == Qt::Checked) ? true : false;
    if(theEnabling != en) {
        theEnabling = en;
        __redraw();
    }
}

void OscillatorControl::__changeTheVector(float a, float p)
{
    if(theAmplitude != a || thePhase != p) {
        theAmplitude = a;
        thePhase = p;
        __redraw();
    }
}

void OscillatorControl::setParam(float f, float a, float p, bool e)
{
    bool isChanged = false;
    if(theFrequency != f) {theFrequency = f; isChanged=true;};
    if(theAmplitude != a) {theAmplitude = a; isChanged=true;};
    if(thePhase != p) {thePhase = p; isChanged=true;};
    if(theEnabling != e) {theEnabling = e; isChanged=true;};
    if(isChanged) {
        __redraw();
        rend->setVector(theAmplitude, thePhase);
    }
}



void OscillatorControl::__redraw()
{
    InputFreq->setText(QString::number(theFrequency));
    InputAmpl->setText(QString::number(theAmplitude));
  //  InputPhas->setText(QString::number(thePhase));
    spinPhase->setValue(thePhase);
    ckEnabled->setCheckState(theEnabling ? Qt::Checked : Qt::Unchecked);

    emit changeParam(theFrequency, theAmplitude, thePhase, theEnabling);

}
