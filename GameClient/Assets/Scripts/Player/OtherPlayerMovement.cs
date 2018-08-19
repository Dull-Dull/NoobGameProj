using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OtherPlayerMovement : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public Vector3 velocity
	{
		get { return m_velocity; }
		set { m_velocity = value; }
	}

	private Vector3 m_velocity = new Vector3();
}
