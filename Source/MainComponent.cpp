/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

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
    
    // if the child has children you want to listen to, use true.
    comp.addMouseListener(this, false);
    ownedArrayComp.addMouseListener(this, true);
    
    setSize (600, 400);
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
    ownedArrayComp.setBounds( comp.getX(), comp.getBottom(), getWidth() - comp.getX(), getHeight() - comp.getBottom() );
}
