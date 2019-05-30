using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using UnityEngine;
using Noob;

public class ServerSession : MonoBehaviour {

	public string Ip = "";

	void Awake()
	{
		
		NoobSerializAbleAttribute.Init();

		session.m_OnConnect += ( SocketError err ) =>
		{
			if( err == SocketError.Success )
			{
				CS_Hello hello = new CS_Hello();
				session.Send( hello );
			}
			else
			{
				connectionError = true;
			}
		};

		session.m_OnDisConnect += () =>
		{
			connectionError = true;
		};

		session.AsyncConnect( Ip, 15000 );

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

		if( connectionError )
		{
			Canvas connecErrorCanvas = GameObject.Find( "ConnectErrorCanvas" ).GetComponent<Canvas>();
			connecErrorCanvas.enabled = true;
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
	private bool connectionError = false;

	[PacketProcRegistration( SC_Hello.index )]
	public void SC_HelloProc( Packet pck )
	{
		GameObject loginCanvasObj = GameObject.Find( "LoginCanvas" );
		Canvas loginCanvas = loginCanvasObj.GetComponent<Canvas>();
		loginCanvas.enabled = true;

		GameObject nickFieldObj = GameObject.Find( "LoginCanvas/NickNameField" );
		UnityEngine.UI.InputField nickField = nickFieldObj.GetComponent<UnityEngine.UI.InputField>();
		nickField.Select();
	}

	[PacketProcRegistration( SC_Login.index )]
	public void SC_LoginProc( Packet pck )
	{
		SC_Login login = pck as SC_Login;

		PlayerManager.CreateControlPlayer( login );

		GameObject loginCanvasObj = GameObject.Find( "LoginCanvas" );
		Destroy( loginCanvasObj );

		ChatInputHud chatInputHud = GameObject.Find( "ChatInputCanvas/ChatInputField" ).GetComponent<ChatInputHud>();
		chatInputHud.PlayerIndex = login.playerIndex;
	}

	[PacketProcRegistration( Noob.Ping.index )]
	public void SC_PingProc( Packet pck )
	{
		session.Send( pck );
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

	[PacketProcRegistration( N_Move.index )]
	public void N_MoveProc( Packet pck )
	{
		N_Move movePck = pck as N_Move;
		GameObject player = PlayerManager.FindPlayer( movePck.playerIndex );
		if( player == null )
			return;

		Animator anim = player.GetComponent<Animator>();
		anim.SetInteger( "State", (int)movePck.animation.state );

		OtherPlayerMovement movement = player.GetComponent<OtherPlayerMovement>();
		movement.SetTransform( movePck.transform );
	}

	[PacketProcRegistration( N_Roll.index )]
	public void N_RollProc( Packet pck )
	{
		N_Roll rollPck = pck as N_Roll;
		GameObject player = PlayerManager.FindPlayer( rollPck.playerIndex );
		if( player == null )
			return;

		OtherPlayerMovement movement = player.GetComponent<OtherPlayerMovement>();
		movement.SetDirection( rollPck.degree );
	}

	[PacketProcRegistration( N_Chat.index )]
	public void N_ChatProc( Packet pck )
	{
		N_Chat chatPck = pck as N_Chat;
		GameObject player = PlayerManager.FindPlayer( chatPck.playerIndex );

		if( player == null )
			return;

		PlayerHud hud = player.GetComponent<PlayerHud>();
		hud.InsertChatMessage( chatPck.message );
	}
}
