#pragma once

#include "ofMain.h"
#include "ofxDeckLink.h"

class ofApp : public ofBaseApp
{

public:
    void setup();
    void update();
    void draw();

    void keyPressed( int key );

    ofxDeckLinkAPI::Input input;

};
