#include <stdio.h>
#include <OpenNI.h>
#include <NiTE.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include "tinyxml2.h"

using namespace openni;
using namespace std;
using namespace tinyxml2;

//Based on Nite samples : SimpleUserTracker
#define MAX_USERS 10
bool g_visibleUsers[MAX_USERS] = { false };
nite::SkeletonState g_skeletonStates[MAX_USERS] = { nite::SKELETON_NONE };

#define USER_MESSAGE(msg) \
	{printf("[%08llu] User #%d:\t%s\n",ts, user.getId(),msg);}

void updateUserState(const nite::UserData& user, unsigned long long ts)
{
	if (user.isNew())
		USER_MESSAGE("New")
	else if (user.isVisible() && !g_visibleUsers[user.getId()])
		USER_MESSAGE("Visible")
	else if (!user.isVisible() && g_visibleUsers[user.getId()])
		USER_MESSAGE("Out of Scene")
	else if (user.isLost())
		USER_MESSAGE("Lost")

		g_visibleUsers[user.getId()] = user.isVisible();


	if (g_skeletonStates[user.getId()] != user.getSkeleton().getState())
	{
		switch (g_skeletonStates[user.getId()] = user.getSkeleton().getState())
		{
		case nite::SKELETON_NONE:
			USER_MESSAGE("Stopped tracking.")
				break;
		case nite::SKELETON_CALIBRATING:
			USER_MESSAGE("Calibrating...")
				break;
		case nite::SKELETON_TRACKED:
			USER_MESSAGE("Tracking!")
				break;
		case nite::SKELETON_CALIBRATION_ERROR_NOT_IN_POSE:
		case nite::SKELETON_CALIBRATION_ERROR_HANDS:
		case nite::SKELETON_CALIBRATION_ERROR_LEGS:
		case nite::SKELETON_CALIBRATION_ERROR_HEAD:
		case nite::SKELETON_CALIBRATION_ERROR_TORSO:
			USER_MESSAGE("Calibration Failed... :-|")
				break;
		}
	}
}


