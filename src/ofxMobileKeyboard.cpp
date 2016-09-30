/*
 * ofxMobileKeyboard.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Enric Marco -- Relabtive
 */

#include "ofMain.h"
#include "ofxMobileKeyboard.h"

#ifdef TARGET_ANDROID

//--------------------------------------------------------------
void ofxMobileKeyboard::setup (const char * _projectName, const char * _prefix, const char * _sufix){

	pathName = _projectName;
	prefix = _prefix;
	sufix =  _sufix;

	isActive = false;

	setupJNI();

}

//---------------------------------------------------------------
void ofxMobileKeyboard::setupJNI (){

	ofLogNotice("ofxMobileKeyboard") << "Setting up JNI" << endl;
	JNIEnv *env = ofGetJNIEnv();

	char result[500];

	strcpy(result,prefix);
	strcat(result,pathName);
	strcat(result,sufix);

	localClass = env->FindClass(result);

    //get OFActivity class from java
    javaClass = (jclass) env->NewGlobalRef(localClass);
    if (!javaClass) {
        ofLogError("ofxMobileKeyboard") << "javaClass NOT found!" << endl;
    }else if(javaClass){
        ofLogNotice("ofxMobileKeyboard") << "javaClass found!" << endl;
    }

    //get OFActiviy object from java
    javaObject = ofGetOFActivityObject();
    javaObject = (jobject) env->NewGlobalRef(javaObject);
    if (!javaObject) {
        ofLogError("ofxMobileKeyboard") << "javaObject NOT created!" << endl;
    }else if(javaObject) {
        ofLogNotice("ofxMobileKeyboard") << "javaObject created!" << endl;
    }

}

//-----------------------------------------------------------------
void ofxMobileKeyboard::showKeyboard(){
    if(!isActive){
    	JNIEnv *env = ofGetJNIEnv();

    	javaReturnMethod = env->GetMethodID(javaClass,"showKeyboard","()V");
    	if(!javaReturnMethod){
    		ofLog() << "showKeyboard Method NOT found!" << endl;
    	}else if(javaReturnMethod){
    		ofLog() << "showKeyboard Method found!" << endl;
    	}

    	env->CallVoidMethod(javaObject, javaReturnMethod);
        isActive = true;
    }
}

//-------------------------------------------------------------------
void ofxMobileKeyboard::hideKeyboard(){
    if(isActive){
    	JNIEnv *env = ofGetJNIEnv();

    	 javaReturnMethod = env->GetMethodID(javaClass,"hideKeyboard","()V");
    	if(!javaReturnMethod){
    		ofLog() << "hideKeyboard Method NOT found!" << endl;
    	}else if(javaReturnMethod){
    		ofLog() << "hideKeyboard Method found!" << endl;
    	}

    	env->CallVoidMethod(javaObject, javaReturnMethod);

        isActive = false;
    }
}

//---------------------------------------------------------------------
bool ofxMobileKeyboard::isKeyboardActive(){
	return isActive;
}

#endif


#ifdef TARGET_OF_IOS

void ofxMobileKeyboard::setup(float x, float y, float w, float h){

        posX = x;
        posY = y;
        width = w;
        height = h;

        isActive = false;
        str = "";

        keyboard = new ofxiOSKeyboard(posX, posY, width, height);

        keyboard->setPosition(posX, posY);
        keyboard->setBgColor(255,255,255,255);
        keyboard->setFontColor(0,0,0,255);
        keyboard->setFontSize(height-5);
        keyboard->setPlaceholder("Type your message here");

    }

    void ofxMobileKeyboard::setup(string hintString, float x, float y, float w, float h){

        posX = x;
        posY = y;
        width = w;
        height = h;

        isActive = false;
        str = "";

        keyboard = new ofxiOSKeyboard(posX, posY, width, height);

        keyboard->setPosition(posX, posY);
        keyboard->setBgColor(255,255,255,255);
        keyboard->setFontColor(0,0,0,255);
        keyboard->setFontSize(height-5);
        keyboard->setPlaceholder(hintString);

    }

    string ofxMobileKeyboard::recieveKeyboard(){
        str = keyboard->getLabelText();

        return str;
    }

    void ofxMobileKeyboard::showKeyboard(){
        isActive = true;
        keyboard->openKeyboard();
        keyboard->setVisible(true);

    };
    void ofxMobileKeyboard::hideKeyboard(){
        isActive = false;
        keyboard->setVisible(false);
    };

    bool ofxMobileKeyboard::isKeyboardActive(){
        return isActive;
    };

    void ofxMobileKeyboard::setBackgroundColor(int r, int g, int b, int a){
        keyboard->setBgColor(r,g,b,a);
    }

    void ofxMobileKeyboard::setFontColor(int r, int g, int b, int a){
        keyboard->setFontColor(r,g,b,a);
    }

#endif


