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
    
    void getAttackParam (std::atomic<float>* attack)
    {
        env1.setAttack(double(*attack));
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
        //ADSR! :)
        env1.setAttack(10);
        env1.setDecay(300); //30ms decay
        env1.setSustain(0.1); //between 0-1
        env1.setRelease(0); //10ms release
                        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.saw(frequency);
            double theSound = env1.adsr(theWave, env1.trigger) * level;
            double filteredSound = filter1.lores(theSound, 200, 0.1);

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
    double frequency;
    
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};
