#pragma once
#include "VisionDeviceManager.hpp"

class SkeletonManager {
private:
	VisionDeviceManager::Ptr visionDeviceManager;
	vector<CommonSkeleton> commonSkeletons;
	
	bool isSkeletonTrackingActivated = false;
	
	ARVboMesh::Ptr allSkeletonMesh = make_shared<ARVboMesh>();
	ARVboMesh::Ptr handSkeletonMesh = make_shared<ARVboMesh>();
	ofMatrix4x4 system_pose;

	int depthWidth, depthHeight;
	int colorWidth, colorHeight;

	// 받아오는 joint 저장할 것 필요

public:
	typedef shared_ptr<SkeletonManager> Ptr;

private:
	// player_idx, point (L_Hand, R_Hand) 순서
	vector<vector<ofPoint>> handPoints_2d;
	vector<vector<ofPoint>> handPoints_3d;
	void makeAllJointsMesh();
	void makeHandJointMesh();
	void makeJointPoints();


public:
	void init(VisionDeviceManager::Ptr _visionDeviceManager) {
		visionDeviceManager = _visionDeviceManager;
	}

	void setup();
	void update();
	void drawAllJointsDebug(int x, int y, int w, int h);
	void meshDrawAllJointsDebug();
	void drawHandJointsDebug(int x, int y, int w, int h);
	void meshDrawHandJointsDebug();

	bool getIsSkeletonTrackingActivate() {
		return isSkeletonTrackingActivated;
	}

	void setIsSkeletonTrackingActivate(bool isSkeletonTrackingActivated) {
		this->isSkeletonTrackingActivated = isSkeletonTrackingActivated;
	}

	ARVboMesh::Ptr getAllSkeletonMesh() {
		return allSkeletonMesh;
	}
	ARVboMesh::Ptr getHandSkeletonMesh() {
		return handSkeletonMesh;
	}
	vector<vector<ofPoint>> getHandPoints_2d() {
		return handPoints_2d;
	}
	vector<vector<ofPoint>> getHandPoints_3d() {
		return handPoints_3d;
	}

};