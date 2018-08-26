using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OtherPlayerMovement : MonoBehaviour {

	// Use this for initialization
	void Awake () {
		trans = GetComponent<Transform>();
		anim = GetComponent<Animator>();
	}
	
	// Update is called once per frame
	void FixedUpdate () {
		Noob.PLAYER_STATE state = (Noob.PLAYER_STATE)anim.GetInteger( "State" );

		if( state == Noob.PLAYER_STATE.RUN )
		{
			Vector3 nextEstimationPos = m_estimationPos + ( m_velocity * Time.deltaTime );
			Vector3 nextPos = trans.position + ( m_velocity * Time.deltaTime );
			trans.position = Vector3.Lerp( nextPos, nextEstimationPos, moveSmoothing * Time.deltaTime );
		}
		else if( state == Noob.PLAYER_STATE.STOP )
		{
			stopTime += Time.deltaTime;
			trans.position = Vector3.Lerp( m_stopOldPos, m_estimationPos, stopSmoothing * stopTime );
		}
	}

	public void SetTransform( Noob.PlayerTransform playerTransform )
	{
		m_estimationPos = new Vector3( playerTransform.position.x, 0.0f, playerTransform.position.y );
		m_velocity.x = playerTransform.velocity.x;
		m_velocity.z = playerTransform.velocity.y;

		if( (Noob.PLAYER_STATE)anim.GetInteger( "State" ) == Noob.PLAYER_STATE.STOP )
		{
			m_stopOldPos = trans.position;
			stopTime = 0.0f;
		}
	}

	Animator anim = null;
	Transform trans = null;
	private Vector3 m_velocity = new Vector3();
	private Vector3 m_estimationPos = new Vector3();
	private readonly float moveSmoothing = 2.0f;

	private Vector3 m_stopOldPos = new Vector3();
	private float stopTime = 0.0f;
	private readonly float stopSmoothing = 10.0f;
}
