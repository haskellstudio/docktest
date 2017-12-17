
#include "DockPanel.h"
#include "DockButtons.h"

DockPanel::DockPanel (DockManager *parent, juce::Component* component, const int position, bool isDocked)
	: DockHolder (parent, this, position, isDocked),
	  content (component)
{
    
	content->addMouseListener (this, true);
    //juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon, "const juce::String &title", "<#const juce::String &message#>");
	addAndMakeVisible (content);
}

DockPanel::~DockPanel ()
{
	deleteAllChildren ();
}

void DockPanel::resized ()
{
	content->setBounds (DockHolder::getContentBounds());
	DockHolder::resized ();
}

void DockPanel::paint (juce::Graphics &g)
{
	DockHolder::paint (g);
}

