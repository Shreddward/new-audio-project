#include "PluginEditor.h"

NewAudioProjectAudioProcessorEditor::NewAudioProjectAudioProcessorEditor (NewAudioProjectAudioProcessor& p)
    : juce::AudioProcessorEditor (&p),
      processor (p),
      keyboardComponent (processor.getKeyboardState(), juce::MidiKeyboardComponent::horizontalKeyboard)
{
    setSize (980, 640);

    addAndMakeVisible (keyboardComponent);
    keyboardComponent.setKeyWidth (26.0f);

    addAndMakeVisible (octaveDownButton);
    addAndMakeVisible (octaveUpButton);
    addAndMakeVisible (octaveLabel);
    octaveLabel.setJustificationType (juce::Justification::centred);

    octaveDownButton.onClick = [this] { setOctaveShift (getOctaveShift() - 1); };
    octaveUpButton.onClick = [this]   { setOctaveShift (getOctaveShift() + 1); };

    masterGainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    masterGainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 20);
    masterGainSlider.setTextValueSuffix (" x");
    addAndMakeVisible (masterGainSlider);

    pitchWheelSlider.setSliderStyle (juce::Slider::LinearVertical);
    pitchWheelSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 20);
    addAndMakeVisible (pitchWheelSlider);

    modWheelSlider.setSliderStyle (juce::Slider::LinearVertical);
    modWheelSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 20);
    addAndMakeVisible (modWheelSlider);

    auto& apvts = processor.getValueTreeState();
    masterGainAttachment = std::make_unique<SliderAttachment> (apvts, "masterGain", masterGainSlider);
    pitchAttachment      = std::make_unique<SliderAttachment> (apvts, "pitchBend", pitchWheelSlider);
    modAttachment        = std::make_unique<SliderAttachment> (apvts, "modWheel", modWheelSlider);

    applyOctaveShiftToKeyboard (getOctaveShift());
}

int NewAudioProjectAudioProcessorEditor::getOctaveShift() const
{
    if (auto* raw = processor.getValueTreeState().getRawParameterValue ("octaveShift"))
        return juce::roundToInt (raw->load());

    return 0;
}

void NewAudioProjectAudioProcessorEditor::setOctaveShift (int newShift)
{
    newShift = juce::jlimit (-2, 2, newShift);

    if (auto* param = processor.getValueTreeState().getParameter ("octaveShift"))
    {
        param->beginChangeGesture();
        param->setValueNotifyingHost (param->convertTo0to1 ((float) newShift));
        param->endChangeGesture();
    }

    applyOctaveShiftToKeyboard (newShift);
}

void NewAudioProjectAudioProcessorEditor::applyOctaveShiftToKeyboard (int shift)
{
    const int lowest = juce::jlimit (0, 67, 36 + shift * 12);
    keyboardComponent.setAvailableRange (lowest, lowest + 60);
    keyboardComponent.setLowestVisibleKey (lowest);

    const juce::String sign = (shift >= 0 ? "+" : "");
    octaveLabel.setText ("Octave " + sign + juce::String (shift), juce::dontSendNotification);
}

void NewAudioProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour::fromRGB (15, 23, 42));

    g.setColour (juce::Colour::fromRGB (34, 211, 238));
    g.setFont (juce::Font (24.0f, juce::Font::bold));
    g.drawFittedText ("Performance Scaffold", getLocalBounds().removeFromTop (40), juce::Justification::centred, 1);

    g.setColour (juce::Colour::fromRGB (148, 163, 184));
    g.setFont (juce::Font (14.0f));
    g.drawFittedText ("Keyboard + octave shift + pitch/mod + APVTS baseline",
                      getLocalBounds().withTrimmedTop (40).removeFromTop (24),
                      juce::Justification::centred, 1);

    g.setColour (juce::Colours::white.withAlpha (0.85f));
    g.drawText ("Master Gain", masterGainSlider.getBounds().translated (0, -22), juce::Justification::centred);
    g.drawText ("Pitch Wheel", pitchWheelSlider.getBounds().translated (0, -22), juce::Justification::centred);
    g.drawText ("Mod Wheel", modWheelSlider.getBounds().translated (0, -22), juce::Justification::centred);
}

void NewAudioProjectAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (16);
    area.removeFromTop (64);

    auto topControls = area.removeFromTop (240);

    auto octaveArea = topControls.removeFromLeft (240);
    octaveArea.reduce (10, 10);
    octaveLabel.setBounds (octaveArea.removeFromTop (28));
    octaveArea.removeFromTop (8);
    auto octaveButtons = octaveArea.removeFromTop (34);
    octaveDownButton.setBounds (octaveButtons.removeFromLeft (110));
    octaveButtons.removeFromLeft (8);
    octaveUpButton.setBounds (octaveButtons.removeFromLeft (110));

    auto gainArea = topControls.removeFromLeft (240).reduced (20, 10);
    masterGainSlider.setBounds (gainArea.removeFromTop (180));

    auto wheelArea = topControls.removeFromLeft (240).reduced (20, 10);
    auto leftWheel = wheelArea.removeFromLeft (100);
    wheelArea.removeFromLeft (20);
    auto rightWheel = wheelArea.removeFromLeft (100);
    pitchWheelSlider.setBounds (leftWheel.removeFromTop (180));
    modWheelSlider.setBounds (rightWheel.removeFromTop (180));

    area.removeFromTop (10);
    keyboardComponent.setBounds (area.removeFromBottom (220));
}
