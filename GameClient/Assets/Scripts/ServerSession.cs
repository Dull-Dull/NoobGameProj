using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using UnityEngine;
using Noob;

public class ServerSession : MonoBehaviour {

	void Awake()
	{
		NoobSerializAbleAttribute.Init();

		session.m_OnConnect += ( SocketError err ) =>
		{
			if( err == SocketError.Success )
			{
				Debug.Log( "Connect Success!!!" );
				CS_Hello hello = new CS_Hello();
				session.Send( hello );
			}
			else
				Debug.Log( "Connect Fail!!!" );
		};

		session.m_OnDisConnect += () =>
		{
			Debug.Log( "Disconnected!!!" );
		};

		session.AsyncConnect( "127.0.0.1", 15000 );

		pckProcMng = new PacketProcManager( this );
	}

	// Use this for initialization
	void Start() {
		Debug.Log( "Start()" );

		//StartCoroutine( CloseSession() );
	}

	IEnumerator CloseSession()
	{
		yield return new WaitForSeconds( 3 );

		session.Close();
		Debug.Log( "Close()" );
	}
	
	// Update is called once per frame
	void Update () {
		if( session.IsConnected )
		{
			for( Packet pck = session.TryPopPacket(); pck != null; pck = session.TryPopPacket() )
			{
				pckProcMng.runPckProc( pck );
			}
		}
	}

	private void OnDestroy()
	{
		if( session.IsConnected )
			session.Close();
	}

	private TcpSession session = new TcpSession();
	private PacketProcManager pckProcMng = null;

	[PacketProcRegistration( 1 )]
	public void SC_HelloProc( Packet pck )
	{
		Debug.Log( "Call SC_Hello pck!!!" );
	}

	[PacketProcRegistration( 3 )]
	public void SC_PingProc( Packet pck )
	{
		Debug.Log( "Recv SC_Ping pck!!!" );
		CS_Ping ping = new CS_Ping();
		ping.tick = ( pck as SC_Ping ).tick;
		session.Send( ping );
	}
}
