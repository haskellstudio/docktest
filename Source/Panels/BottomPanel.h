//=============================================================================
#ifndef __BOTTOM_PANEL_H__
#define __BOTTOM_PANEL_H__
//=============================================================================
#include "../includes.h"
//=============================================================================
class BottomPanel : public juce::Component
{
	public:
		BottomPanel ();
		~BottomPanel ();
		//=====================================================================
		void resized ();
		void paint (juce::Graphics &g);
		//=====================================================================
	private:
};
//=============================================================================
#endif //__BOTTOM_PANEL_H__
//=============================================================================