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

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    //================
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        
    }
    //================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        
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
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        
    }
    //================
    
private:
    double level;
    double frequency;
};
