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
        std::cout << midiNoteNumber << std::endl;
    }
    //================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        //clearCurrentNote();
        if(velocity == 0)
        {
            clearCurrentNote();
        }
    }
    //================
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
                        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.saw(frequency);
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
    double level;
    double filterAmnt;
    double frequency;
    
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};
