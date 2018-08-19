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

	public void Send( Packet pck )
	{
		session.Send( pck );
	}

	private TcpSession session = new TcpSession();
	private PacketProcManager pckProcMng = null;

	[PacketProcRegistration( SC_Hello.index )]
	public void SC_HelloProc( Packet pck )
	{
		GameObject loginCanvasObj = GameObject.Find( "LoginCanvas" );
		Canvas loginCanvas = loginCanvasObj.GetComponent<Canvas>();
		loginCanvas.enabled = true;
	}

	[PacketProcRegistration( SC_Login.index )]
	public void SC_LoginProc( Packet pck )
	{
		Debug.Log( "Call SC_Login pck!!!" );

		SC_Login login = pck as SC_Login;

		PlayerManager.CreateControlPlayer( login );

		GameObject loginCanvasObj = GameObject.Find( "LoginCanvas" );
		Destroy( loginCanvasObj );
	}

	[PacketProcRegistration( SC_Ping.index )]
	public void SC_PingProc( Packet pck )
	{
		Debug.Log( "Recv SC_Ping pck!!!" );
		CS_Ping ping = new CS_Ping();
		ping.tick = ( pck as SC_Ping ).tick;
		session.Send( ping );
	}

	[PacketProcRegistration( SC_EnterPlayer.index )]
	public void SC_NewPlayerProc( Packet pck )
	{
		PlayerManager.CreateOtherPlayer( pck as SC_EnterPlayer );
	}

	[PacketProcRegistration( SC_ExitPlayer.index )]
	public void SC_ExitPlayerProc( Packet pck )
	{
		PlayerManager.DestroyOtherPlayer( ( pck as SC_ExitPlayer ).playerIndex );
	}
}
