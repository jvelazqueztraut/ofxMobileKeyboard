/*
 * ofxMobileKeyboard.h
 *
 *  Created on: 13/03/2015
 *      Author: Enric Marco -- Relabtive
 */

#pragma once

#ifndef __ofxMobileKeyboard__
#define __ofxMobileKeyboard__

#include "ofMain.h"

#ifdef TARGET_ANDROID
	#include "ofxAndroid.h"
	#include <jni.h>
#endif
#ifdef TARGET_OF_IOS
    #include "ofxiOS.h"
    #include "ofxiOSExtras.h"
#endif

class ofxMobileKeyboard {


private:


#ifdef TARGET_ANDROID
	void setupJNI();
	void setHint();

    const char *pathName;
    const char *hint;
	const char *prefix, *sufix;
    int posXint, posYint, widthint, heightint;

	jclass javaClass;
	jclass localClass;
	jstring s;
	jstring hintString;
	jmethodID javaReturnMethod;
	jmethodID javaReturnMethodAux;
	jobject javaObject;

#endif

#ifdef TARGET_OF_IOS
    ofxiOSKeyboard * keyboard;
#endif


	float posX, posY, width, height;

	string str;

	bool isActive;


public:


#ifdef TARGET_ANDROID

	void setup(const char * projectName, const char * prefix, const char * sufix);
	void showKeyboard();
	void hideKeyboard();
	bool isKeyboardActive();

#endif



#ifdef TARGET_OF_IOS

    void setup(float x, float y, float w, float h);
    void setup(string hintString, float x, float y, float w, float h);
    string recieveKeyboard();
    void showKeyboard();
    void hideKeyboard();
    bool isKeyboardActive();
    void setBackgroundColor(int r, int g, int b, int a);
    void setFontColor(int r, int g, int b, int a);

#endif


};

#endif /* defined(__ofxMobileKeyboard__) */

