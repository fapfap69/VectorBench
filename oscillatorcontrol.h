#ifndef OSCILLATORCONTROL_H
#define OSCILLATORCONTROL_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>

#include "rendervector.h"

class OscillatorControl : public QWidget
{
    Q_OBJECT
public:
    explicit OscillatorControl(QWidget *parent = 0);
    OscillatorControl(const QString aName, QWidget *parent = 0);

     void setColor(QColor c) { theColor = c; __setUptheLabel(); }
     void setParam(float f, float a, float p, bool e);


signals:
    void changeParam(float Frequency, float Amplitude, float Phase, bool enabled);

public slots:

private:
     void __setUptheLabel();
     void __redraw();

private slots:
     void __changeThePhase(double);
     void __changeTheParams();
     void __changeTheVector(float, float);
     void __changeTheEnable(int);

private:
    QString theName;
    QFont *theFont;

    float theFrequency;
    float theAmplitude;
    float thePhase;
    bool theEnabling;

    QColor theColor;

    QLabel *l1;
    QLineEdit *InputFreq;
    QLineEdit *InputAmpl;
    QLineEdit *InputPhas;
    QCheckBox *ckEnabled;
    QDoubleSpinBox *spinPhase;

    RenderVector *rend;

};

#endif // OSCILLATORCONTROL_H
