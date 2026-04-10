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
    ),
#endif
      apvts (*this, nullptr, "PARAMS", createParameterLayout())
{
}

void NewAudioProjectAudioProcessor::prepareToPlay (double, int)
{
    lastPitchBendValue = -1;
    lastModWheelValue = -1;
}

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

void NewAudioProjectAudioProcessor::pushPerformanceControllers (juce::MidiBuffer& midi)
{
    const auto pitchNorm = apvts.getRawParameterValue ("pitchBend")->load(); // -1..1
    const auto modNorm = apvts.getRawParameterValue ("modWheel")->load();    // 0..1

    const int pitch14 = juce::jlimit (0, 16383, (int) std::lround (8192.0f + pitchNorm * 8191.0f));
    const int mod7 = juce::jlimit (0, 127, (int) std::lround (modNorm * 127.0f));

    if (pitch14 != lastPitchBendValue)
    {
        midi.addEvent (juce::MidiMessage::pitchWheel (1, pitch14), 0);
        lastPitchBendValue = pitch14;
    }

    if (mod7 != lastModWheelValue)
    {
        midi.addEvent (juce::MidiMessage::controllerEvent (1, 1, mod7), 0); // CC1
        lastModWheelValue = mod7;
    }
}

void NewAudioProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

#if ! JucePlugin_IsSynth
    for (int ch = getTotalNumInputChannels(); ch < getTotalNumOutputChannels(); ++ch)
        buffer.clear (ch, 0, buffer.getNumSamples());
#endif

    keyboardState.processNextMidiBuffer (midiMessages, 0, buffer.getNumSamples(), true);
    pushPerformanceControllers (midiMessages);

    const float gain = apvts.getRawParameterValue ("masterGain")->load();
    buffer.applyGain (gain);
}

juce::AudioProcessorEditor* NewAudioProjectAudioProcessor::createEditor()
{
    return new NewAudioProjectAudioProcessorEditor (*this);
}

juce::AudioProcessorValueTreeState::ParameterLayout NewAudioProjectAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        "masterGain", "Master Gain",
        juce::NormalisableRange<float> (0.0f, 2.0f, 0.001f), 0.8f));

    params.push_back (std::make_unique<juce::AudioParameterInt> (
        "octaveShift", "Octave Shift", -2, 2, 0));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        "pitchBend", "Pitch Bend",
        juce::NormalisableRange<float> (-1.0f, 1.0f, 0.0001f), 0.0f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        "modWheel", "Mod Wheel",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.0001f), 0.0f));

    return { params.begin(), params.end() };
}

void NewAudioProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    const auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void NewAudioProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary (data, sizeInBytes));
    if (xml != nullptr && xml->hasTagName (apvts.state.getType()))
        apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewAudioProjectAudioProcessor();
}
