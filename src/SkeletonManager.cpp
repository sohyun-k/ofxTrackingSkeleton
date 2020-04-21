#include "SkeletonManager.h"

void SkeletonManager::makeAllJointsMesh()
{
	this->allSkeletonMesh->clear();
	this->allSkeletonMesh->setMode(OF_PRIMITIVE_POINTS);
	this->allSkeletonMesh->disableIndices();
	this->allSkeletonMesh->enableColors();
	// 포인트들을 Vertex에 추가
	int skeletonNum = this->commonSkeletons.size();
	for (int i = 0; i < skeletonNum; i++) {
		CommonSkeleton common_skeleton = this->commonSkeletons.at(i);
		ofColor randColor = ofColor(rand() % 255, rand() % 255, rand() % 255);
		for (int common_idx = 0; common_idx < CommonJointTable::COUNT; common_idx++) {
			CommonJoint joint = common_skeleton.joints[common_idx];
			ofPoint pt_3d = joint.point_3d;
			this->allSkeletonMesh->addVertex(pt_3d);
			this->allSkeletonMesh->addColor(randColor);
		}
	}
}

void SkeletonManager::makeHandJointMesh()
{
	this->handSkeletonMesh->clear();
	this->handSkeletonMesh->setMode(OF_PRIMITIVE_POINTS);
	this->handSkeletonMesh->disableIndices();
	this->handSkeletonMesh->enableColors();
	int skeletonNum = this->commonSkeletons.size();
	for (int i = 0; i < skeletonNum; i++) {
		CommonSkeleton common_skeleton = this->commonSkeletons.at(i);
		ofColor randColor = ofColor(rand() % 255, rand() % 255, rand() % 255);
		CommonJoint L_hand_joint = common_skeleton.joints[CommonJointTable::L_Hand];
		this->handSkeletonMesh->addVertex(L_hand_joint.point_3d);
		this->handSkeletonMesh->addColor(randColor);
		CommonJoint R_hand_joint = common_skeleton.joints[CommonJointTable::R_Hand];
		this->handSkeletonMesh->addVertex(R_hand_joint.point_3d);
		this->handSkeletonMesh->addColor(randColor);
	}

}

void SkeletonManager::makeJointPoints()
{
	this->commonSkeletons = visionDeviceManager->getCommonSkeletons();
	// Hand Point만 추출하여 저장
	vector<ofPoint> joint_vec_2d, joint_vec_3d;
	for (int i = 0; i < this->commonSkeletons.size(); i++) {
		CommonSkeleton common_skeleton = this->commonSkeletons.at(i);
		int player_index = common_skeleton.player_index;
		CommonJoint L_hand_joint = common_skeleton.joints[CommonJointTable::L_Hand];
		CommonJoint R_hand_joint = common_skeleton.joints[CommonJointTable::R_Hand];
		joint_vec_2d.clear();
		joint_vec_3d.clear();
		joint_vec_2d.push_back(L_hand_joint.point_2d);
		joint_vec_2d.push_back(R_hand_joint.point_2d);
		joint_vec_3d.push_back(L_hand_joint.point_3d);
		joint_vec_3d.push_back(R_hand_joint.point_3d);
		handPoints_2d.push_back(joint_vec_2d);
		handPoints_3d.push_back(joint_vec_3d);
	}

}

void SkeletonManager::setup()
{
	//kinect setup
	depthWidth = visionDeviceManager->getDepthWidth();
	depthHeight = visionDeviceManager->getDepthHeight();
	colorWidth = visionDeviceManager->getColorWidth();
	colorHeight = visionDeviceManager->getColorHeight();
}

void SkeletonManager::update()
{
	visionDeviceManager->update();
	handPoints_2d.clear();
	handPoints_3d.clear();
	// 스켈레톤 받는것 다시 진행
	this->makeJointPoints();
}

void SkeletonManager::drawAllJointsDebug(int x, int y, int w, int h)
{
	ofImage colorImg = visionDeviceManager->getColorImage();
	float rescale_x = colorImg.getWidth() / visionDeviceManager->getDepthWidth();
	float rescale_y = colorImg.getHeight() / visionDeviceManager->getDepthHeight();
	float scale_x = w / colorImg.getWidth();
	float scale_y = h / colorImg.getHeight();

	//Joint들 모두 다 draw
	int skeletonNum = this->commonSkeletons.size();
	for (int i = 0; i < skeletonNum; i++) {
		CommonSkeleton common_skeleton = this->commonSkeletons.at(i);
		ofColor randColor = ofColor(rand() % 255, rand() % 255, rand() % 255);
		ofPushStyle();
		ofSetColor(randColor);
		for (int common_idx = 0; common_idx < CommonJointTable::COUNT; common_idx++) {
			CommonJoint joint = common_skeleton.joints[common_idx];
//			ofPoint pt_2d = joint.point_2d*ofPoint(scale_x, scale_y)*ofPoint(rescale_x, rescale_y) + ofPoint(x, y);
			ofPoint pt_2d = joint.point_2d;
			ofDrawCircle(pt_2d, 2);
		}
		ofPopStyle();
	}

//	colorImg.draw(x, y, w, h);
	colorImg.draw(x, y, visionDeviceManager->getDepthWidth(), visionDeviceManager->getDepthHeight());
}

void SkeletonManager::meshDrawAllJointsDebug()
{
	this->makeAllJointsMesh();
	ofPushMatrix();
	glPointSize(10);
	this->allSkeletonMesh->draw();
	glPointSize(1);
	ofPopMatrix();
}

void SkeletonManager::drawHandJointsDebug(int x, int y, int w, int h)
{
	ofImage colorImg = visionDeviceManager->getColorImage();
	float scale_x = w / colorImg.getWidth();
	float scale_y = h / colorImg.getHeight();

	//Joint들 모두 다 draw

	for (int idx = 0; idx < handPoints_2d.size(); idx++) {
		for (int hand_idx = 0; hand_idx < handPoints_2d.at(idx).size(); hand_idx++) {
			ofPoint pt = handPoints_2d.at(idx).at(hand_idx)*ofPoint(scale_x, scale_y) + ofPoint(x, y);
			ofDrawCircle(pt, 5);
		}
	}
	colorImg.draw(x, y, w, h);
}

void SkeletonManager::meshDrawHandJointsDebug()
{
	this->makeHandJointMesh();
	ofPushMatrix();
	glPointSize(10);
	this->handSkeletonMesh->draw();
	ofPopMatrix();
}





