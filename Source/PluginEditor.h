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
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    void setOctaveShift (int newShift);
    int getOctaveShift() const;
    void applyOctaveShiftToKeyboard (int shift);

    NewAudioProjectAudioProcessor& processor;

    juce::MidiKeyboardComponent keyboardComponent;
    juce::TextButton octaveDownButton { "Oct -" };
    juce::TextButton octaveUpButton   { "Oct +" };
    juce::Label octaveLabel;

    juce::Slider masterGainSlider;
    juce::Slider pitchWheelSlider;
    juce::Slider modWheelSlider;

    std::unique_ptr<SliderAttachment> masterGainAttachment;
    std::unique_ptr<SliderAttachment> pitchAttachment;
    std::unique_ptr<SliderAttachment> modAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewAudioProjectAudioProcessorEditor)
};
