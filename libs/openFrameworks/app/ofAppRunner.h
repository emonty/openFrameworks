#pragma once

#include "ofConstants.h"
#include "ofPoint.h"
#include "ofRectangle.h"

class ofAppBaseWindow;
class ofBaseApp;

void 		ofSetupOpenGL(ofAppBaseWindow * windowPtr, int w, int h, int screenMode);	// sets up the opengl context!
void 		ofSetupOpenGL(int w, int h, int screenMode);	// sets up the opengl context!
void 		ofRunApp(ofBaseApp * OFSA = NULL);
ofBaseApp * ofGetAppPtr();

//-------------------------- time
float 		ofGetFrameRate();
int			ofGetFrameNum();
void 		ofSetFrameRate(int targetRate);
void		ofSleepMillis(int millis);
double		ofGetLastFrameTime();

//-------------------------- cursor
void 		ofHideCursor();
void 		ofShowCursor();
//-------------------------- window / screen
int 		ofGetWindowPositionX();
int 		ofGetWindowPositionY();
int 		ofGetScreenWidth();
int 		ofGetScreenHeight();
int			ofGetWindowMode();
int 		ofGetWidth();			// <-- should we call this ofGetWindowWidth?
int 		ofGetHeight();
ofPoint		ofGetWindowSize();
ofRectangle	ofGetWindowRect();

void 		ofSetWindowPosition(int x, int y);
void 		ofSetWindowShape(int width, int height);
void 		ofSetWindowTitle(string title);
void		ofEnableSetupScreen();
void		ofDisableSetupScreen();
void		ofSetFullscreen(bool fullscreen);
void		ofToggleFullscreen();
//-------------------------- sync
void 		ofSetVerticalSync(bool bSync);

//-------------------------- mouse/key query
bool		ofGetMousePressed(int button=-1); //by default any button
bool		ofGetKeyPressed(int key=-1); //by default any key

int			ofGetMouseX();
int			ofGetMouseY();

int			ofGetPreviousMouseX();
int			ofGetPreviousMouseY();
