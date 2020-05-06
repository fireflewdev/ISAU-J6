/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/


class Isauj6AudioProcessorEditor  : public AudioProcessorEditor,
public Slider::Listener

{
public:
    Isauj6AudioProcessorEditor (Isauj6AudioProcessor&);
    ~Isauj6AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Isauj6AudioProcessor& processor;
    
    
    Slider attackSlider; // [2]
    Label attackLabel;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Isauj6AudioProcessorEditor)
};
