#include "ofApp.h"

#define USE_KINECT2 true
#define USE_SKELETON true

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofEnableDepthTest();

#if USE_KINECT2
	manager = VisionDeviceManager::Kinect2_Ptr();

	manager->setup();
	manager->setFlipHorizontal(true);
	manager->setFlipVertical(false);

	manager->setMapColorToDepth(true);
	manager->setMapDepthToCamera(true);
#endif

#if USE_SKELETON
	skeletonManager.init(manager);
	skeletonManager.setup();
#endif
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
#if USE_KINECT2
	manager->update();
#endif
#if USE_SKELETON
	if (skeletonManager.getIsSkeletonTrackingActivate()) {
		skeletonManager.update();
	}
#endif
}

//--------------------------------------------------------------
void ofApp::draw(){
#if USE_SKELETON
	if (skeletonManager.getIsSkeletonTrackingActivate()) {
//		ofPushMatrix();
//		ofPushStyle();
//		skeletonManager.drawAllJointsDebug(0, 0, manager->getColorWidth() / 2, manager->getColorHeight() / 2);
//		skeletonManager.drawAllJointsDebug(0, 0, manager->getColorWidth(), manager->getColorHeight());
//		skeletonManager.drawHandJointsDebug(manager->getColorWidth() / 2, 0, manager->getColorWidth() / 2, manager->getColorHeight() / 2);
//		/*
		viewer.begin();
		ofSetBackgroundColor(ofColor::black);
		ofDrawAxis(2000);
		ofPushStyle();
		ofSetColor(ofColor::white);
		ofPushMatrix();
		ofRotate(90, 0, 0, -1);
		ofDrawGridPlane(500, 7, true);
		ofPopMatrix();
		ofPopStyle();
		
		ofPushMatrix();
		manager->getPointCloudMesh().draw();
		ofPopMatrix();

		skeletonManager.meshDrawAllJointsDebug();
//		skeletonManager.meshDrawHandJointsDebug();
		viewer.end();
//		*/
//		ofPopStyle();
//		ofPushMatrix();
	}
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	constexpr float move_offset = 10.f;
	constexpr float angle_offset = 1.f;
	viewer.keyPressed(key);
	switch (key) {
	case OF_KEY_LEFT_SHIFT: shift_pressed = true; break;
	}
#if USE_SKELETON
	if (key == 's' || key == 'S') {
		skeletonManager.setIsSkeletonTrackingActivate(true);
	}
#endif
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case OF_KEY_LEFT_SHIFT:
		shift_pressed = false;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (shift_pressed == false) {
		viewer.mouseDragged(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	viewer.mousePressed(x, y, button);
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
