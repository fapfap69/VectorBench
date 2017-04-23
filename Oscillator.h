#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <QObject>
#include <QWidget>
#include <math.h>

class Oscillator : public QObject
{

  Q_OBJECT

public:
    Oscillator(float Frequency);
    Oscillator(float Frequency, float Amplitude, float Phase = 0);


signals:
    void valueChanged(int newValue);
    void paramChanged(float f, float a, float p, bool e);

public slots:
    float setTick(float aTime);
    void setParam(float f, float a, float p, bool e);

public:
    static float PI;
    static float PI2;
    static float PIh;

public:
    float getAmplitude() { return(Amplitude);}
    float getPhase(bool isDegree = false) { return(Phase * (isDegree ?  (180.0 / PI) : 1) ); }
    float getFrequency() { return(Frequence);}
    float getSinAmplitude() { return(Amplitude*sin(Phase)); }
    float getCosAmplitude() { return(Amplitude*cos(Phase)); }
    bool isEnabled() { return(Enabled); }

    float getTime() { return(Time); }
    float getValue() { return(Value); }
    float getSinValue() { return(SinComp); }
    float getCosValue() { return(CosComp); }

    void setAmplitude(float aAmplitude) { Amplitude = aAmplitude; }
    void setPhase(float aPhase, bool isDegree = false) { Phase = __correctPhase( aPhase * (isDegree ?  (PI / 180.0) : 1)); }
    void setFrequency(float aFrequence) { Frequence = aFrequence;}
    void setEnabled(bool e) {Enabled = e;}

    void invert(void);
    void add( Oscillator* o);
    void copy(Oscillator* o);
    void sub(Oscillator* o);
    void multiply(float Amp);

private:
    float __correctPhase(float aPhase);

private:
    bool isDegree;
    float Amplitude;
    float Phase;
    float Frequence;
    bool Enabled;

    float Time;
    float Value;
    float SinComp;
    float CosComp;
};


#endif // OSCILLATOR_H
