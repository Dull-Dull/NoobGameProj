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
		Vector3 pos = trans.position;
		if( m_velocity.x >= 0.1f )
		{
			Debug.Log( trans.position.ToString( "F5" ) );
			Debug.Log( ( m_velocity * Time.deltaTime ).ToString( "F5" ) );
		}
		trans.position = pos + ( m_velocity * Time.deltaTime );
		if( m_velocity.x >= 0.1f )
		{
			Debug.Log( trans.position.ToString("F5") );
		}
			
	}

	public void SetTransform( Noob.PlayerTransform playerTransform )
	{
		trans.position = new Vector3( playerTransform.position.x, 0.0f, playerTransform.position.y );
		m_velocity.x = playerTransform.velocity.x;
		m_velocity.z = playerTransform.velocity.y;
	}

	Transform trans = null;
	private Vector3 m_velocity = new Vector3();
}
