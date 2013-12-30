#include "ofMain.h"
#include "testApp.h"

int main( ){
	ofSetupOpenGL(400,300, OF_WINDOW);
	ofRunApp( new testApp());
}
