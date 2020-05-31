/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct MyComp : Component
{
    
    // don't need a resized function if the struct has no children (:
    //void resized() override {}
   
    void paint( Graphics& g ) override
    {
        g.fillAll(Colours::green);
    }
    
    void mouseEnter( const MouseEvent& e ) override
    {
        DBG( "mouseEnter()" );
    }
    
    void mouseExit( const MouseEvent& e ) override
    {
        DBG( "mouseExit()" );
    }
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    // when you mouse over a child, it leaves the parents scope, thus is leaves the parent context
    // when you move to the child component.
    
    // a mouse listener in the .cpp to be able to listen to the events in a child
    
    void mouseEnter( const MouseEvent& e ) override
    {
        DBG( "Main Component mouseEnter()" );
    }
    
    void mouseExit( const MouseEvent& e ) override
    {
        DBG( " Main Component mouseExit()" );
    }

private:
    //==============================================================================
    // Your private member variables go here...
    MyComp comp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
