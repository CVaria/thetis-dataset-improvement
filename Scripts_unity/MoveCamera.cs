using UnityEngine;
using System.Collections;

public class MoveCamera : MonoBehaviour {
	
	float speed = 10.0f;
	//GameObject neck, left_shoulder;
	//float x,y,z;
	//Vector3 center;

	void Update () {

		//neck = GameObject.Find ("Bip01 Neck");
		//left_shoulder = GameObject.Find ("Bip01 L UpperArm");
		//center = ((neck.transform.position - left_shoulder.transform.position)/2.0f) + neck.transform.position;
		//x = this.transform.position.x;
		//y = neck.transform.position.y;
		//z = neck.transform.position.z + 1000;
		//this.transform.position = new Vector3 (x,y,z);

		//transform.LookAt(center);

		if (Input.GetMouseButton (1)) {
			if (Input.GetAxis ("Mouse X") > 0) {
				transform.position += new Vector3 (Input.GetAxisRaw ("Mouse X") * Time.deltaTime * speed, 
				                                   0.0f, Input.GetAxisRaw ("Mouse Y") * Time.deltaTime * speed);
			}
			
			else if (Input.GetAxis ("Mouse X") < 0) {
				transform.position += new Vector3 (Input.GetAxisRaw ("Mouse X") * Time.deltaTime * speed, 
				                                   0.0f, Input.GetAxisRaw ("Mouse Y") * Time.deltaTime * speed);
			}
		}
	}
}