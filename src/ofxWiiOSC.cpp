/*
 *  ofxWiiOSC.cpp
 *  ofxOpenNIPainter
 *
 *  Created by Patricio González Vivo on 24/02/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "ofxWiiOSC.h"

ofxWiiOSC::ofxWiiOSC(){
	receiver.setup(IN_PORT);
	sender.setup( OUT_HOST, OUT_PORT );
	isNunchuck = false;
}

void ofxWiiOSC::update(){
	while( receiver.hasWaitingMessages() ){
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		if ( m.getAddress() == "/wii/connected" )
			isConnected = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/mousemode" )
			mouseMode = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/a" )
			buttonA = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/b" )
			buttonB = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/up" )
			buttonUp = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/down" )
			buttonDown = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/left" )
			buttonLeft = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/right" )
			buttonRight = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/minus" )
			buttonMinus = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/plus" )
			buttonPlus = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/home" )
			buttonHome = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/one" )
			buttonOne = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/button/two" )
			buttonTwo = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/wii/acc" ){
				acc.x = m.getArgAsFloat( 0 );
				acc.y = m.getArgAsFloat( 1 );
				acc.z = m.getArgAsFloat( 2 );
		} else if ( m.getAddress() == "/wii/orientation" ){
			roll += (m.getArgAsFloat( 0 ) - roll)*0.04;
			pitch += (m.getArgAsFloat(1) - pitch)*0.04;
		} else if ( m.getAddress() == "/wii/irdata" ){
			ir[0].x = m.getArgAsFloat( 0 );
			ir[0].y = m.getArgAsFloat( 1 );
			ir[0].s = m.getArgAsFloat( 2 );
			ir[1].x = m.getArgAsFloat( 3 );
			ir[1].y = m.getArgAsFloat( 4 );
			ir[1].s = m.getArgAsFloat( 5 );
			ir[2].x = m.getArgAsFloat( 6 );
			ir[2].y = m.getArgAsFloat( 7 );
			ir[2].s = m.getArgAsFloat( 8 );
			ir[3].x = m.getArgAsFloat( 9 );
			ir[3].y = m.getArgAsFloat( 10 );
			ir[3].s = m.getArgAsFloat( 11 );
		} else if ( m.getAddress() == "/wii/batterylevel" ){
			batterylevel = m.getArgAsFloat( 0 );
		} else if ( m.getAddress() == "/nunchuk/joystick" ){
			nX = m.getArgAsFloat( 0 );
			nY = m.getArgAsFloat( 1 );
			isNunchuck = true;
 		} else if ( m.getAddress() == "/nunchuk/button/z" )
			buttonZ = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/nunchuk/button/c" )
			buttonC = (m.getArgAsInt32(0)==0)?false:true;
		else if ( m.getAddress() == "/nunchuk/acc" ){
			acc.x = m.getArgAsFloat( 0 );
			acc.y = m.getArgAsFloat( 1 );
			acc.z = m.getArgAsFloat( 2 );
		} else if ( m.getAddress() == "/nunchuk/orientation" ){
			nRoll += (m.getArgAsFloat( 0 ) - nRoll)*0.04;
			nPitch += (m.getArgAsFloat(1) - nPitch)*0.04;
		} 
	}
}

void ofxWiiOSC::draw(ofPoint pos){
	//if (isConnected){
		ofPushMatrix();
		ofTranslate(pos);
		ofSetColor(255);
		//glScalef(5, 40, 5);
		ofBox(0, 0, 0, 1);
		ofDrawAxis(20);
		//ofRect(pos.x, pos.y, 20, 60);
		ofPopMatrix();
		
	//}
}

void ofxWiiOSC::requestBatteryLevel(){
	ofxOscMessage m;
	m.setAddress( "/wii/batterylevel" );
	sender.sendMessage( m );
}

void ofxWiiOSC::setLed(int n1, int n2, int n3, int n4){
	ofxOscMessage m;
	m.setAddress( "/wii/led" );
	m.addIntArg( n1 );
	m.addIntArg( n2 );
	m.addIntArg( n3 );
	m.addIntArg( n4 );
	sender.sendMessage( m );
}