//=============================================================================
#include "DockManager.h"
#include "DockButtons.h"
//=============================================================================
DockManager::DockManager ()
	: top (0), left (0), center (0), right (0), bottom (0),
	  topButton (0), leftButton (0), rightButton (0), bottomButton (0),
	  lastMouseEvent (0)
{
    addAndMakeVisible (leftButton = getDockableButton (juce::String("left"), LEFT), ZORDER_LEFT_BUTTON);// new juce::DrawableButton("tesss", juce::DrawableButton::ImageFitted));
    leftButton->setToggleState (true, false);
    leftButton->setClickingTogglesState (true);
    leftButton->addMouseListener (this, true);
    leftButton->addListener (this);
    
    addAndMakeVisible (rightButton = getDockableButton (juce::String("right"), RIGHT), ZORDER_RIGHT_BUTTON);
    rightButton->setToggleState (false, false);
    rightButton->setClickingTogglesState (true);
    rightButton->addMouseListener (this, true);
    rightButton->addListener (this);

    addAndMakeVisible (topButton = getDockableButton (juce::String("top"), TOP), ZORDER_TOP_BUTTON);
    topButton->setToggleState (false, false);
    topButton->setClickingTogglesState (true);
    topButton->addMouseListener (this, true);
    topButton->addListener (this);

    addAndMakeVisible (bottomButton = getDockableButton (juce::String("bottom"), BOTTOM), ZORDER_BOTTOM_BUTTON);
    bottomButton->setToggleState (false, false);
    bottomButton->setClickingTogglesState (true);
    bottomButton->addMouseListener (this, true);
    bottomButton->addListener (this);
}
//=============================================================================
DockManager::~DockManager ()
{
	deleteAllChildren ();
}
//=============================================================================
void DockManager::timerCallback ()
{
}
//=============================================================================
void DockManager::mousePropagation (const juce::MouseEvent &e, const int position)
{
	if (position != TOP && top)	top->mouseExit (e);
	if (position != LEFT && left)	left->mouseExit (e);
	if (position != RIGHT && right)	right->mouseExit (e);
	if (position != BOTTOM && bottom) bottom->mouseExit (e);
	if (position != CENTER && center) center->mouseExit (e);
}
//=============================================================================
bool DockManager::isDocked (const int position)
{
	switch (position)
	{
		case TOP:
			return top->isDocked ();
		case LEFT:
			return left->isDocked ();
		case RIGHT:
			return right->isDocked ();
		case BOTTOM:
			return bottom->isDocked ();
		default:
			return false;
	}
}
//=============================================================================
void DockManager::setPanelComponent (const int position, juce::Component *component)
{
	switch (position)
	{
		case CENTER:
			{
				if (center)
					delete center;
				center = new DockPanel (this, component, CENTER, true);
				addAndMakeVisible (center, ZORDER_CENTER);
			}
			break;
		case LEFT:
			{
				if (left)
					delete left;
                left = new DockPanel (this, component, LEFT, (leftButton == nullptr)? false : !leftButton->getToggleState());
				left->addComponentListener (this);
				addAndMakeVisible (left, ZORDER_LEFT);
			}
			break;
		case RIGHT:
			{
				if (right)
					delete right;
				right = new DockPanel (this, component, RIGHT, (rightButton == nullptr)? false : !rightButton->getToggleState());
				right->addComponentListener (this);
				addAndMakeVisible (right, ZORDER_RIGHT);
			}
			break;
		case TOP:
			{
				if (top)
					delete top;
				top = new DockPanel (this, component, TOP,  (topButton == nullptr)? false : !topButton->getToggleState());
				top->addComponentListener (this);
				addAndMakeVisible (top, ZORDER_TOP);
			}
			break;
		case BOTTOM:
			{
				if (bottom)
					delete bottom;
				bottom = new DockPanel (this, component, BOTTOM,  (bottomButton == nullptr)? false : !bottomButton->getToggleState());
				bottom->addComponentListener (this);
				addAndMakeVisible(bottom, ZORDER_BOTTOM);
			}
			break;
		default: 
			break;
	}
}
//=============================================================================
void DockManager::paint (juce::Graphics &g)
{
    g.fillAll (juce::Colours::darkgrey);
}
//=============================================================================
void DockManager::componentMovedOrResized (juce::Component &component, bool wasMoved, bool wasResized)
{
	return;
	if (wasResized)
		resized ();
}
//=============================================================================
void DockManager::resized ()
{
	const int w = getWidth();
	const int h = getHeight();

    const int b = w * 0.01f;//BUTTONSIZE;
 
//    if(b < 0)
//    {
//        juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon, "b", "b < 0");
//    }
    if(top)
    {
        top->setBoundsExTop(b);
    }
    
    if(bottom)
    {
        bottom->setBoundsExBottom(b);
    }
    
    
    const int th = (top == nullptr) ? 0 :top->getBounds().getHeight();
    const bool td = (top == nullptr) ? 0 : top->isDocked();
    const int bh = bottom == nullptr ? 0 : bottom->getBounds().getHeight();
    const bool bd = bottom == nullptr ? 0 : bottom->isDocked();
    if(left)
    {
        left->setBoundsExLeft(b,    //button size  = > x
                              (td ? th : 0) ,  //  top height
                              (bd ? bh : 0)  // bottom height
                              );
    }
    
	
    const int lw = left == nullptr ? 0 : left->getBounds().getWidth();
    const bool ld = left == nullptr ? 0 :left->isDocked();
    right->setBoundsExRight(b,
                             (td ? th : 0) ,// top height
                            (bd ? bh : 0)   // bottom height
                            );

    
    
    const int rw = right == nullptr ? 0 : right->getBounds().getWidth();
    const bool rd = right == nullptr ? 0 : right->isDocked();
   

	int cx, cy, cw, ch;
	cx = b + (ld ? lw : 0);
	cw = w - (ld ? lw : 0) 
		   - (rd ? rw : 0) - (b*2);
	cy = b + (td ? th : 0);
	ch = h - (td ? th : 0) 
		   - (bd ? bh : 0) - (b*2);
	if(center) center->setBounds (cx, cy, cw, ch);

    
    
    

	if(topButton) topButton->setBounds (0, 0, w, b);

	if(leftButton)
    {
        leftButton->setBounds (0,
						   b + (td ? th : 0), 
						   b, 
						   h - (td ? th : 0) 
							 - (bd ? bh : 0) - (b*2));
       // leftButton->setBounds(getLocalBounds());
    }
    

	if(rightButton) rightButton->setBounds (w - b,
							b + (td ? th : 0), 
							b, 
							h - (td ? th : 0) 
							  - (bd ? bh : 0) - (b*2));

	if(bottomButton) bottomButton->setBounds (0, h - b, w, b);
}
//=============================================================================
void DockManager::buttonClicked (juce::Button *button)
{
	if (button == topButton)
	{
        if(top)
        {
            top->setOpen (!button->getToggleState());
            top->setDocked (!button->getToggleState());
            top->setVisible (!button->getToggleState());
        }
	}
	else
	if (button == leftButton)
	{
        if(left)
        {
            left->setOpen (!button->getToggleState());
            left->setDocked (!button->getToggleState());
            left->setVisible (!button->getToggleState());
        }

	}
	else
	if (button == rightButton)
	{
        if(right)
        {
            right->setOpen (!button->getToggleState());
            right->setDocked (!button->getToggleState());
            right->setVisible (!button->getToggleState());
        }

	}
	else
	if (button == bottomButton)
	{
        if(bottom)
        {
            bottom->setOpen (!button->getToggleState());
            bottom->setDocked (!button->getToggleState());
            bottom->setVisible (!button->getToggleState());
        }

	}
	resized ();
}
//=============================================================================
void DockManager::mouseEnter (const juce::MouseEvent &e)
{
    if(animator.isAnimating())
    {
        return;
    }
	juce::Component *animate = 0;
	juce::Component *child = 0;
	juce::Rectangle<int> position;
	int runningMs;


	if (e.eventComponent == topButton)
	{
        if(top)
		if (!top->isDocked() && 
			!top->isOpen())
		{
			top->setOpen (true);
			animate = top;
			if (top->panel != nullptr)
			{
				child = dynamic_cast<DockPanel*>(top)->content;
				child->setAlpha(1.0f);
			}

			position = animate->getBounds ();
			animate->setBounds (position.getX(), 
								position.getY() - position.getHeight(),
								position.getWidth(), 
								position.getHeight());
		}
	}
	else
	if (e.eventComponent == leftButton)
	{
        int b = left->getX();
        if(b < 0)
        {
         //   juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon, "b", "b < 0");
        }
        if(left)
		if (!left->isDocked() && 
			!left->isOpen() )
		{
			left->setOpen (true);
			animate = left;

			if (left->panel != nullptr)
			{
				child = dynamic_cast<DockPanel*>(left)->content;
				child->setAlpha(1.0f);
			}

			position = animate->getBounds ();
            int x = position.getX();
            int w = position.getWidth();
            int arg1 = x -w;
            if(arg1 < -286)
            {
                juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon, "b", "b < 0");
            }
			animate->setBounds (arg1,
								position.getY(),
								position.getWidth(), 
								position.getHeight());
		}
	}
	else
	if (e.eventComponent == rightButton)
	{
        if(right)
		if (!right->isDocked() && 
			!right->isOpen())
		{
			right->setOpen (true);
			animate = right;
			if (right->panel != nullptr)
			{
				child = dynamic_cast<DockPanel*>(right)->content;
				child->setAlpha(1.0f);
			}

			position = animate->getBounds ();
			animate->setBounds (position.getX() + position.getWidth(), 
								position.getY(),
								position.getWidth(), 
								position.getHeight());
		}
	}
	else
	if (e.eventComponent == bottomButton)
	{
        if(bottom)
		if (!bottom->isDocked() && 
			!bottom->isOpen())
		{
			bottom->setOpen (true);
			animate = bottom;
			if (bottom->panel != nullptr)
			{
				child = dynamic_cast<DockPanel*>(bottom)->content;
				child->setAlpha(1.0f);
			}

			position = animate->getBounds ();
			animate->setBounds (position.getX(), 
								getHeight() + position.getHeight(),
								position.getWidth(), 
								position.getHeight());
		}
	}

	if (animate && child)
	{
		if (!animator.isAnimating (animate) && !animate->isVisible())
		{	
			child->setVisible (true);
			animate->setVisible (true);
			runningMs= juce::roundDoubleToInt(juce::jlimit(0.0, 120.0, (position.getWidth() + position.getHeight()) * 0.25));
			animator.animateComponent (animate, position, 1.0, runningMs, true, 1.0, 0.0);
		}
	}
}

