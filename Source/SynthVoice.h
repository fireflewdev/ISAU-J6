/*
  ==============================================================================

    SynthVoice.h
    Created: 12 Dec 2019 12:18:23am
    Author:  Gordon Tenev

  ==============================================================================
*/
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void setAttackParam (double e)
    {
        env1.setAttack(e);
    }
    
    void setDecayParam (double e)
    {
        env1.setDecay(e);
    }
    
    void setSustainParam (double e)
    {
        env1.setSustain(e);
    }
    
    void setReleaseParam (double e)
    {
        env1.setRelease(e);
    }
    
    void setOscillatorParams(int o1, int o2)
    {
        oscillator = o1;
        oscillator2 = o2;
    }
    
    void setDetuneParams(double o1, double o2)
    {
        oscDetune = o1;
        osc2Detune = o2;
        //std::cout <<"o "<< oscDetune << " " << osc2Detune << std::endl;
    }
    void setOctaveParams(int o1, int o2){
        octave = o1;
        octave2 = o2;
    }
    
    void setOscMixParam (double e)
    {
        oscMix = e;
        //std::cout <<"o "<< oscMix << std::endl;
    }
    
    
    void setFilterParam (double e)
    {
        filterAmnt = e;
        //std::cout <<"filter "<< e << std::endl;
    }
    
    static double noteHz(int midiNoteNumber, double centsOffset)
    {
        double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        hertz *= std::pow(2.0, centsOffset / 1200); // freq*(2^(centsoffset/1200)
        return hertz;
    }
    
    //==========================================
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = noteHz(midiNoteNumber, 0);
        //std::cout << midiNoteNumber << std::endl;
    }
    //================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        //clearCurrentNote();
        if(velocity <= 0.1)
        {
            clearCurrentNote();
        }
    }
    //================
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
                        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave;
            double o1;
            double o2;
            double multiplier1 = frequency*pow(2.0, (double)(octave-2));
            double multiplier2 = frequency*pow(2.0, (double)(octave2-2));
            double f1 = multiplier1 + oscDetune;
            double f2 = multiplier2 + osc2Detune;
            if (oscillator == 1)
            {
                o1 = osc1.saw(f1);
            }
            else if (oscillator == 2)
            {
                o1 = osc1.square(f1);
            }
            else if (oscillator == 3)
            {
                o1 = osc1.triangle(f1);
            }
            else
            {
                o1 = osc1.sinewave(f1);
            }
            
            if (oscillator2 == 1)
            {
                o2 = osc2.saw(f2);
            }
            else if (oscillator2 == 2)
            {
                o2 = osc2.square(f2);
            }
            else if (oscillator2 == 3)
            {
                o2 = osc2.triangle(f2);
            }
            else
            {
                o2 = osc2.sinewave(f2);
            }
            
            theWave = o1*oscMix+o2*(1-oscMix);
            
            double theSound = env1.adsr(theWave, env1.trigger) * level;
            double filteredSound = filter1.lores(theSound, filterAmnt, 0.1);

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, filteredSound);
            }
            ++startSample;
        }
    }
    //================
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    //================
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    //================
    
private:
    int oscillator;
    int oscillator2;
    int octave;
    int octave2;
    
    double oscDetune;
    double osc2Detune;
    
    double oscMix;
    
    double level;
    double filterAmnt;
    double frequency;
    
    maxiOsc osc1;
    maxiOsc osc2;
    maxiEnv env1;
    maxiFilter filter1;
};
