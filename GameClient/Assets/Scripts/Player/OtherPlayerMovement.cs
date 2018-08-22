using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OtherPlayerMovement : MonoBehaviour {

	// Use this for initialization
	void Awake () {
		trans = GetComponent<Transform>();
	}
	
	// Update is called once per frame
	void FixedUpdate () {

		Vector3 nextEstimationPos = m_estimationPos + ( m_velocity * Time.deltaTime );
		Vector3 oldPos = trans.position + ( m_velocity * Time.deltaTime );
		trans.position = Vector3.Lerp( oldPos, nextEstimationPos, smoothing * Time.deltaTime );
	}

	public void SetTransform( Noob.PlayerTransform playerTransform )
	{
		m_estimationPos = new Vector3( playerTransform.position.x, 0.0f, playerTransform.position.y );
		m_velocity.x = playerTransform.velocity.x;
		m_velocity.z = playerTransform.velocity.y;
	}

	Transform trans = null;
	private Vector3 m_velocity = new Vector3();
	private Vector3 m_estimationPos = new Vector3();
	private readonly float smoothing = 2.0f;
}