void DockManager::mouseExit (const juce::MouseEvent &e)
{
    if(animator.isAnimating())
    {
        return;
    }
	//juce::Component *leftContent = dynamic_cast<DockPanel*>(left)->content;
	//juce::Component *rightContent = dynamic_cast<DockPanel*>(right)->content;
    if(left)
	if (left->panel != nullptr)
	{
		juce::Component *leftContent = dynamic_cast<DockPanel*>(left)->content;

		if (e.eventComponent == leftButton && !left->isDocked())
		{
//            int t1 = e.y;
//            int t2  = leftButton->getY();
//
//            int t3 = leftButton->getHeight()-BUTTONSIZE;
            
			if (/*e.y < leftButton->getY() */
                e.y < BUTTONSIZE ||
				e.y > leftButton->getHeight() - BUTTONSIZE)
			{
				animator.fadeOut(leftContent, FADEOUTMS);
				animator.fadeOut(left, FADEOUTMS);
				left->setOpen(false);
			}
		}
	}

	if(right)
	if (right->panel != nullptr)
	{
		juce::Component *rightContent = dynamic_cast<DockPanel*>(right)->content;
		if (e.eventComponent == rightButton && !right->isDocked())
		{
			if (//e.y < rightButton->getY()
                e.y < BUTTONSIZE||
				e.y > rightButton->getHeight() - BUTTONSIZE)
			{
				animator.fadeOut(rightContent, FADEOUTMS);
				animator.fadeOut(right, FADEOUTMS);
				right->setOpen(false);
			}
		}
	}

}
