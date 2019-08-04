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


using namespace openni;
using namespace std;

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

	skeletonFile << user.getId() << " HEAD - x: " << head.getPosition().x << " y: " << head.getPosition().y << " z: " << head.getPosition().z << "\n" ;
	skeletonFile << user.getId() << " LEFT_ELBOW - x: " << left_elbow.getPosition().x << "y: " << left_elbow.getPosition().y << " z: " << left_elbow.getPosition().z << "\n";
	skeletonFile << user.getId() << " LEFT_FOOT - x: " << left_foot.getPosition().x << " y: " << left_foot.getPosition().y << " z: " << left_foot.getPosition().z << "\n";
	skeletonFile << user.getId() << " LEFT_HAND - x: " << left_hand.getPosition().x << " y: " << left_hand.getPosition().y << " z: " << left_hand.getPosition().z << "\n";
	skeletonFile << user.getId() << " LEFT_HIP - x: " << left_hip.getPosition().x << " y: " << left_hip.getPosition().y << " z: " << left_hip.getPosition().z << "\n";
	skeletonFile << user.getId() << " LEFT_KNEE - x: " << left_knee.getPosition().x << " y: " << left_knee.getPosition().y << " z: " << left_knee.getPosition().z << "\n";
	skeletonFile << user.getId() << " LEFT_SHOULDER - x: " << left_shoulder.getPosition().x << " y: " << left_shoulder.getPosition().y << " z: " << left_shoulder.getPosition().z << "\n";
	skeletonFile << user.getId() << " NECK - x: " <<  neck.getPosition().x << " y: " << neck.getPosition().y << " z: " << neck.getPosition().z << "\n";
	skeletonFile << user.getId() << " RIGHT_ELBOW - x: " << right_elbow.getPosition().x << " y: " << right_elbow.getPosition().y << " z: " << right_elbow.getPosition().z << "\n";
	skeletonFile << user.getId() << " RIGHT_FOOT - x: " << right_foot.getPosition().x << " y: " << right_foot.getPosition().y << " z: " <<  right_foot.getPosition().z << "\n";
	skeletonFile << user.getId() << " RIGHT_HAND - x: " << right_hand.getPosition().x << " y: "<< right_hand.getPosition().y << " z: " << right_hand.getPosition().z << "\n";
	skeletonFile << user.getId() << " RIGHT_HIP - x: " <<  right_hip.getPosition().x << " y: " << right_hip.getPosition().y << " z: " <<  right_hip.getPosition().z << "\n";
	skeletonFile << user.getId() << " RIGHT_KNEE - x: "<< right_knee.getPosition().x << " y: " << right_knee.getPosition().y << " z: " << right_knee.getPosition().z << "\n";
	skeletonFile << user.getId() << " RIGHT_SHOULDER - x: " << right_shoulder.getPosition().x << " y: " << right_shoulder.getPosition().y << " z: " << right_shoulder.getPosition().z << "\n";
	skeletonFile << user.getId() << " TORSO - x: " << torso.getPosition().x << " y: " << torso.getPosition().y << " z: " << torso.getPosition().z << "\n";

	skeletonFile.close();
}


vector<string> getFilesFromFolder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}


vector<string> split(const string &s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> toks;
	while (getline(ss, item, delim)) {
		toks.push_back(item);
	}
	return toks;
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
	string infolder_name;
	string outfolder_name;
	string infile_name;
	string outfile_name;
	vector<string> files;
	vector<string> tokens;

	cout << "Enter directory of infolder (use /)\n";
	getline(cin, infolder_name);

	files = getFilesFromFolder(infolder_name);

	cout << "Enter directory of outfolder/name\n";
	getline(cin, outfolder_name);
	
	for (int i = 0; i<files.size(); ++i)
		cout << files[i] << "\n";
	
	system("pause");


	for (int i=0; i<files.size(); i++)
	{

		infile_name = infolder_name + "/" + files[i];
		cout << "infile_name: " << infile_name <<" ";
		tokens = split(files[i], '.');
		outfile_name = outfolder_name + "/" + tokens[0];
		cout << "outfile_name: " << outfile_name << "\n";

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
					/*printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), head.getPosition().x, head.getPosition().y, head.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), left_elbow.getPosition().x, left_elbow.getPosition().y, left_elbow.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), left_foot.getPosition().x, left_foot.getPosition().y, left_foot.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), left_hand.getPosition().x, left_hand.getPosition().y, left_hand.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), left_hip.getPosition().x, left_hip.getPosition().y, left_hip.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), left_knee.getPosition().x, left_knee.getPosition().y, left_knee.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), left_shoulder.getPosition().x, left_shoulder.getPosition().y, left_shoulder.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), neck.getPosition().x, neck.getPosition().y, neck.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), right_elbow.getPosition().x, right_elbow.getPosition().y, right_elbow.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), right_foot.getPosition().x, right_foot.getPosition().y, right_foot.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), right_hand.getPosition().x, right_hand.getPosition().y, right_hand.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), right_hip.getPosition().x, right_hip.getPosition().y, right_hip.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), right_knee.getPosition().x, right_knee.getPosition().y, right_knee.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), right_shoulder.getPosition().x, right_shoulder.getPosition().y, right_shoulder.getPosition().z);
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), torso.getPosition().x, torso.getPosition().y, torso.getPosition().z);
					*/
					WriteSkeletonToFile(user, outfile_name, frames);
				}

			}

		}



		printf("frames = %s\n", to_string(frames).c_str());
		

		system("pause");
	}


	nite::NiTE::shutdown();
}