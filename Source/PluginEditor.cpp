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
    
    //Osc1 select
    oscMenu.addItem("Saw", 1);
    oscMenu.addItem("Square", 2);
    oscMenu.addItem("Triangle",3);
    oscMenu.addItem("Sine", 4);
    oscMenu.setSelectedId(1);
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
    oscMenu.setJustificationType(Justification::centred);
    
    //Osc1 detune
    oscDetune.setSliderStyle(Slider::SliderStyle::Rotary);
    oscDetune.setRange(-10.0f, 10.0f);
    oscDetune.setValue(0);
    oscDetune.setTextBoxStyle(Slider::TextBoxBelow, true, 0, 0);
    oscDetune.addListener(this);
    addAndMakeVisible(&oscDetune);
    
    //Osc1 detune label
    addAndMakeVisible (detuneLabel1);
    detuneLabel1.setText ("Detune\n" + to_string(0.0f).substr(0,4) + " Hz", dontSendNotification);
    detuneLabel1.setColour (Label::textColourId, Colours::orange);
    detuneLabel1.setJustificationType (Justification::centred);
    
    //Osc1 octave
    oscOctave.addItem("+1",3);
    oscOctave.addItem("0", 2);
    oscOctave.addItem("-1", 1);
    oscOctave.setSelectedId(2);
    addAndMakeVisible(&oscOctave);
    oscOctave.addListener(this);
    oscOctave.setJustificationType(Justification::centred);
    
    //Osc2 select
    osc2Menu.addItem("Saw", 1);
    osc2Menu.addItem("Square", 2);
    osc2Menu.addItem("Triangle",3);
    osc2Menu.addItem("Sine", 4);
    osc2Menu.setSelectedId(1);
    addAndMakeVisible(&osc2Menu);
    osc2Menu.addListener(this);
    osc2Menu.setJustificationType(Justification::centred);
    
    //Osc2 detune
    osc2Detune.setSliderStyle(Slider::SliderStyle::Rotary);
    osc2Detune.setRange(-10.0f, 10.0f);
    osc2Detune.setValue(0);
    osc2Detune.setTextBoxStyle(Slider::TextBoxBelow, true, 0, 0);
    osc2Detune.addListener(this);
    addAndMakeVisible(&osc2Detune);
    
    //Osc2 detune label
    addAndMakeVisible (detuneLabel2);
    detuneLabel2.setText ("Detune\n" + to_string(0.0f).substr(0,4) + " Hz", dontSendNotification);
    detuneLabel2.setColour (Label::textColourId, Colours::orange);
    detuneLabel2.setJustificationType (Justification::centred);
    
    //Osc2 octave
    osc2Octave.addItem("+1",3);
    osc2Octave.addItem("0", 2);
    osc2Octave.addItem("-1", 1);
    osc2Octave.setSelectedId(2);
    addAndMakeVisible(&osc2Octave);
    osc2Octave.addListener(this);
    osc2Octave.setJustificationType(Justification::centred);
    
    //Osc mix
    oscSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscSlider.setRange(0, 1.0f);
    oscSlider.setValue(0.5f);
    oscSlider.addListener(this);
    addAndMakeVisible(&oscSlider);
    
    //Vol
    volumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    volumeSlider.setRange(0.0f, 100.0f);
    volumeSlider.setValue(50.0f);
    //volumeSlider.setTextBoxStyle(Slider::TextBoxAbove, true, 50.0, 20.0);
    //volumeSlider.setTextValueSuffix (" ms");
    volumeSlider.addListener(this);
    addAndMakeVisible(&volumeSlider);
    
    //Filter
    filterSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    filterSlider.setRange(20, 9000.0f);
    filterSlider.setValue(9000.0f);
    filterSlider.setTextBoxStyle(Slider::TextBoxAbove, true, 0, 0);
    ///filterSlider.setTextValueSuffix (" ms");
    filterSlider.addListener(this);
    addAndMakeVisible(&filterSlider);
    
    //Filter label
    addAndMakeVisible (filterLabel);
    filterLabel.setText ("Lowpass filter", dontSendNotification);
    filterLabel.setColour (Label::textColourId, Colours::white);
    filterLabel.setJustificationType (Justification::centred);
    filterLabel.attachToComponent (&filterSlider, false);
    
    //ADSR
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
    sustainSlider.setRange(0.01f, 1.0f);
    sustainSlider.setValue(500.0f);
    //sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    sustainSlider.addListener(this);
    addAndMakeVisible(&sustainSlider);
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(0.1f);
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
    
    g.drawFittedText ("Vol", getWidth()-50, 120, 50, 30, Justification::centred, 1);
    g.drawFittedText ("Mix", 280, 160, 40, 30, Justification::centred, 1);
    g.drawFittedText ("ADSR", 20, getHeight()-160, 140, 30, Justification::centred, 1);
    g.drawFittedText ("A subtractive synth by Fireflew", getWidth()-220, getHeight()-50, 200, 30, Justification::bottomRight, 1);
    
    g.setFont (30.0f);
    g.drawFittedText ("ISAU-J6", getWidth()-220, getHeight()-80, 200, 30, Justification::bottomRight, 1);

}

void Isauj6AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    int buff = 20;
    
    //!!!!!!!
    oscMenu.setBounds(buff, buff, 100, 60);
    oscDetune.setBounds(buff+110, buff, 60, 60);
    detuneLabel1.setBounds(buff+90, buff+40, 100, 60);
    oscOctave.setBounds(buff+190, buff, 60, 40);
    
    osc2Menu.setBounds(buff, buff*2+80, 100, 60);
    osc2Detune.setBounds(buff+110, buff*2+80, 60, 60);
    detuneLabel2.setBounds(buff+90, buff*2+120, 100, 60);
    osc2Octave.setBounds(buff+190, buff*2+80, 60, 40);
    
    oscSlider.setBounds(buff+270, buff, 20, 120+buff);
    
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
    if (slider == &oscSlider){
        processor.oscMix = oscSlider.getValue();
    }
    if (slider == &oscDetune){
        float o = oscDetune.getValue();
        if (o < 0.5f && o > -0.5f){ //correct for small offsets when you obviously want to reset at 0
            o = 0;
        }
        string a;
        if (o == 0){
            a = "";
        } else if(o > 0){
            a = "+";
        } else {
            a = "-";
        }
        detuneLabel1.setText ("Detune\n" + a + to_string(abs(o)).substr(0,4) + " Hz", dontSendNotification);
        processor.oscDetune = o;
    }
    if (slider == &osc2Detune){
        float o = osc2Detune.getValue();
        if (o < 0.5f && o > -0.5f){ //correct for small offsets when you obviously want to reset at 0
            o = 0;
        }
        string a;
        if (o == 0){
            a = "";
        } else if(o > 0){
            a = "+";
        } else {
            a = "-";
        }
        detuneLabel2.setText ("Detune\n" + a + to_string(abs(o)).substr(0,4) + " Hz", dontSendNotification);
        processor.osc2Detune = o;
    }
}

void Isauj6AudioProcessorEditor::comboBoxChanged(ComboBox* box){
    if (box == &oscMenu){
        processor.oscillator = oscMenu.getSelectedId();
    }
    if (box == &osc2Menu){
        processor.oscillator2 = osc2Menu.getSelectedId();
    }
    if (box == &oscOctave){
        processor.oscOctave = oscOctave.getSelectedId();
    }
    if (box == &osc2Octave){
        processor.osc2Octave = osc2Octave.getSelectedId();
    }
}
