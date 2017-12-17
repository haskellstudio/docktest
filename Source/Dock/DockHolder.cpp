//=============================================================================

#include "DockButtons.h"
#include "DockHolder.h"
#include "DockManager.h"
#include "DockPanel.h"
//=============================================================================
DockHolder::DockHolder(DockManager* parent, DockPanel* p, const int type, bool isDocked)
	: manager(parent),
	panel(p),
	orientation(type),
	docked(isDocked),
	open(isDocked),
	inside(false),
	resizable(0),
	constrainer(nullptr)
{
		init();
}
//=============================================================================
DockHolder::~DockHolder ()
{
	deleteAllChildren ();
	constrainer = nullptr;
}

//=============================================================================
void DockHolder::paint (juce::Graphics &g)
{
	g.fillAll (juce::Colours::black);

	const int button = BUTTONSIZE;
	const int padding = PADDINGSIZE;

	const int width = getWidth();
	const int height = getHeight();

	if (orientation == CENTER)
	{
		{
			const float left = 0.0f;
			const float right = left + width;
			const float top = 0.0f;
			const float bottom = top + height;
			const int x1 = juce::roundFloatToInt(left);
			const int x2 = juce::roundFloatToInt(right-1);
			const int y1 = juce::roundFloatToInt(top);
			const int y2 = juce::roundFloatToInt(bottom-1);

			g.setColour (juce::Colour(0xff333333));
			g.drawHorizontalLine (y1, left, right);
			g.drawHorizontalLine (y2, left, right);
			if (!manager->isDocked (LEFT))
				g.drawVerticalLine (x1, top, bottom);
			if (!manager->isDocked (RIGHT))
				g.drawVerticalLine (x2, top, bottom);
		}
	}
	else
	if (orientation == TOP)
	{
		if (!isDocked())
		{
			const float left = 0.0f + button;
			const float right = left + (width-(button*2));
			const float top = 0.0f + height - padding;
			const float bottom = top + padding;
			const int y  = height - padding;
			const int x1 = button;
			const int x2 = width-(button+1);

		//	g.setColour (juce::Colour(0xff333333));
            g.setColour (juce::Colour(0xff0000ff));
            g.drawHorizontalLine (y, left, right);
            g.drawVerticalLine  (x1, top, bottom);
            g.drawVerticalLine  (x2, top, bottom);
		}
	}
	else
	if (orientation == LEFT)
	{
		{
			const float left = 0.0f;
			const float right = left + width;
			const float top = 0.0f;
			const float bottom = top + height;
			const int x = 0;
			const int y1 = 0;
			const int y2 = height - 1;

			g.setColour (juce::Colour(0xff333333));
			g.drawVerticalLine    (x, top, bottom);
			g.drawHorizontalLine (y1, left, right);
			g.drawHorizontalLine (y2, left, right);
		}
	}
	else
	if (orientation == RIGHT)
	{
		{
			const float left = 0.0f;
			const float right = left + width;
			const float top = 0.0f;
			const float bottom = top + height;
			const int x = width - 1;
			const int y1 = 0;
			const int y2 = height - 1;

			g.setColour (juce::Colour(0xff333333));
			g.drawVerticalLine    (x, top, bottom);
			g.drawHorizontalLine (y1, left, right);
			g.drawHorizontalLine (y2, left, right);
		}
	}
	else
	if (orientation == BOTTOM)
	{
		if (!isDocked())
		{
			const float left = 0.0f + button;
			const float right = left + (width-(button*2));
			const float top = 0.0f;
			const float bottom = top + (padding-1);
			const int y  = padding - 1;
			const int x1 = button;
			const int x2 = width-(button+1);

			g.setColour (juce::Colour(0xff333333));
			g.drawHorizontalLine (y, left, right);
			g.drawVerticalLine (x1, top, bottom);
			g.drawVerticalLine (x2, top, bottom);
		}
	}
}
//=============================================================================
const juce::Rectangle<int> DockHolder::getContentBounds ()
{
	const int pad = PADDINGSIZE;
	const int width = getWidth();
	const int height = getHeight();

	switch (orientation)
	{
		case CENTER:
			{
				const int y = pad;
				const int h = height-(pad*2);
				int x = 0;
				int w = width-(x*2);
				if (!manager->isDocked (LEFT))
				{
					x += pad; 
					w -= pad;
				}
				if (!manager->isDocked (RIGHT))
				{
					w -= pad;
				}
				return juce::Rectangle <int> (x, y, w, h);
			}
			break;
		case LEFT:
			{
				const int x = pad;
				const int y = pad;
				const int w = width-((pad*2)-1);
				const int h = height-(pad*2);
				return juce::Rectangle <int> (x, y, w, h);
			}
			break;
		case RIGHT:
			{
				const int x = pad-1;
				const int y = pad;
				const int w = width-((pad*2)-1);
				const int h = height-(pad*2);
				return juce::Rectangle <int> (x, y, w, h);
			}
			break;
		case TOP:
			{
				return juce::Rectangle <int> (0, 0, width, height-pad);
			}
			break;
		case BOTTOM:
			{
				return juce::Rectangle <int> (0, pad, width, height-pad);
			}
			break;
		default:
			{
				return juce::Rectangle <int> (0, 0, width, height);
			}
			break;
	}
	return juce::Rectangle <int> ();
}


