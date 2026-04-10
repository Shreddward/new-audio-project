#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class NewAudioProjectAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit NewAudioProjectAudioProcessorEditor (NewAudioProjectAudioProcessor&);
    ~NewAudioProjectAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    NewAudioProjectAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewAudioProjectAudioProcessorEditor)
};
