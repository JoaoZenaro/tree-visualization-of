#pragma once

#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"

// node structure definition
typedef struct Node {
	int data;
	Node* left;
	Node* right;
};

// open frameworks required setup
class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();

	void keyPressed(int key);

	// custom 'draw' function
	void printTree(int x, int y, Node* root, int index);

	// 3rd party header for drawing centered strings
	ofxCenteredTrueTypeFont font;
};