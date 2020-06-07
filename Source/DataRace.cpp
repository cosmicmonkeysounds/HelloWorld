/*
  ==============================================================================

    DataRace.cpp
    Created: 7 Jun 2020 3:02:12pm
    Author:  l33t h4x0r

  ==============================================================================
*/

#include "DataRace.h"

bool Data::operator==(const Data& other )
{
    return x == other.x && y == other.y;
}

bool Data::operator!= (const Data& other )
{
    return !(*this == other);
}

void A::run()
{
    while( true )
    {
        if( threadShouldExit() )
            break;
        
        d = newDataA;
        
        if( d != newDataA && d != newDataB )
        {
            auto _local = d;
            std::cout << "A: d = { .x= " << String::toHexString(_local.x) << " }\n B: d = { .y= " << String::toHexString(_local.y) << " }\n";
        }
        wait(10);
    }
}

void B::run()
{
    while( true )
    {
        if( threadShouldExit() )
            break;
        
        d = newDataB;
        
        if( d != newDataA && d != newDataB )
        {
            auto _local = d;
            std::cout << "A: d = { .x= " << String::toHexString(_local.x) << " }\n B: d = { .y= " << String::toHexString(_local.y) << " }\n";
            
        }
        wait(10);
    }
}
