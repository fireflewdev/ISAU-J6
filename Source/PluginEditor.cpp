/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Isauj6AudioProcessorEditor::Isauj6AudioProcessorEditor (Isauj6AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    
}

Isauj6AudioProcessorEditor::~Isauj6AudioProcessorEditor()
{
    //setLookAndFeel(nullptr);
}

//==============================================================================
void Isauj6AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    
    g.drawFittedText ("ISAU J6 SYNTH", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void Isauj6AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    attackSlider.setBounds(10,10,40,100);
}

void Isauj6AudioProcessorEditor::sliderValueChanged(Slider* slider){
    if (slider == &attackSlider){
        processor.attackTime = attackSlider.getValue();
    }
}
