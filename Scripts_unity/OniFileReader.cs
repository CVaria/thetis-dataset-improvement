using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using System.IO;

public class OniFileReader : MonoBehaviour {
	
	//public static List< List <Vector3> > FrameList;
	//List <Vector3> Frame;
	public static Dictionary<int, Dictionary<string, Vector3>> FrameList;
	Dictionary <string, Vector3> Frame;
	public static int frameIndex;
	List<string> Joints;
	// Use this for initialization
	void Start () {
		
		//FrameList = new List<List<Vector3>> ();
		FrameList = new Dictionary<int, Dictionary<string, Vector3>>();
		Joints = new List<string> ();
		Frame = new Dictionary<string, Vector3>();
		frameIndex = 0;
		
		//**************************************************************
		Joints.Add ("Bip01 Head");
		Joints.Add ("Bip01 L Forearm");
		Joints.Add ("Bip01 L Foot");
		Joints.Add ("Bip01 L Hand");
		Joints.Add ("Bip01 L Thigh");
		Joints.Add ("Bip01 L Calf");
		Joints.Add ("Bip01 L UpperArm");
		Joints.Add ("Bip01 Neck");
		Joints.Add ("Bip01 R Forearm");
		Joints.Add ("Bip01 R Foot");
		Joints.Add ("Bip01 R Hand");
		Joints.Add ("Bip01 R Thigh");
		Joints.Add ("Bip01 R Calf");
		Joints.Add ("Bip01 R UpperArm");
		Joints.Add ("Bip01 Spine1");
		//**************************************************************
		
		
		FileInfo theSourceFile = new FileInfo ("C:/Users/Eotw/Desktop/results/normal_oniFiles/ONI_AMATEURS/backhand/p1.txt");
		StreamReader reader = theSourceFile.OpenText();
		Debug.Log ("Opened, Reading starts\n");
		
		string text;
		int frameId;
		
		
		text = reader.ReadLine();
		while(text!=null)
		{
			string[] fr_arr = text.Split(' ');
			if(fr_arr.Length >= 2)
			{
				frameId = int.Parse(fr_arr[1]);
				//Debug.Log (frameIndex);
				
				for(int i=0; i<15; i++)
				{
					text = reader.ReadLine();
					string[] j_arr = text.Split(' ');
					//Frame.Add(new Vector3(float.Parse(j_arr[0]),float.Parse(j_arr[1]),float.Parse(j_arr[2]) ));
					Frame.Add(Joints[i], new Vector3(float.Parse(j_arr[0]),float.Parse(j_arr[1]),float.Parse(j_arr[2]) ));
				}
				
				FrameList.Add(frameId, new Dictionary<string, Vector3>(Frame));
			}	
			
			Frame.Clear();
			
			//print (Frame[1]);
			text = reader.ReadLine();
			//Console.WriteLine(text);
			//print (text);
		} 
		
		print ("NOW FRAMELIST HAS:\n");
		
		for (int k=0; k< FrameList.Count; k++)
		{
			print("Frame : " + k);
			for(int i=0; i<15; i++)
			{
				print (FrameList[k][Joints[i]].x +" "+ FrameList[k][Joints[i]].y +" " + FrameList[k][Joints[i]].z ); 
			}
		}
		
		
	}
	
	// Update is called once per frame
	void LateUpdate () {
		frameIndex++;
	}
}

