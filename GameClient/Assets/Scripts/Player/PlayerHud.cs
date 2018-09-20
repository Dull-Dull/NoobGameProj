using System.Collections;
using System.Collections.Generic;
using UnityEngine;

class ChatMessage
{
	public string message;
	public float recvTime;
}

public class PlayerHud : MonoBehaviour {

	// Use this for initialization
	void Awake () {
		m_hud = Instantiate( Resources.Load( "Prefabs/PlayerHud" ) ) as GameObject;
		m_chatText = m_hud.GetComponent<Transform>().Find( "ChatText" ).GetComponent<UnityEngine.UI.Text>();
	}
	
	// Update is called once per frame
	void Update () {
		Transform playerPos = GetComponent<Transform>();
		Transform hudPos = m_hud.GetComponent<Transform>();

		hudPos.position = playerPos.position + m_offset;
		checkChatExpire();		
	}

	public void SetActiveHud( bool active )
	{
		m_hud.SetActive( active );
		Update();
	}

	public void InsertChatMessage( string message )
	{
		ChatMessage chatMessage = new ChatMessage();
		chatMessage.message = message;
		chatMessage.recvTime = Time.time;

		m_chatList.Add( chatMessage );
		drawChatMessage();
	}

	private void checkChatExpire()
	{
		if( m_chatList.Count != 0 )
		{
			if( ( Time.time - m_chatList[0].recvTime ) > m_chatMessageAliveTime )
			{
				m_chatList.RemoveAt( 0 );
				drawChatMessage();
			}
		}
	}

	private void drawChatMessage()
	{
		System.Text.StringBuilder builder = new System.Text.StringBuilder(256,1024);

		foreach( var chat in m_chatList )
			builder.AppendLine( chat.message );

		if( builder.Length != 0 )
			builder.Remove( builder.Length - 1, 1 );

		m_chatText.text = builder.ToString();
	}

	public string nick
	{
		get{ return m_hud.GetComponent<Transform>().Find( "NickText" ).GetComponent<UnityEngine.UI.Text>().text; }
		set{ m_hud.GetComponent<Transform>().Find( "NickText" ).GetComponent<UnityEngine.UI.Text>().text = value; }
	}

	public uint index
	{
		get { return m_index; }
		set { m_index = value; }
	}

	public bool controled
	{
		get { return m_controled; }
		set { m_controled = value; }
	}

	private GameObject m_hud = null;
	private UnityEngine.UI.Text m_chatText = null;
	private Vector3 m_offset = new Vector3( 0.0f, 4.5f, 0.0f );
	private uint m_index = 0;
	private bool m_controled = false;

	private List<ChatMessage> m_chatList = new List<ChatMessage>();
	private readonly float m_chatMessageAliveTime = 5.0f;
}
