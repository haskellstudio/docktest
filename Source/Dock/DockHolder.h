
#ifndef __DOCKHOLDER_H__
#define __DOCKHOLDER_H__

#include "../includes.h"

class DockManager;
class DockPanel;

class DockHolder : public juce::Component
{
	public:
		DockHolder (DockManager* parent, DockPanel* panel, const int type);
		~DockHolder ();


		const juce::Rectangle<int> getContentBounds();
		
		const int getCurrentSize ()			{ return size; }
    
        void setBoundsExLeft(int buttonSize, int topHeight, int bottomHeight)
        {
            int pwidth = getParentWidth();
            int pheight = getParentHeight();
            
            setBounds (buttonSize,
                           buttonSize + topHeight,
                           pwidth * 0.15f,
                           pheight - topHeight - bottomHeight - (buttonSize*2));
            
            constrainer->setMinimumWidth(pwidth * .1f);
            constrainer->setMaximumWidth(pwidth * .2f);

        }
    
		juce_UseDebuggingNewOperator
	protected:
		friend DockManager;
		
		void resized ();
		void paint (juce::Graphics &g);
		
		void mouseEnter (const juce::MouseEvent &e);
		void mouseMove (const juce::MouseEvent &e);
		void mouseExit (const juce::MouseEvent &e);
		
		bool isMouseInside ()				{ return inside; }
		
		bool isOpen ()						{ return open; }
		void setOpen (bool status)			{ open = status; }
		
		bool isDocked ()					{ return docked; }
		void setDocked (bool status)		{ docked = status; }
		
		void init();
	private:
		juce::ComponentAnimator animator;
		DockManager *manager;
		DockPanel* panel;
		int orientation;
		int size;
		bool docked;
		bool inside;
		bool open;

		//=====================================================================
		int button;		// default: 15
		int padding;	// default: 3
		//=====================================================================

		//=====================================================================
		friend class DockPanel;
		juce::ResizableBorderComponent *resizable;
		ScopedPointer<juce::ComponentBoundsConstrainer> constrainer;
	
		//=====================================================================
};
//=============================================================================
#endif //__DOCKHOLDER_H__
//=============================================================================