//=============================================================================
void DockHolder::resized ()
{

	
    int pwidth = getParentWidth();
    int pheight = getParentHeight();

    switch (orientation)
    {
//    case CENTER:
//        if (_bNeedSetSize)
//            setSize(pwidth, pheight);
//        break;
//    case TOP:
//        if (_bNeedSetSize)
//            setSize(pwidth, pwidth * 0.1);
//        break;

    case RIGHT:
        constrainer->setMinimumWidth(pwidth * .1f);
        constrainer->setMaximumWidth(pwidth * .2f);
//        if (_bNeedSetSize)
//            setSize(312, pheight);
        break;
    case BOTTOM:
        constrainer->setMinimumHeight(pheight * 0.1);
        constrainer->setMaximumHeight(pheight * 0.2);
//        if (_bNeedSetSize)
//            setSize(manager->getWidth(), pheight * 0.15);
        break;
    }

	if (resizable)
		resizable->setBounds (0, 0, getWidth(), getHeight());

	//_bNeedSetSize = false;

}
//=============================================================================
void DockHolder::mouseEnter (const juce::MouseEvent &e)
{
	if (docked)
		return;
	setVisible (true);
	if (panel)
		panel->content->setVisible (true);
	inside = true;
}
//=============================================================================
void DockHolder::mouseMove (const juce::MouseEvent &e)
{
	manager->mousePropagation (e, orientation);
}
//=============================================================================
void DockHolder::mouseExit (const juce::MouseEvent &e)
{
	const int x = e.getEventRelativeTo (this).x;
	const int y = e.getEventRelativeTo (this).y;
	const int w = getWidth ();
	const int h = getHeight ();

	if (!docked && open)
	{
		switch (orientation)
		{
			case TOP:
				if (y > h			&&
				   (x > 0			||
					x < w))
					open = false;
				break;

			case LEFT:
				if (x > w			||
				    y < 0			||
					y > h)
					open = false;
				break;

			case RIGHT:
				if (x < 0			||
				    y < 0			||
					y > h)
					open = false;
				break;

			case BOTTOM:
				if (y < 0			&&
				   (x > 0			||
					x < w))
					open = false;
				break;
		}
	}

	if (!docked)
	{
		if (!open)
		{
			animator.fadeOut (this, FADEOUTMS);
			if (panel)
				animator.fadeOut (panel->content, FADEOUTMS);
		}
	}
	else
	{
		if (inside)
		{
			animator.fadeOut (this, FADEOUTMS);
			if (panel)
				animator.fadeOut (panel->content, FADEOUTMS);
		}
	}
	inside = false;
}
//=============================================================================


void DockHolder::init()
{
	if (!constrainer)
		constrainer = new juce::ComponentBoundsConstrainer();

	if (!resizable)
		resizable = new juce::ResizableBorderComponent(this, constrainer);

	if (orientation == LEFT)
	{
		addAndMakeVisible(resizable = new juce::ResizableBorderComponent(this, constrainer));
		resizable->setBorderThickness(juce::BorderSize<int>(0, 0, 0, PADDINGSIZE));
	}
	else if (orientation == RIGHT)
	{
		addAndMakeVisible(resizable = new juce::ResizableBorderComponent(this, constrainer));
		resizable->setBorderThickness(juce::BorderSize<int>(0, PADDINGSIZE, 0, 0));
	}
	else if (orientation == BOTTOM)
	{
		addAndMakeVisible(resizable = new juce::ResizableBorderComponent(this, constrainer));
		resizable->setBorderThickness(juce::BorderSize<int>(PADDINGSIZE, 0, 0, 0));
	}
}
