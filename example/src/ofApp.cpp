#include "ofApp.h"

void ofApp::setup()
{
    ofSetVerticalSync( true );
    ofSetFrameRate( 60 );

    if( input.setup( 0 ) ) {
        input.start( bmdModeHD1080i5994 );
    }
}

void ofApp::update()
{
    input.update();
}

void ofApp::draw()
{
    ofClear( 0 );
    input.draw( 0, 0, ofGetWidth(), ofGetHeight() );

    ofDrawBitmapStringHighlight( ofToString( ofGetFrameRate() ), 10, 20 );
    ofDrawBitmapStringHighlight( ofToString( input.getDrawMode() ), 10, 40 );
    ofDrawBitmapStringHighlight( input.getTimecodeString(), 10, 60 );
}

void ofApp::keyPressed( int key )
{
    if( key == 'f' ) {
        ofToggleFullscreen();
    }

    if( key == '1' ) {
        input.setDrawMode( ofxDeckLinkAPI::Input::DRAWMODE_PROGRESSIVE );
    }

    if( key == '2' ) {
        input.setDrawMode( ofxDeckLinkAPI::Input::DRAWMODE_UPPERFIELD );
    }

    if( key == '3' ) {
        input.setDrawMode( ofxDeckLinkAPI::Input::DRAWMODE_LOWERFIELD );
    }

    if( key == '4' ) {
        input.setDrawMode( ofxDeckLinkAPI::Input::DRAWMODE_AUTOFIELD );
    }
}
