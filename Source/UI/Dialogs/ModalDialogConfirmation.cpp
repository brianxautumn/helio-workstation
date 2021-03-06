/*
    This file is part of Helio Workstation.

    Helio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Helio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helio. If not, see <http://www.gnu.org/licenses/>.
*/

//[Headers]
#include "Common.h"
//[/Headers]

#include "ModalDialogConfirmation.h"

//[MiscUserDefs]
static const int asyncCancelCommandId = 123123;
//[/MiscUserDefs]

ModalDialogConfirmation::ModalDialogConfirmation(Component &owner, const String &message, const String &okText, const String &cancelText, int okCode, int cancelCode)
    : ownerComponent(owner),
      okCommand(okCode),
      cancelCommand(cancelCode)
{
    addAndMakeVisible (background = new PanelC());
    addAndMakeVisible (panel = new PanelA());
    addAndMakeVisible (messageLabel = new Label (String(),
                                                 TRANS("...")));
    messageLabel->setFont (Font (Font::getDefaultSerifFontName(), 21.00f, Font::plain).withTypefaceStyle ("Regular"));
    messageLabel->setJustificationType (Justification::centred);
    messageLabel->setEditable (false, false, false);
    messageLabel->setColour (Label::textColourId, Colours::white);
    messageLabel->setColour (TextEditor::textColourId, Colours::black);
    messageLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cancelButton = new TextButton (String()));
    cancelButton->setButtonText (TRANS("..."));
    cancelButton->setConnectedEdges (Button::ConnectedOnTop);
    cancelButton->addListener (this);

    addAndMakeVisible (component2 = new ShadowDownwards());
    addAndMakeVisible (okButton = new TextButton (String()));
    okButton->setButtonText (TRANS("..."));
    okButton->setConnectedEdges (Button::ConnectedOnTop);
    okButton->addListener (this);


    //[UserPreSize]
    this->messageLabel->setText(message, dontSendNotification);
    this->okButton->setButtonText(okText);
    this->cancelButton->setButtonText(cancelText);
    //[/UserPreSize]

    setSize (400, 210);

    //[Constructor]
    this->rebound();
    this->setWantsKeyboardFocus(true);
    this->setInterceptsMouseClicks(true, true);
    this->toFront(true);
    this->setAlwaysOnTop(true);
    this->grabKeyboardFocus();
    //[/Constructor]
}

ModalDialogConfirmation::~ModalDialogConfirmation()
{
    //[Destructor_pre]
    FadingDialog::fadeOut();
    //[/Destructor_pre]

    background = nullptr;
    panel = nullptr;
    messageLabel = nullptr;
    cancelButton = nullptr;
    component2 = nullptr;
    okButton = nullptr;

    //[Destructor]
    //[/Destructor]
}

void ModalDialogConfirmation::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0x59000000));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ModalDialogConfirmation::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    background->setBounds ((getWidth() / 2) + -1 - ((getWidth() - 10) / 2), 5, getWidth() - 10, getHeight() - 10);
    panel->setBounds ((getWidth() / 2) + -1 - ((getWidth() - 30) / 2), 15, getWidth() - 30, 137);
    messageLabel->setBounds ((getWidth() / 2) - ((getWidth() - 40) / 2), 5 + 18, getWidth() - 40, 121);
    cancelButton->setBounds ((getWidth() / 2) + -5 - 139, 15 + 137, 139, 42);
    component2->setBounds ((getWidth() / 2) - (284 / 2), 15 + 137 - 3, 284, 24);
    okButton->setBounds ((getWidth() / 2) + 5, 15 + 137, 139, 42);
    //[UserResized] Add your own custom resize handling here..
    this->grabKeyboardFocus();
    //[/UserResized]
}

