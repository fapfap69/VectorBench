#include "oscillator.h"

float Oscillator::PIh = asin(1.0);
float Oscillator::PI = asin(1.0) * 2;
float Oscillator::PI2 = asin(1.0) * 4;

Oscillator::Oscillator(float aFrequence)
{
    Amplitude = 1;
    Frequence = aFrequence;
    Phase = 0;
    SinAmp =  Amplitude*sin(Phase);
    CosAmp = Amplitude*cos(Phase);
    Enabled = false;
}

Oscillator::Oscillator(float aFrequence, float aAmplitude, float aPhase)
{
    Amplitude = aAmplitude;
    Frequence = aFrequence;
    Phase = __correctPhase(aPhase);
    SinAmp =  Amplitude*sin(Phase);
    CosAmp = Amplitude*cos(Phase);

}

float Oscillator::__correctPhase(float aPhase)
{
    aPhase = fmod(aPhase, PI2); // normalise to 2 PI
    if(aPhase < 0){
        aPhase = PI2 - aPhase;
    }
    return(aPhase);
}

void Oscillator::invert(void)
{
    Phase = __correctPhase( Phase + PI );
    return;
}

void Oscillator::add( Oscillator* o)
{
    float A,B,a,b;
    A = Amplitude;
    a = Phase;
    B = o->getAmplitude();
    b = o->getPhase();

    Amplitude = sqrt( A*A + B*B + (2*A*B*cos( fabs(a-b) )));
    Phase = atan((A*sin(a)+B*sin(b))/(A*cos(a)+B*cos(b)));
    return;
}

void Oscillator::copy(Oscillator* o)
{
    Frequence = o->getFrequency();
    Amplitude = o->getAmplitude();
    Phase = o->getPhase();
    setTick( o->getTime() );
    return;
}

void Oscillator::sub(Oscillator* o)
{
    Oscillator temp(o->getFrequency(),o->getAmplitude(),o->getPhase());
    temp.invert();
    add(&temp);
    return;
}

void Oscillator::multiply(float Amp)
{
    Amplitude *= Amp;
    return;
}

float Oscillator::setTick(float aTime, float *sinVal, float *cosVal)
{
    Time = aTime;
    float t = PI2 * Frequence * Time;

    Value = Amplitude * sin(t + Phase);
    SinComp = SinAmp *cos(t);
    CosComp = CosAmp *sin(t);
    *sinVal = SinComp;
    *cosVal = CosComp;

    emit valueChanged(Value);
    return(Value);

}
float Oscillator::setTick(float aTime)
{
    float a,b;
    return(setTick(aTime,&a,&b));
}

void Oscillator::setParam(float f, float a, float p, bool e)
{
    Frequence = f;
    Amplitude = a;
    Phase = __correctPhase(p);
    Enabled = e;
    SinAmp =  Amplitude*sin(Phase);
    CosAmp = Amplitude*cos(Phase);

    emit paramChanged(Frequence, Amplitude, Phase, Enabled);
}
