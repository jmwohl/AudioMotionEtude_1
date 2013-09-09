//
//  Trigger.cpp
//  opencvExample
//
//  Created by Jonathan Wohl on 9/5/13.
//
//

#include "Trigger.h"

Trigger::Trigger(ofPoint _center, int _radius, string file, float _initVol, float _initPan) {
    center = _center;
    color = 0x000000;
    alpha = 100;
    r = 10;
    rate = 5;
    complete = false;
    radius = _radius;
    player.setMultiPlay(true);
    player.setVolume(_initVol);
    player.setPan(_initPan);
//    cout << _initVol << endl;
    player.loadSound(file);
}

void Trigger::draw() {
//    cout << "DRAW" << endl;
    if (triggered) {
        cout << "TRIGGERED" << endl;
        color = 0x0000FF;
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;
        ofSetColor(r, g, b, alpha);
        ofCircle(center.x, center.y, radius);
        radius += rate;
        rate -= 0.1f;
        alpha = 100 - radius;
    }
    if (rate <= 0) {
        cout << "HIDING" << endl;
        triggered = false;
        rate = 5;
        radius = 20;
    }
}

void Trigger::setColor(int _color) {
    color = _color;
}

