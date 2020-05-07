/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Isauj6AudioProcessor::Isauj6AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
oscillator(1),
oscillator2(1),
midiVolume(70.0f),
oscMix(1.0f),
filterVal(9000.0f),
attackTime(0.1f),
decayTime(500.0f),
sustainVal(1.0f),
releaseTime(0.1f)

#endif
{
    /*NormalisableRange<float> attackParam (0.1f, 5000.0f);
    NormalisableRange<float> decayParam (0.1f, 500.0f);
    NormalisableRange<float> sustainParam (0.1f, 1.0f);*/
    mySynth.clearVoices();
    int voiceCount = 16;
    for(int i = 0; i < voiceCount; i++) //16 voice synth
    {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

Isauj6AudioProcessor::~Isauj6AudioProcessor()
{
    
}

//==============================================================================
const String Isauj6AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Isauj6AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Isauj6AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Isauj6AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Isauj6AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Isauj6AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Isauj6AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Isauj6AudioProcessor::setCurrentProgram (int index)
{
}

const String Isauj6AudioProcessor::getProgramName (int index)
{
    return {};
}

void Isauj6AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Isauj6AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void Isauj6AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Isauj6AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Isauj6AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        // ..do something to the data...
    }
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        SynthVoice *myVoice = dynamic_cast<SynthVoice *>(mySynth.getVoice(i));
        
        //volume
        MidiBuffer processedMidi;
        int time;
        MidiMessage m;
        
        for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
        {
            if (m.isNoteOn())
            {
                uint8 newVel = (uint8)midiVolume;
                m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
            }
            else if (m.isNoteOff())
            {
            }
            else if (m.isAftertouch())
            {
            }
            else if (m.isPitchWheel())
            {
            }
            
            processedMidi.addEvent (m, time);
        }
        
        midiMessages.swapWith (processedMidi);
        
        //oscillator
        myVoice->setOscillatorParam(oscillator);
        myVoice->setOscillator2Param(oscillator2);
        myVoice->setOscMixParam(oscMix);
        //filter
        myVoice->setFilterParam(filterVal);
        
        //ADSR
        myVoice->setAttackParam(attackTime);
        myVoice->setDecayParam(decayTime);
        myVoice->setSustainParam(sustainVal);
        myVoice->setReleaseParam(releaseTime);
    }
    buffer.clear();
    
    /*for (int v = 0; v < mySynth.getNumVoices(); v++) {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(v))))
        {
            
        }
    }*/
    
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Isauj6AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Isauj6AudioProcessor::createEditor()
{
    return new Isauj6AudioProcessorEditor (*this);
}

//==============================================================================
void Isauj6AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Isauj6AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Isauj6AudioProcessor();
}
