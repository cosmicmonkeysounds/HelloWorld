/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


BackgroundThread::BackgroundThread( int _w, int _h ) : Thread("BackgroundThread"), w(_w), h(_h)
{
    DBG( "Thread CTOR" );
    startThread();
}

BackgroundThread::~BackgroundThread()
{
    stopThread(500);
}

void BackgroundThread::run()
{
    while( true )
    {
        if( threadShouldExit() )
            break;
        
        auto canvas = Image( Image::PixelFormat::RGB, w, h, true );
        
        if( threadShouldExit() )
            break;
        
        
        
        bool shouldBail = false;
        for( int x = 0; x < w; ++x )
        {
            
            if( threadShouldExit() )
            {
                shouldBail = true;
                break;
            }
            for( int y = 0; y < h; ++y )
            {
                canvas.setPixelAt( x, y, Colour(r.nextFloat(),
                                                r.nextFloat(),
                                                r.nextFloat(),
                                                1.f) );
            }
        }
        
        DBG( "In background thread" );
        
        // more stuff!!
        
        if( threadShouldExit() || shouldBail )
            break;
        
        if( updateRenderer )
            updateRenderer( std::move(canvas) );
        
        wait(-1);
        
    }
}

void BackgroundThread::setUpdateRenderer( std::function<void(Image&&)> func )
{
    updateRenderer = std::move( func );
    DBG("Setting renderer");
}

DualButton::DualButton()
{
    addAndMakeVisible(btn1);
    addAndMakeVisible(btn2);
    
//    btn1.onClick = [this]()
//    {
//        DBG( "This is btn1's size: " << this->btn1.getBounds().toString() );
//        timerThing.stopTimer();
//
//    };
//
//    btn2.onClick = [this]()
//    {
//        DBG( "This is btn2's size: " << this->btn2.getBounds().toString() );
//        timerThing.startTimerHz(2);
//    };
    
}

void DualButton::setBtn1Handler( std::function<void()> func )
{
    btn1.onClick = std::move(func);
}
void DualButton::setBtn2Handler( std::function<void()> func )
{
    btn2.onClick = std::move(func);
}

void DualButton::resized()
{
    auto bounds = getLocalBounds();
    btn1.setBounds( bounds.removeFromTop(30) );
    btn2.setBounds( bounds );
}

OwnedArrayComponent::OwnedArrayComponent()
{
    for( int i = 0; i < 10; i++ )
    {
        auto* widget = buttons.add( new TextButton(String(i)) );
        addAndMakeVisible(widget);
        widget->addListener(this);
    }
}

OwnedArrayComponent::~OwnedArrayComponent()
{
    for( auto* btn : buttons )
    {
        btn->removeListener(this);
    }
}

void OwnedArrayComponent::resized()
{
    auto width = getWidth() / static_cast<float>( buttons.size() );
    auto height = getHeight();
    
    int x = 0;
    
    for ( auto* widget : buttons )
    {
        widget->setBounds( x, 0, width, height );
        x += width;
    }
}

void OwnedArrayComponent::buttonClicked( Button* clickedButton )
{
    if( clickedButton == buttons.getFirst() )
    {
        DBG( "First btn clicked" );
    }
    else if( clickedButton == buttons.getLast() )
    {
        DBG( "Last btn clicked" );
    }
    else
    {
        DBG( "Clicked some other btn" );
    }
}


//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(comp);
    addAndMakeVisible(ownedArrayComp);
    addAndMakeVisible(dualButton);
    addAndMakeVisible(repeating);
    addAndMakeVisible(hiResAsync);

    
    // if the child has children you want to listen to, use true.
    comp.addMouseListener(this, false);
    ownedArrayComp.addMouseListener(this, true);
    
    dualButton.setBtn1Handler( [this]()
    {
        repeating.startTimer(300);
    });
    
    dualButton.setBtn2Handler( [this]()
    {
        repeating.stopTimer();
    });
    
    setSize (600, 400);
    
    addAndMakeVisible(renderer);
}

MainComponent::~MainComponent()
{
    comp.removeMouseListener(this);
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    comp.setBounds( 30, 30, 100, 100 );
    ownedArrayComp.setBounds( comp.getX(),
                              comp.getBottom(),
                              getWidth() - comp.getX(),
                              getHeight() - comp.getBottom() );
    
    dualButton.setBounds( comp.getBounds()
                          .withX(comp.getRight() + 5) );
    
    repeating.setBounds( dualButton.getBounds()
                        .withX(dualButton.getRight() + 5) );
    
    hiResAsync.setBounds( repeating.getBounds()
                          .withX(repeating.getRight() + 5) );
    
    renderer.setBounds( hiResAsync.getBounds()
                        .withX(hiResAsync.getRight() + 5) );
}
