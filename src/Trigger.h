//
//  Trigger.h
//  opencvExample
//
//  Created by Jonathan Wohl on 9/5/13.
//
//

#pragma once

#ifndef __opencvExample__Trigger__
#define __opencvExample__Trigger__

#include <iostream>
#include "ofMain.h"


class Trigger {
    
public:
    Trigger(ofPoint _center, int _radius, string file, float _initVol, float _initPan);
    void draw();
    void setColor(int _color);
    
    ofSoundPlayer player;
    ofPoint center;
    int radius;
    bool triggered;
    int alpha;
    float r;
    float rate;
    bool complete;

private:
    int color;
};

#endif /* defined(__opencvExample__Trigger__) */
