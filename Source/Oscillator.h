/*
  ==============================================================================

    Oscillator.h
    Created: 6 May 2020 8:33:44pm
    Author:  Gordon Tenev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Oscillator    : public Component, private ComboBox::Listener
{
public:
    Oscillator();
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox*) override;
private:
    ComboBox oscMenu;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
