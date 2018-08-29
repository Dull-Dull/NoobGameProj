using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Noob;

public static class PlayerManager
{
	public static void CreateOtherPlayer( SC_EnterPlayer pck )
	{
		if( m_playerResource == null )
			m_playerResource = Resources.Load( "Prefabs/Player" );

		if( m_playerPool.Count == 0 )
		{
			for( int i = 0; i < 20; ++i )
			{
				GameObject tempPlayer = Object.Instantiate( m_playerResource ) as GameObject;
				tempPlayer.AddComponent<OtherPlayerMovement>();

				tempPlayer.SetActive( false );
				tempPlayer.GetComponent<PlayerHud>().SetActiveHud( false );

				m_playerPool.Enqueue( tempPlayer );
			}
		}

		//CreateOtherPlayer
		GameObject player = m_playerPool.Dequeue();
		player.SetActive( true );

		//SetPosition
		Transform trans = player.GetComponent<Transform>();
		trans.position = new Vector3( pck.transform.position.x, 0, pck.transform.position.y );

		OtherPlayerMovement movement = player.GetComponent<OtherPlayerMovement>();
		movement.SetTransform( pck.transform );

		//SetHud
		PlayerHud hud = player.GetComponent<PlayerHud>();
		hud.nick = pck.nick;
		hud.index = pck.playerIndex;
		hud.SetActiveHud( true );

		//AddPlayerList
		m_playerList.Add( pck.playerIndex, player );
	}

	public static void DestroyOtherPlayer( uint index )
	{
		GameObject player = null;
		if( m_playerList.TryGetValue( index, out player ) == false )
			return;

		m_playerList.Remove( index );

		player.SetActive( false );
		PlayerHud hud = player.GetComponent<PlayerHud>();
		hud.SetActiveHud( false );
		m_playerList.Remove( hud.index );
		m_playerPool.Enqueue( player );
	}

	public static void CreateControlPlayer( SC_Login login )
	{
		if( m_playerResource == null )
			m_playerResource = Resources.Load( "Prefabs/Player" );

		//Create PlayerObject
		GameObject player = Object.Instantiate( m_playerResource ) as GameObject;

		//Add Extra Components
		player.AddComponent<PlayerMovement>();

		//Setting Hud
		PlayerHud playerHud = player.GetComponent<PlayerHud>();
		playerHud.nick = GameObject.Find( "LoginCanvas/NickNameField/Text" ).GetComponent<UnityEngine.UI.Text>().text;
		playerHud.index = login.playerIndex;
		playerHud.controled = true;

		//Setting SpawnPosition
		Transform pos = player.GetComponent<Transform>();;
		pos.position = new Vector3( login.spawnPosition.x, 0, login.spawnPosition.y );

		//Setting Camera
		GameObject.Find( "Main Camera" ).GetComponent<CameraFollow>().target = pos;

		m_playerList.Add( playerHud.index, player );
	}

	public static GameObject FindPlayer( uint index )
	{
		GameObject player = null;
		if( m_playerList.TryGetValue( index, out player ) )
			return player;
		else
			return null;
	}

	private static Object m_playerResource = null;
	private static Queue<GameObject> m_playerPool = new Queue<GameObject>();
	private static Dictionary<uint, GameObject> m_playerList = new Dictionary<uint, GameObject>();
}
