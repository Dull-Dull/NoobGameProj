using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OtherPlayerMovement : MonoBehaviour {

	// Use this for initialization
	void Awake ()
	{
		trans = GetComponent<Transform>();
		anim = GetComponent<Animator>();
	}
	
	// Update is called once per frame
	void FixedUpdate ()
	{
		Noob.PLAYER_STATE state = (Noob.PLAYER_STATE)anim.GetInteger( "State" );

		if( state == Noob.PLAYER_STATE.RUN )
		{
			Vector3 nextEstimationPos = m_estimationPos + ( m_velocity * Time.deltaTime );
			Vector3 nextPos = trans.position + ( m_velocity * Time.deltaTime );
			trans.position = Vector3.Lerp( nextPos, nextEstimationPos, moveSmoothing * Time.deltaTime );
		}
		else if( state == Noob.PLAYER_STATE.STOP )
		{
			stopMoveTime += Time.deltaTime;
			trans.position = Vector3.Lerp( m_stopOldPos, m_estimationPos, stopSmoothing * stopMoveTime );
		}

	}

	void Update()
	{
		if( Mathf.Abs( m_estimationDegree - m_oldDegree ) > 180.0f )
			Debug.Log( "from : " + m_oldDegree + "\tto : " + m_estimationDegree );
		stopRollTime += Time.deltaTime;
		float degree = Mathf.Lerp( m_oldDegree, m_estimationDegree, 10.0f * stopRollTime );
		trans.rotation = Quaternion.Euler( trans.rotation.eulerAngles.x, degree, trans.rotation.eulerAngles.z );
	}

	public void SetTransform( Noob.PlayerTransform playerTransform )
	{
		m_estimationPos = new Vector3( playerTransform.position.x, 0.0f, playerTransform.position.y );
		m_velocity.x = playerTransform.velocity.x;
		m_velocity.z = playerTransform.velocity.y;

		if( (Noob.PLAYER_STATE)anim.GetInteger( "State" ) == Noob.PLAYER_STATE.STOP )
		{
			m_stopOldPos = trans.position;
			stopMoveTime = 0.0f;
		}
	}

	public void SetDirection( float degree )
	{
		m_estimationDegree = degree;
		m_oldDegree = trans.rotation.eulerAngles.y;

		float degreeDiff = m_estimationDegree - m_oldDegree;
		float velocity = 0.0f;
		if( degreeDiff > 180.0f )
			velocity = degreeDiff - 360.0f;
		else if( degreeDiff < -180.0f )
			velocity = degreeDiff + 360.0f;
		else
			velocity = degreeDiff;

		if( velocity < 0.0f && m_estimationDegree > m_oldDegree )
			m_estimationDegree -= 360.0f;
		else if( velocity > 0.0f && m_estimationDegree < m_oldDegree )
			m_estimationDegree += 360.0f;

		stopRollTime = 0.0f;
	}

	Animator anim = null;
	Transform trans = null;
	private Vector3 m_velocity = new Vector3();
	private Vector3 m_estimationPos = new Vector3();
	private readonly float moveSmoothing = 2.0f;

	private Vector3 m_stopOldPos = new Vector3();
	private float stopMoveTime = 0.0f;
	private readonly float stopSmoothing = 10.0f;

	private float m_oldDegree = 0.0f;
	private float m_estimationDegree = 0.0f;
	private float stopRollTime = 0.0f;
}