void ModalDialogConfirmation::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == cancelButton)
    {
        //[UserButtonCode_cancelButton] -- add your button handler code here..
        this->cancel();
        //[/UserButtonCode_cancelButton]
    }
    else if (buttonThatWasClicked == okButton)
    {
        //[UserButtonCode_okButton] -- add your button handler code here..
        this->okay();
        //[/UserButtonCode_okButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ModalDialogConfirmation::parentHierarchyChanged()
{
    //[UserCode_parentHierarchyChanged] -- Add your code here...
    this->rebound();
    //[/UserCode_parentHierarchyChanged]
}

void ModalDialogConfirmation::parentSizeChanged()
{
    //[UserCode_parentSizeChanged] -- Add your code here...
    this->rebound();
    //[/UserCode_parentSizeChanged]
}

void ModalDialogConfirmation::handleCommandMessage (int commandId)
{
    //[UserCode_handleCommandMessage] -- Add your code here...
    if (commandId == asyncCancelCommandId)
    {
        this->cancel();
    }
    //[/UserCode_handleCommandMessage]
}

bool ModalDialogConfirmation::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    if (key.isKeyCode(KeyPress::escapeKey))
    {
        this->cancel();
        return true;
    }
    else if (key.isKeyCode(KeyPress::returnKey))
    {
        this->okay();
        return true;
    }

    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}

void ModalDialogConfirmation::inputAttemptWhenModal()
{
    //[UserCode_inputAttemptWhenModal] -- Add your code here...
    this->postCommandMessage(asyncCancelCommandId);
    //[/UserCode_inputAttemptWhenModal]
}


//[MiscUserCode]
//[/MiscUserCode]

#if 0
/*
BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ModalDialogConfirmation"
                 template="../../Template" componentName="" parentClasses="public FadingDialog"
                 constructorParams="Component &amp;owner, const String &amp;message, const String &amp;okText, const String &amp;cancelText, int okCode, int cancelCode"
                 variableInitialisers="ownerComponent(owner),&#10;okCommand(okCode),&#10;cancelCommand(cancelCode)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="210">
  <METHODS>
    <METHOD name="parentSizeChanged()"/>
    <METHOD name="parentHierarchyChanged()"/>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
    <METHOD name="inputAttemptWhenModal()"/>
    <METHOD name="handleCommandMessage (int commandId)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: 59000000" hasStroke="0"/>
  </BACKGROUND>
  <JUCERCOMP name="" id="e96b77baef792d3a" memberName="background" virtualName=""
             explicitFocusOrder="0" pos="-1Cc 5 10M 10M" posRelativeH="ac3897c4f32c4354"
             sourceFile="../Themes/PanelC.cpp" constructorParams=""/>
  <JUCERCOMP name="" id="fee11f38ba63ec9" memberName="panel" virtualName=""
             explicitFocusOrder="0" pos="-1Cc 15 30M 137" sourceFile="../Themes/PanelA.cpp"
             constructorParams=""/>
  <LABEL name="" id="cf32360d33639f7f" memberName="messageLabel" virtualName=""
         explicitFocusOrder="0" pos="0Cc 18 40M 121" posRelativeY="e96b77baef792d3a"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="..."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default serif font" fontsize="21" kerning="0" bold="0"
         italic="0" justification="36"/>
  <TEXTBUTTON name="" id="ccad5f07d4986699" memberName="cancelButton" virtualName=""
              explicitFocusOrder="0" pos="-5Cr 0R 139 42" posRelativeY="fee11f38ba63ec9"
              buttonText="..." connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <JUCERCOMP name="" id="ab3649d51aa02a67" memberName="component2" virtualName=""
             explicitFocusOrder="0" pos="0Cc 3R 284 24" posRelativeY="fee11f38ba63ec9"
             sourceFile="../Themes/ShadowDownwards.cpp" constructorParams=""/>
  <TEXTBUTTON name="" id="7855caa7c65c5c11" memberName="okButton" virtualName=""
              explicitFocusOrder="0" pos="5C 0R 139 42" posRelativeY="fee11f38ba63ec9"
              buttonText="..." connectedEdges="4" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
