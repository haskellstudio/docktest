#include "mainWindow.h"
#include "mainComponent.h"

MainWindow::MainWindow () : juce::DocumentWindow("FTF", juce::Colours::darkgrey, juce::DocumentWindow::allButtons, true)
{
    MainComponent* const contentComponent = new MainComponent (this);
	setContentOwned (contentComponent, false);
	
	juce::DocumentWindow::setResizable (true, false);
	//juce::DocumentWindow::setResizeLimits (800, 600, 8192, 8192);
	juce::DocumentWindow::setFullScreen (false);
	juce::DocumentWindow::setVisible (true);
	
    // don't want the window to take focus when the title-bar is clicked..
    setWantsKeyboardFocus (true);
    
    
    Rectangle<int> displayRect = juce::Desktop::getInstance().getDisplays().getMainDisplay().userArea;
   // Rectangle<int> totalBounds = juce::Desktop::getInstance().getDisplays().getMainDisplay().totalArea;
   //double scale =juce::Desktop::getInstance().getDisplays().getMainDisplay().scale;
    int width = displayRect.getWidth() * .8f;
    int height = width * 0.618 ;//displayRect.getHeight()*.6f;
  // setSize(width, height );
    
    
    //Desktop::getInstance().getDisplays().refresh();
    RectangleList<int> rects = Desktop::getInstance().getDisplays().getRectangleList(true);
    if (rects.getNumRectangles() > 1)
        // Full screen on the first monitor
        setBounds(rects.getRectangle(1));
    else
    {
        //setBounds(rects.getRectangle(0));
        // Don't go fullscreen
        centreWithSize(width,height);
    }

    
    
    
    
   // setSize(500, 500);
}

MainWindow::~MainWindow ()
{
	setContentOwned (0, false);
}

void MainWindow::closeButtonPressed()
{
	juce::JUCEApplication::getInstance()->systemRequestedQuit();
}
