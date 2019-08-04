using UnityEngine;
using System.Collections;

public class JointPositionController : MonoBehaviour {
	
	int myframe;
	float x, y, z;
	// Use this for initialization
	void Start () {
		Debug.Log (this.gameObject.name);
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 newPosition;
		//print ("frameID " + OniFileReader.frameIndex);
		myframe = OniFileReader.frameIndex % OniFileReader.FrameList.Count;
		x = OniFileReader.FrameList [myframe] [this.gameObject.name].x; 
		y = OniFileReader.FrameList [myframe] [this.gameObject.name].y; 
		z = OniFileReader.FrameList [myframe] [this.gameObject.name].z; 
		print ("frameID " + OniFileReader.frameIndex+" "+this.gameObject.name+": "+"X=" + x + " Y=" + y + " Z=" + z);
		newPosition = new Vector3(x,y,z);
		transform.position = newPosition;
	}
}

