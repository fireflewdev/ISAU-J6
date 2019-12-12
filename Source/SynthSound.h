/*
  ==============================================================================

    SynthSound.h
    Created: 12 Dec 2019 12:18:10am
    Author:  Gordon Tenev

  ==============================================================================
*/
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
    bool appliesToNote(int /*midiNoteNumber*/){
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/){
        return true;
    }
};