void WriteSkeletonToFile(const nite::UserData& user, std::string filename, int frame) {

	std::ofstream skeletonFile;
	skeletonFile.open(filename + ".txt", std::fstream::out | std::fstream::app);

	const nite::SkeletonJoint& head = user.getSkeleton().getJoint(nite::JOINT_HEAD);
	const nite::SkeletonJoint& left_elbow = user.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW);
	const nite::SkeletonJoint& left_foot = user.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT);
	const nite::SkeletonJoint& left_hand = user.getSkeleton().getJoint(nite::JOINT_LEFT_HAND);
	const nite::SkeletonJoint& left_hip = user.getSkeleton().getJoint(nite::JOINT_LEFT_HIP);
	const nite::SkeletonJoint& left_knee = user.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE);
	const nite::SkeletonJoint& left_shoulder = user.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER);
	const nite::SkeletonJoint& neck = user.getSkeleton().getJoint(nite::JOINT_NECK);
	const nite::SkeletonJoint& right_elbow = user.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW);
	const nite::SkeletonJoint& right_foot = user.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT);
	const nite::SkeletonJoint& right_hand = user.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND);
	const nite::SkeletonJoint& right_hip = user.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP);
	const nite::SkeletonJoint& right_knee = user.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE);
	const nite::SkeletonJoint& right_shoulder = user.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER);
	const nite::SkeletonJoint& torso = user.getSkeleton().getJoint(nite::JOINT_TORSO);

	skeletonFile << " FRAME : " << frame << "\n";
	//if(head.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " HEAD - x: " << head.getPosition().x << " y: " << head.getPosition().y << " z: " << head.getPosition().z << "\n" ;
	//if(left_elbow.getPositionConfidence() > .5)	
		skeletonFile << user.getId() << " LEFT_ELBOW - x: " << left_elbow.getPosition().x << "y: " << left_elbow.getPosition().y << " z: " << left_elbow.getPosition().z << "\n";
	//if(left_foot.getPositionConfidence() > .5)	
		skeletonFile << user.getId() << " LEFT_FOOT - x: " << left_foot.getPosition().x << " y: " << left_foot.getPosition().y << " z: " << left_foot.getPosition().z << "\n";
	//if(left_hand.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " LEFT_HAND - x: " << left_hand.getPosition().x << " y: " << left_hand.getPosition().y << " z: " << left_hand.getPosition().z << "\n";
	//if(left_hip.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " LEFT_HIP - x: " << left_hip.getPosition().x << " y: " << left_hip.getPosition().y << " z: " << left_hip.getPosition().z << "\n";
	//if(left_knee.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " LEFT_KNEE - x: " << left_knee.getPosition().x << " y: " << left_knee.getPosition().y << " z: " << left_knee.getPosition().z << "\n";
	//if(left_shoulder.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " LEFT_SHOULDER - x: " << left_shoulder.getPosition().x << " y: " << left_shoulder.getPosition().y << " z: " << left_shoulder.getPosition().z << "\n";
	//if(neck.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " NECK - x: " <<  neck.getPosition().x << " y: " << neck.getPosition().y << " z: " << neck.getPosition().z << "\n";
	//if(right_elbow.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " RIGHT_ELBOW - x: " << right_elbow.getPosition().x << " y: " << right_elbow.getPosition().y << " z: " << right_elbow.getPosition().z << "\n";
	//if(right_foot.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " RIGHT_FOOT - x: " << right_foot.getPosition().x << " y: " << right_foot.getPosition().y << " z: " <<  right_foot.getPosition().z << "\n";
	//if(right_hand.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " RIGHT_HAND - x: " << right_hand.getPosition().x << " y: "<< right_hand.getPosition().y << " z: " << right_hand.getPosition().z << "\n";
	//if(right_hip.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " RIGHT_HIP - x: " <<  right_hip.getPosition().x << " y: " << right_hip.getPosition().y << " z: " <<  right_hip.getPosition().z << "\n";
	//if(right_knee.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " RIGHT_KNEE - x: "<< right_knee.getPosition().x << " y: " << right_knee.getPosition().y << " z: " << right_knee.getPosition().z << "\n";
	//if(right_shoulder.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " RIGHT_SHOULDER - x: " << right_shoulder.getPosition().x << " y: " << right_shoulder.getPosition().y << " z: " << right_shoulder.getPosition().z << "\n";
	//if(torso.getPositionConfidence() > .5)
		skeletonFile << user.getId() << " TORSO - x: " << torso.getPosition().x << " y: " << torso.getPosition().y << " z: " << torso.getPosition().z << "\n";

	skeletonFile.close();
}

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

