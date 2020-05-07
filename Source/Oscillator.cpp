/*
  ==============================================================================

    Oscillator.cpp
    Created: 6 May 2020 8:33:44pm
    Author:  Gordon Tenev

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator()
{
    setSize(200,200);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    oscMenu.addItem("Saw", 1);
    oscMenu.addItem("Square", 2);
    oscMenu.addItem("Triangle",3);
    oscMenu.addItem("Sine", 4);
    
    oscMenu.setSelectedId(1);
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
    
    oscMenu.setJustificationType(Justification::centred);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{

}

void Oscillator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(ComboBox* box){
    if (box == &oscMenu){
        //processor.osc1 = oscMenu.getSelectedItemIndex();
    }
}
