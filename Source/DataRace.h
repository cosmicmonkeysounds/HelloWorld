/*
  ==============================================================================

    DataRace.h
    Created: 7 Jun 2020 3:02:12pm
    Author:  l33t h4x0r

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

// Any data type that is 8bytes or less is *usually* an Atomic variable.

// They are free from data race problems (when one global variable is being read and written from by different threads.)

// this data struct is now 16bytes, and not an atomic variable.
struct Data
{
    uint64 x = 0;
    uint64 y = 0;
    
    bool operator==(const Data& other);
    bool operator!=(const Data& other);
};

const Data newDataA = { 0xaaaaaaaa, 0xaaaaaaaa };
const Data newDataB = { 0xffffffff, 0xffffffff };

struct A : Thread
{
    
    Data& d;
    
    A(Data& _d) : Thread("A"), d(_d)
    {
        startThread();
    }
    
    ~A()
    {
        stopThread(100);
    }
    
    void run() override;
};

struct B : Thread
{
    
    Data& d;
    
    B(Data& _d) : Thread("B"), d(_d)
    {
        startThread();
    }
    
    ~B()
    {
        stopThread(100);
    }
    void run() override;
};

struct Test
{
    Data someData;
    A a{someData};
    B b{someData};
};
