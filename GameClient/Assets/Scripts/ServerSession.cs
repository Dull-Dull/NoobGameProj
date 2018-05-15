using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using UnityEngine;
using Noob;

public class ServerSession : MonoBehaviour {

	void Awake()
	{
		NoobSerializAbleAttibute.Init();

		session.m_OnConnect += ( SocketError err ) =>
		{
			if( err == SocketError.Success )
				Debug.Log( "Connect Success!!!" );
			else
				Debug.Log( "Connect Fail!!!" );
		};

		session.m_OnDisConnect += () =>
		{
			Debug.Log( "Disconnected!!!" );
		};

		session.AsyncConnect( "127.0.0.1", 15000 );
		
	}

	// Use this for initialization
	void Start() {
		Debug.Log( "Start()" );

		StartCoroutine( CloseSession() );
	}

	IEnumerator CloseSession()
	{
		yield return new WaitForSeconds( 3 );

		session.Close();
		Debug.Log( "Close()" );
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	private void OnDestroy()
	{
		session.Close();
	}



	private TcpSession session = new TcpSession();
}