int WriteSkeletonToXML(const nite::UserData& user, std::string filename, int frame, int newXML)
{
	std::string name = filename + ".xml";
	XMLDocument xmlDoc;
	XMLError eResult;
	XMLNode *pRoot;
	XMLElement *pElement;
	XMLElement *pElement2;
	XMLElement *pElement3;
	XMLElement * pPrecedent = nullptr;
	XMLElement *pIter;

	const nite::SkeletonJoint& head = user.getSkeleton().getJoint(nite::JOINT_HEAD);
	const nite::SkeletonJoint& left_elbow = user.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW);
	const nite::SkeletonJoint& left_foot = user.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT);
	const nite::SkeletonJoint& left_hand = user.getSkeleton().getJoint(nite::JOINT_LEFT_HAND);
	const nite::SkeletonJoint& left_hip = user.getSkeleton().getJoint(nite::JOINT_LEFT_HIP);
	const nite::SkeletonJoint& left_knee = user.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE);
	const nite::SkeletonJoint& left_shoulder = user.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER);
	const nite::SkeletonJoint& neck = user.getSkeleton().getJoint(nite::JOINT_NECK);
	const nite::SkeletonJoint& right_elbow = user.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW);
	const nite::SkeletonJoint& right_foot = user.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT);
	const nite::SkeletonJoint& right_hand = user.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND);
	const nite::SkeletonJoint& right_hip = user.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP);
	const nite::SkeletonJoint& right_knee = user.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE);
	const nite::SkeletonJoint& right_shoulder = user.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER);
	const nite::SkeletonJoint& torso = user.getSkeleton().getJoint(nite::JOINT_TORSO);

	if (newXML)
	{
		pRoot = xmlDoc.NewElement("FrameList");
		xmlDoc.InsertFirstChild(pRoot);
		pElement = xmlDoc.NewElement("Frame");
		pElement->SetAttribute("number", (int)frame);
		pElement2 = xmlDoc.NewElement("User");
		pElement2->SetAttribute("number", (int)user.getId());
		pRoot->InsertEndChild(pElement);
		printf("First frame %d\n", frame);

	}
	else
	{
		eResult = xmlDoc.LoadFile(name.c_str());
		XMLCheckResult(eResult);

		pRoot = xmlDoc.FirstChild();
		if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

		pIter = pRoot->FirstChildElement("Frame");

		while (pIter != nullptr)
		{
			// Store pIter as the best known location for the new 'timeStamp'
			pPrecedent = pIter;
			// Attempt to find the next 'timeStamp' element
			pIter = pIter->NextSiblingElement("Frame");

		}

		int num;

		if (pPrecedent != nullptr)
		{

			eResult = pPrecedent->QueryIntAttribute("number", &num);
			XMLCheckResult(eResult);
			if (num == frame)
			{
				pElement = pPrecedent;

			}
			else
			{
				pElement = xmlDoc.NewElement("Frame");
				pElement->SetAttribute("number", (int)frame);
				pRoot->InsertEndChild(pElement);
			}
		}
		else
		{
			pElement = xmlDoc.NewElement("Frame");
			pElement->SetAttribute("number", (int)frame);
			pRoot->InsertEndChild(pElement);
		}

		pElement2 = xmlDoc.NewElement("User");
		pElement2->SetAttribute("number", (int)user.getId());
		

	}

	pElement3 = xmlDoc.NewElement("HEAD");
	pElement3->SetAttribute("x", (float)head.getPosition().x);
	pElement3->SetAttribute("y", (float)head.getPosition().y);
	pElement3->SetAttribute("z", (float)head.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("LEFT_ELBOW");
	pElement3->SetAttribute("x", (float)left_elbow.getPosition().x);
	pElement3->SetAttribute("y", (float)left_elbow.getPosition().y);
	pElement3->SetAttribute("z", (float)left_elbow.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("LEFT_FOOT");
	pElement3->SetAttribute("x", (float)left_foot.getPosition().x);
	pElement3->SetAttribute("y", (float)left_foot.getPosition().y);
	pElement3->SetAttribute("z", (float)left_foot.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("LEFT_HAND");
	pElement3->SetAttribute("x", (float)left_hand.getPosition().x);
	pElement3->SetAttribute("y", (float)left_hand.getPosition().y);
	pElement3->SetAttribute("z", (float)left_hand.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("LEFT_HIP");
	pElement3->SetAttribute("x", (float)left_hip.getPosition().x);
	pElement3->SetAttribute("y", (float)left_hip.getPosition().y);
	pElement3->SetAttribute("z", (float)left_hip.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("LEFT_KNEE");
	pElement3->SetAttribute("x", (float)left_knee.getPosition().x);
	pElement3->SetAttribute("y", (float)left_knee.getPosition().y);
	pElement3->SetAttribute("z", (float)left_knee.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("LEFT_SHOULDER");
	pElement3->SetAttribute("x", (float)left_shoulder.getPosition().x);
	pElement3->SetAttribute("y", (float)left_shoulder.getPosition().y);
	pElement3->SetAttribute("z", (float)left_shoulder.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("NECK");
	pElement3->SetAttribute("x", (float)neck.getPosition().x);
	pElement3->SetAttribute("y", (float)neck.getPosition().y);
	pElement3->SetAttribute("z", (float)neck.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("RIGHT_ELBOW");
	pElement3->SetAttribute("x", (float)right_elbow.getPosition().x);
	pElement3->SetAttribute("y", (float)right_elbow.getPosition().y);
	pElement3->SetAttribute("z", (float)right_elbow.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("RIGHT_FOOT");
	pElement3->SetAttribute("x", (float)right_foot.getPosition().x);
	pElement3->SetAttribute("y", (float)right_foot.getPosition().y);
	pElement3->SetAttribute("z", (float)right_foot.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("RIGHT_HAND");
	pElement3->SetAttribute("x", (float)right_hand.getPosition().x);
	pElement3->SetAttribute("y", (float)right_hand.getPosition().y);
	pElement3->SetAttribute("z", (float)right_hand.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("RIGHT_HIP");
	pElement3->SetAttribute("x", (float)right_hip.getPosition().x);
	pElement3->SetAttribute("y", (float)right_hip.getPosition().y);
	pElement3->SetAttribute("z", (float)right_hip.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("RIGHT_KNEE");
	pElement3->SetAttribute("x", (float)right_knee.getPosition().x);
	pElement3->SetAttribute("y", (float)right_knee.getPosition().y);
	pElement3->SetAttribute("z", (float)right_knee.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("RIGHT_SHOULDER");
	pElement3->SetAttribute("x", (float)right_shoulder.getPosition().x);
	pElement3->SetAttribute("y", (float)right_shoulder.getPosition().y);
	pElement3->SetAttribute("z", (float)right_shoulder.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement3 = xmlDoc.NewElement("TORSO");
	pElement3->SetAttribute("x", (float)torso.getPosition().x);
	pElement3->SetAttribute("y", (float)torso.getPosition().y);
	pElement3->SetAttribute("z", (float)torso.getPosition().z);
	pElement2->InsertEndChild(pElement3);
	pElement->InsertEndChild(pElement2);
	//pRoot->InsertEndChild(pElement);

	eResult = xmlDoc.SaveFile(name.c_str());
	XMLCheckResult(eResult);

	//system("pause");

	return XML_SUCCESS;
}



int main()
{
	openni::Status rc = openni::OpenNI::initialize();
	openni::Device device;
	openni::VideoStream video;
	//openni::SensorType sensor;
	nite::Status niteRc = nite:: NiTE::initialize();
	nite::UserTracker userTracker;
	nite::UserTrackerFrameRef userTrackerFrame;
	int OniLength;
	int frames;
	//string infolder_name;
	//string outfolder_name;
	string infile_name;
	string outfile_name;
	vector<string> files;
	vector<string> tokens;

	//cout << "Enter directory of infolder (use /)\n";
	//getline(cin, infile_name);
	infile_name = "C:/Users/Eotw/Desktop/Thetis_ONI/ONI_EXPERTS/backhand/p15.oni";
	//files = getFilesFromFolder(infolder_name);

	//cout << "Enter directory of outfolder/name\n";
	//getline(cin, outfile_name);
	outfile_name = "C:/Users/Eotw/Desktop/test";

	//na bgalo ta system meta
	rc = device.open(infile_name.c_str());
	if (rc != openni::STATUS_OK)
	{
		printf("Couldn't open file\n%s\n", OpenNI::getExtendedError());
		return 1;
	}

	rc = video.create(device, openni::SENSOR_DEPTH);
	if (rc != openni::STATUS_OK)
	{
		printf("Couldnt create video\n%s\n", OpenNI::getExtendedError());
		return 1;
	}

		
	niteRc = userTracker.create(&device);

	if (niteRc != nite::STATUS_OK)
	{
		printf("Couldn't open file\n%s\n", OpenNI::getExtendedError());
		return 1;
	}


	if (device.isFile())
	{
		printf("Opened a file\n");
		OniLength = device.getPlaybackControl()->getNumberOfFrames(video);
		printf("OniLength = %s\n", std::to_string(OniLength).c_str());
	}
	else
	{
		printf("Working only for pre-recorded .oni files\n");
		return 1;
	}


	int newXML = -1;
	for (frames = 0; frames < OniLength; frames++)
	{
		niteRc = userTracker.readFrame(&userTrackerFrame);
		if (niteRc != nite::STATUS_OK)
		{
			printf("Get next frame failed\n");
			continue;
		}

		const nite::Array<nite::UserData>& users = userTrackerFrame.getUsers();
		for (int i = 0; i < users.getSize(); ++i)
		{
			const nite::UserData& user = users[i];
			updateUserState(user, userTrackerFrame.getTimestamp());
			if (user.isNew())
			{
				userTracker.startSkeletonTracking(user.getId());
			}
			else if (user.getSkeleton().getState() == nite::SKELETON_TRACKED)
			{					
				WriteSkeletonToFile(user, outfile_name, frames);
				if (newXML == -1)
				{
					WriteSkeletonToXML(user, outfile_name, frames, 1);
					newXML = 1;
				}
				else
					WriteSkeletonToXML(user, outfile_name, frames, 0);
				
			}

		}

	}



	printf("frames = %s\n", to_string(frames).c_str());	
	nite::NiTE::shutdown();
	system("pause");

}