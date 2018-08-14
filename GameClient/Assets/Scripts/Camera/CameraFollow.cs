using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour {

	private void Awake()
	{
		if( target != null )
			offset = transform.position - target.position;
	}

	private void FixedUpdate()
	{
		if( target != null )
		{
			Vector3 targetCamPos = target.position + offset;
			transform.position = Vector3.Lerp( transform.position, targetCamPos, smoothing * Time.deltaTime );
		}
	}

	public Transform target;
	public float smoothing = 5f;
	private Vector3 offset = new Vector3( 0.0f, 15.0f, -24.0f );
}
