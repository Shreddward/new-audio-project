#include "PluginEditor.h"

NewAudioProjectAudioProcessorEditor::NewAudioProjectAudioProcessorEditor (NewAudioProjectAudioProcessor& p)
    : juce::AudioProcessorEditor (&p), processor (p)
{
    setSize (900, 600);
}

void NewAudioProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour::fromRGB (15, 23, 42));
    g.setColour (juce::Colour::fromRGB (34, 211, 238));
    g.setFont (juce::Font (24.0f, juce::Font::bold));
    g.drawFittedText ("New Audio Project", getLocalBounds().reduced (24), juce::Justification::centredTop, 1);

    g.setColour (juce::Colour::fromRGB (148, 163, 184));
    g.setFont (juce::Font (14.0f));
    g.drawFittedText ("Baseline JUCE scaffold ready", getLocalBounds().reduced (24, 64), juce::Justification::centredTop, 1);
}

void NewAudioProjectAudioProcessorEditor::resized() {}
