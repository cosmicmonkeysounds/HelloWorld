/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DataRace.h"

struct MyThread : Thread
{
    MyThread() : Thread("MyThread")
    {
        // when this is started, run() is called
        // you can supply a priority argument
        startThread();
    }
    
    ~MyThread()
    {
        // this changes a flag to make threadShouldExit() return true.
        // if you don't kill the thread manually, the OS will after this many milliseconds.
        stopThread(100);
    }
    
    // called once, every time the thread is started
    void run() override
    {
        
        while( true )
        {
            if( threadShouldExit() )
                break;
            
            // do some stuff
            
            if( threadShouldExit() )
                break;
            
            // more stuff!!
            
            if( threadShouldExit() )
                break;
            
            // even more stuff!
            
            // if we have a long process block, it's probably worth while to check back on your thread like this.
            
            // break your tasks into smaller tasks
            
            wait(10);
            // or
            
            // this freezes the thread until somebody calls notify()
            wait(-1);
            
        }
    }
};

// to create this object AFTER a component to set size properly
struct BackgroundThread : Thread
{
    
    BackgroundThread( int _w, int _h );
    
    ~BackgroundThread();
    
    void run() override;
    
    void setUpdateRenderer( std::function<void(Image&&)> func );
    
private:
    int w{0}, h{0};
    Random r;
    std::function<void(Image&&)> updateRenderer;
    
};

struct LambdaTimer : Timer
{
    LambdaTimer( int ms, std::function<void()> func ) : lambda( std::move(func) )
    {
        DBG("Lambda CTOR");
        startTimer(ms);
    }
    
    ~LambdaTimer()
    {
        stopTimer();
    }
    
    void timerCallback() override
    {
        stopTimer();
        if( lambda )
            DBG("executing callback");
            lambda();
    }

    std::function<void()> lambda;
};

#include <array>
struct Renderer : Component, AsyncUpdater
{
    Renderer()
    {
        
        DBG( "Renderer CTOR" );
        lambdaTimer = std::make_unique<LambdaTimer>( 10, [this]()
        {
            processingThread = std::make_unique<BackgroundThread>( getWidth(), getHeight() );
            
            DBG("Before setting processing thread");
            
            processingThread->setUpdateRenderer( [this](Image&& image)
            {
                int renderIndex = firstImage ? 0 : 1;
                firstImage = !firstImage;
                imageToRender[renderIndex] = std::move(image);
                
                DBG( "Before triggerAsync()" );
                
                triggerAsyncUpdate();
                
                lambdaTimer = std::make_unique<LambdaTimer>( 1000, [this]()
                {
                    processingThread->notify();
                });
            });
            
        });
    }
    
    ~Renderer()
    {
        processingThread.reset();
        lambdaTimer.reset();
    }
    
    void paint( Graphics& g ) override
    {
        DBG( "Renderer::Paint" );
        g.drawImage(firstImage ? imageToRender[1] : imageToRender[0], getLocalBounds().toFloat() );
    }
    
    void handleAsyncUpdate() override
    {
        DBG( "Repainting" );
        repaint();
    }
    
private:
    std::unique_ptr<BackgroundThread> processingThread;
    std::unique_ptr<LambdaTimer> lambdaTimer;
    bool firstImage = true;
    std::array<Image, 2> imageToRender;
    
};

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
    Renderer renderer;
    Test test;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
