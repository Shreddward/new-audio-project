#include "PluginProcessor.h"
#include "PluginEditor.h"

NewAudioProjectAudioProcessor::NewAudioProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : juce::AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput ("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
}

void NewAudioProjectAudioProcessor::prepareToPlay (double, int) {}
void NewAudioProjectAudioProcessor::releaseResources() {}

bool NewAudioProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    const auto& mainOut = layouts.getMainOutputChannelSet();
    if (mainOut != juce::AudioChannelSet::mono() && mainOut != juce::AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainInputChannelSet() != mainOut)
        return false;
#endif
    return true;
#endif
}

void NewAudioProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
#if ! JucePlugin_IsSynth
    for (int ch = getTotalNumInputChannels(); ch < getTotalNumOutputChannels(); ++ch)
        buffer.clear (ch, 0, buffer.getNumSamples());
#endif
}

juce::AudioProcessorEditor* NewAudioProjectAudioProcessor::createEditor()
{
    return new NewAudioProjectAudioProcessorEditor (*this);
}

void NewAudioProjectAudioProcessor::getStateInformation (juce::MemoryBlock&) {}
void NewAudioProjectAudioProcessor::setStateInformation (const void*, int) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewAudioProjectAudioProcessor();
}
