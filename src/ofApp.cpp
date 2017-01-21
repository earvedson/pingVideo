#include "ofApp.h"

bool lightIsOn[3] = {false, false, false};

double centimetersPerSecond = 34300;

uint64_t initEndTime;
uint64_t sendEndTime;
uint64_t startTime;
uint64_t endTime;
double lastDistance = 0;

bool pingInInit = false;
bool sendingPing = false;
bool waitingForEcho = false;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(54, 54, 54, 255);
	wiringPiSetup();
	// LEDs
	pinMode(4,OUTPUT);
	digitalWrite(4, LOW);
	pinMode(5,OUTPUT);
	digitalWrite(5, LOW);
	pinMode(6,OUTPUT);
	digitalWrite(6, LOW);
	// Ping
	pinMode(TRIGGER_PIN,OUTPUT); // trigger
	pinMode(ECHO_PIN,INPUT); // echo

	arial30.load("Arial.ttf", 30, true, true);
	arial30.setLineHeight(34.0f);
	arial30.setLetterSpacing(1.035);

	ofSetLogLevel(OF_LOG_VERBOSE);
}

//--------------------------------------------------------------
void ofApp::update(){
	/*
	if (pingInInit == true) {
		if (ofGetElapsedTimeMillis() > initEndTime) {
			pingInInit = false;
			sendPing();
		}
	}
	if (sendingPing) {
		if (ofGetElapsedTimeMillis() > sendEndTime) {
			sendingPing = false;
			ofLogVerbose() << "ping length: " << (ofGetElapsedTimeMillis() - startTime);
			digitalWrite(TRIGGER_PIN, LOW);
		}
	}
	if (waitingForEcho) {
		if (digitalRead(ECHO_PIN) == HIGH) {
			endPing();
		}
	}
	*/


	startTime = ofGetElapsedTimeMillis();
	digitalWrite(TRIGGER_PIN, LOW);
	ofSleepMillis(2);
	digitalWrite(TRIGGER_PIN, HIGH);
	ofSleepMillis(1);
	digitalWrite(TRIGGER_PIN, LOW);
	ofLogVerbose() << "ping time: " << (ofGetElapsedTimeMillis() - startTime);
	while (digitalRead(ECHO_PIN) == LOW) {
		startTime = ofGetElapsedTimeMillis();
	}
	while (digitalRead(ECHO_PIN) == HIGH) {
		endTime = ofGetElapsedTimeMillis();
	}	
	lastDistance = (endTime - startTime) * 17.150;
	ofLogVerbose() << "distance: " << lastDistance;
	ofSleepMillis(10);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(245,58,135);
	char statusString[255]; // an array of chars
	sprintf(statusString, "Waiting for echo: %i - distance: %f", waitingForEcho, lastDistance);
	arial30.drawString(statusString, 30, 60);

}

void ofApp::triggerPing() {
	initPing();
}

void ofApp::initPing() {
	ofLogVerbose() << "initPing";
	digitalWrite(TRIGGER_PIN, LOW);
	waitingForEcho = false; // reset
	initEndTime = ofGetElapsedTimeMillis() + 2;
	pingInInit = true;
}

void ofApp::sendPing() {	
	ofLogVerbose() << "sendPing";
	digitalWrite(TRIGGER_PIN, HIGH);
	startTime = ofGetElapsedTimeMillis();
	sendEndTime = startTime + 5;
	sendingPing = true;
	waitingForEcho = true;
}

void ofApp::endPing() {
	ofLogVerbose() << "endPing";
	waitingForEcho = false;
	endTime = ofGetElapsedTimeMillis();
	lastDistance = (endTime - startTime) * 34300 / 2;
	ofLogNotice() << "Distance: " << lastDistance;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch(key){
		case '1':
			lightIsOn[0] = !lightIsOn[0];
			digitalWrite(4,lightIsOn[0] ? HIGH : LOW);
			break;
		case '2':
			lightIsOn[1] = !lightIsOn[1];
			digitalWrite(5,lightIsOn[1] ? HIGH : LOW);
			break;
		case '3':
			lightIsOn[2] = !lightIsOn[2];
			digitalWrite(6,lightIsOn[2] ? HIGH : LOW);
			break;
		case 'p':
			triggerPing();
			break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}