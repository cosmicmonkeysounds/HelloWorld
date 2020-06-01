/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct MyAsync : Component, AsyncUpdater, HighResolutionTimer
{
    void handleAsyncUpdate() override
    {
        paintColour = (paintColour + 1) % maxColours;
        repaint();
    }
    
    void hiResTimerCallback() override
    {
        triggerAsyncUpdate();
    }
    
    void paint( Graphics& g ) override
    {
        switch( paintColour )
        {
            case 0:
                g.setColour(Colours::red);
                break;
                
            case 1:
                g.setColour(Colours::blue);
                break;
                
            case 2:
                g.setColour(Colours::black);
                break;
                
            case 3:
                g.setColour(Colours::brown);
                break;
        }
        
        g.fillAll();
    }
    
    MyAsync()
    {
        startTimer( 200 );
    }
    
    ~MyAsync()
    {
        stopTimer();
        cancelPendingUpdate();
    }
    
private:
    int paintColour = 0;
    const int maxColours {5};
};

struct DualButton : public Component
{
    TextButton btn1{"btn1"}, btn2{"btn2"};
    DualButton( );
    void resized() override;
    
    void setBtn1Handler( std::function<void()> );
    void setBtn2Handler( std::function<void()> );
    
    
};

struct Widget : public Component
{
    
    Widget( int i ) : num(i) {}
    
    int num = 0;
    
    void paint( Graphics& g ) override
    {
        g.fillAll( Colours::white );
        g.setColour( Colours::black );
        g.drawRect( getLocalBounds().reduced(2) );
        
        g.drawFittedText( String(num),
                          getLocalBounds(),
                          Justification::centred,
                         1 );
    }
};

struct RepeatingThing : Component, Timer
{
    void timerCallback() override
    {
        drawRed = !drawRed;
        repaint();
        
    }
    void paint( Graphics& g ) override
    {
        g.fillAll( drawRed ? Colours::red : Colours::blue );
    }
    
    RepeatingThing()
    {
        startTimerHz(1);
    }
    ~RepeatingThing()
    {
        stopTimer();
    }
    
private:
    bool drawRed = true;
};

struct OwnedArrayComponent : Component, Button::Listener
{
    OwnedArrayComponent();
    ~OwnedArrayComponent();
    void resized() override;
    void buttonClicked( Button* ) override;
    OwnedArray<TextButton> buttons;
};

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
        //DBG( "Main Component mouseEnter()" );
    }
    
    void mouseExit( const MouseEvent& e ) override
    {
        //DBG( " Main Component mouseExit()" );
    }
    
    void mouseDown( const MouseEvent& e ) override
    {
        DBG( "Click click" );
    }

private:
    //==============================================================================
    // Your private member variables go here...
    MyComp comp;
    OwnedArrayComponent ownedArrayComp;
    RepeatingThing repeating;
    DualButton dualButton;
    MyAsync hiResAsync;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
