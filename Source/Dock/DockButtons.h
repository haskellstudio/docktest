#include "../includes.h"

#define BUTTONSIZE 15
#define PADDINGSIZE 13

#define FADEOUTMS 180

#define TOP        0
#define BOTTOM    1
#define LEFT    2
#define RIGHT    3
#define CENTER    4

#define ZORDER_CENTER            0
#define ZORDER_LEFT                1
#define ZORDER_RIGHT            2
#define ZORDER_LEFT_BUTTON        3
#define ZORDER_RIGHT_BUTTON        4
#define ZORDER_TOP                5
#define ZORDER_BOTTOM            6
#define ZORDER_TOP_BUTTON        7
#define ZORDER_BOTTOM_BUTTON    8

static juce::DrawablePath* getDockablePath (const int type, const bool on, const bool over)
{
	juce::DrawablePath* drawable = new juce::DrawablePath ();

	juce::Path path;
	switch (type)
	{
		case TOP:
			if (on)
			{
				for (int i = 0; i < 5; ++i)
				{
					juce::Line<float> line (0.0f+(0.1f*i), 0.0f+(0.2f*i), 1.0f-(0.1f*i), 0.0f+(0.2f*i));
					path.addLineSegment (line, 0.05f);
				}
			}
			else
				path.addTriangle (0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f);
			break;

		case LEFT:
			if (on)
			{
				for (int i = 0; i < 5; ++i)
				{
					juce::Line<float> line (0.0f+(0.2f*i), 0.0f+(0.1f*i), 0.0f+(0.2f*i), 1.0f-(0.1f*i));
					path.addLineSegment (line, 0.05f);
				}
			}
            else
                path.addTriangle (0.0f, .5f, 1.0f, 1.0f, 1.0f, 0.0f);
			break;

		case RIGHT:
			if (on)
			{
				for (int i = 0; i < 5; ++i)
				{
					juce::Line<float> line (1.0f-(0.2f*i), 0.0f+(0.1f*i), 1.0f-(0.2f*i), 1.0f-(0.1f*i));
					path.addLineSegment (line, 0.05f);
				}
			}
			else
				path.addTriangle (0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f);
			break;

		case BOTTOM:
			if (on)
			{
				for (int i = 0; i < 5; ++i)
				{
					juce::Line<float> line (0.0f+(0.1f*i), 1.0f-(0.2f*i), 1.0f-(0.1f*i), 1.0f-(0.2f*i));
					path.addLineSegment (line, 0.05f);
				}
			}
			else
				path.addTriangle (0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f);
			break;
	};
	drawable->setPath (path);

	if (on)
	{
		if (over)
			drawable->setFill (juce::FillType (juce::Colour(0xff00FF00)));
		else
			drawable->setFill (juce::FillType (juce::Colour(0xff1AB20A )));
	}
	else
	{
		if (over)
			drawable->setFill (juce::FillType (juce::Colour(0xff999999)));
		else
			drawable->setFill (juce::FillType (juce::Colour(0xff4c4c4c)));
	}
	return drawable;
}
//=============================================================================
static juce::DrawableButton* getDockableButton (const juce::String& name, const int type)
{
	juce::DrawableButton * const button = new juce::DrawableButton (name, juce::DrawableButton::ImageFitted);

    button->setColour(DrawableButton::ColourIds::backgroundColourId, Colour (0x00000000));
    button->setColour(DrawableButton::ColourIds::backgroundOnColourId, Colour (0x00000000));
    //  leftButton->setColour (TextButton::buttonColourId, Colours::red);
    //  leftButton->setColour (TextButton::buttonOnColourId, Colours::green);
    
	juce::Drawable *normalImage, *overImage, *downImage, *disabledImage;
	juce::Drawable *normalImageOn, *overImageOn, *downImageOn, *disabledImageOn;

	switch (type)
	{
		case TOP:
			normalImage = getDockablePath (TOP, false, false);
			overImage = getDockablePath (TOP, false, true);
			normalImageOn = getDockablePath (TOP, true, false);
			overImageOn = getDockablePath (TOP, true, true);
			break;
		case LEFT:
			normalImage = getDockablePath (LEFT, false, false);
			overImage = getDockablePath (LEFT, false, true);
			normalImageOn = getDockablePath (LEFT, true, false);
			overImageOn = getDockablePath (LEFT, true, true);
            
           
            
			break;
		case RIGHT:
			normalImage = getDockablePath (RIGHT, false, false);
			overImage = getDockablePath (RIGHT, false, true);
			normalImageOn = getDockablePath (RIGHT, true, false);
			overImageOn = getDockablePath (RIGHT, true, true);
			break;
		case BOTTOM:
			normalImage = getDockablePath (BOTTOM, false, false);
			overImage = getDockablePath (BOTTOM, false, true);
			normalImageOn = getDockablePath (BOTTOM, true, false);
			overImageOn = getDockablePath (BOTTOM, true, true);
			break;
	};

	downImage = 0; downImageOn = 0;
	disabledImage = 0; disabledImageOn = 0;

	button->setImages (normalImage, overImage, downImage, disabledImage,
					   normalImageOn, overImageOn, downImageOn, disabledImageOn);

	delete normalImage; delete normalImageOn;
	delete overImage; delete overImageOn;
	delete downImage; delete downImageOn;
	delete disabledImage; delete disabledImageOn;

	return button;
}
//=============================================================================
