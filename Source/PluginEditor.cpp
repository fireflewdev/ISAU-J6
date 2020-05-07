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
    setSize (600, 400);
    
    volumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    volumeSlider.setRange(0, 127.0f);
    volumeSlider.setValue(100.0f);
    //volumeSlider.setTextBoxStyle(Slider::TextBoxAbove, true, 50.0, 20.0);
    //volumeSlider.setTextValueSuffix (" ms");
    volumeSlider.addListener(this);
    addAndMakeVisible(&volumeSlider);
    
    filterSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    filterSlider.setRange(20, 9000.0f);
    filterSlider.setValue(9000.0f);
    filterSlider.setTextBoxStyle(Slider::TextBoxAbove, true, 90.0, 20.0);
    ///filterSlider.setTextValueSuffix (" ms");
    filterSlider.addListener(this);
    addAndMakeVisible(&filterSlider);
    
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.1f);
    //attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    //attackSlider.setTextValueSuffix (" ms");
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 500.0f);
    decaySlider.setValue(500.0f);
    //decaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    //decaySlider.setTextValueSuffix (" ms");
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);
    
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(500.0f);
    //sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    sustainSlider.addListener(this);
    addAndMakeVisible(&sustainSlider);
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.0f, 5000.0f);
    releaseSlider.setValue(0.0f);
    //releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    //releaseSlider.setTextValueSuffix (" ms");
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);
    
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    
}

Isauj6AudioProcessorEditor::~Isauj6AudioProcessorEditor()
{
    //setLookAndFeel(nullptr);
}

//==============================================================================
void Isauj6AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    g.setColour (Colours::white);
    g.setFont (15.0f);
    
    g.drawFittedText ("ISAU J6 SYNTH", 0, 0, getWidth(), 30, Justification::centred, 1);
    g.drawFittedText ("Vol", getWidth()-60, 120, 50, 30, Justification::centred, 1);
    g.drawFittedText ("ADSR", 20, getHeight()-160, 140, 30, Justification::centred, 1);
    g.drawFittedText ("Filter", 160, getHeight()-160, 120, 30, Justification::centred, 1);
}

void Isauj6AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    int buff = 20;
    
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    //!!!!!!!
    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    volumeSlider.setBounds(getWidth()-buff*2,buff,20,100);
    
    filterSlider.setBounds(160+buff,getHeight()-100-buff,100,100);
    
    attackSlider.setBounds(buff,getHeight()-100-buff,20,100);
    decaySlider.setBounds(40+buff,getHeight()-100-buff,20,100);
    sustainSlider.setBounds(80+buff,getHeight()-100-buff,20,100);
    releaseSlider.setBounds(120+buff,getHeight()-100-buff,20,100);
}

void Isauj6AudioProcessorEditor::sliderValueChanged(Slider* slider){
    if (slider == &volumeSlider){
        processor.midiVolume = volumeSlider.getValue();
    }
    if (slider == &filterSlider){
        processor.filterVal = filterSlider.getValue();
    }
    if (slider == &attackSlider){
        processor.attackTime = attackSlider.getValue();
    }
    if (slider == &decaySlider){
        processor.decayTime = decaySlider.getValue();
    }
    if (slider == &sustainSlider){
        processor.sustainVal = sustainSlider.getValue();
    }
    if (slider == &releaseSlider){
        processor.releaseTime = releaseSlider.getValue();
    }
}
