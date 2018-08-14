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
		//Debug.Log( "Call SC_Hello pck!!!" );

		GameObject loginCanvasObj = GameObject.Find( "LoginCanvas" );
		Canvas loginCanvas = loginCanvasObj.GetComponent<Canvas>();
		loginCanvas.enabled = true;

		//CS_Login login = new CS_Login();
		//login.nick = "Unknown";

		//session.Send( login );
	}

	[PacketProcRegistration( SC_Login.index )]
	public void SC_LoginProc( Packet pck )
	{
		Debug.Log( "Call SC_Login pck!!!" );

		var loginCanvasObj = GameObject.Find( "LoginCanvas" );
		loginCanvasObj.GetComponent<Canvas>().enabled = false;

		SC_Login login = pck as SC_Login;

		Debug.Log( "Spawn Position : " + login.spawnPosition );

		var rsc = Resources.Load( "Prefabs/Player" );
		GameObject player = Instantiate( rsc ) as GameObject;
		var playerHudComponent = player.GetComponent<PlayerHud>();
		playerHudComponent.nick = GameObject.Find( "LoginCanvas/NickNameField/Text" ).GetComponent<UnityEngine.UI.Text>().text;
		Transform pos = player.GetComponent<Transform>();
		Vector2 spawnPos = GameObject.Find( "Manager" ).GetComponent<GameRule>().m_spawnSpot[login.spawnPosition];
		pos.position = new Vector3( spawnPos.x, 0, spawnPos.y );

		player.AddComponent<PlayerMovement>();
		player.AddComponent<Rigidbody>();

		GameObject.Find( "Main Camera" ).GetComponent<CameraFollow>().target = pos;
	}

	[PacketProcRegistration( SC_Ping.index )]
	public void SC_PingProc( Packet pck )
	{
		Debug.Log( "Recv SC_Ping pck!!!" );
		CS_Ping ping = new CS_Ping();
		ping.tick = ( pck as SC_Ping ).tick;
		session.Send( ping );
	}
}
