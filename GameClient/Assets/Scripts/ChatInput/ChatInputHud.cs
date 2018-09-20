using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChatInputHud : MonoBehaviour {

	// Use this for initialization
	void Start () {
		GameObject chatInputCanvas = GameObject.Find( "ChatInputCanvas" );
		m_chatInputCanvas = chatInputCanvas.GetComponent<UnityEngine.Canvas>();

		GameObject chatInputField = GameObject.Find( "ChatInputCanvas/ChatInputField" );
		m_chatInputField = chatInputField.GetComponent<UnityEngine.UI.InputField>();

		m_session = GameObject.Find( "Manager" ).GetComponent<ServerSession>();
	}
	
	// Update is called once per frame
	void Update () {
		if( Input.GetKeyDown( KeyCode.Return ) )
		{
			GameObject loginCanvas = GameObject.Find( "LoginCanvas" );
			if( loginCanvas != null )
				return;

			if( m_chatInputCanvas.enabled )
			{
				if( m_chatInputField.text.Length != 0 )
				{
					Noob.N_Chat chat = new Noob.N_Chat();
					chat.playerIndex = m_playerIndex;
					chat.message = m_chatInputField.text;
					m_chatInputField.text = "";

					m_session.Send( chat );
				}

				m_chatInputCanvas.enabled = false;
			}
			else
			{
				m_chatInputCanvas.enabled = true;
				m_chatInputField.Select();
			}
		}
	}

	public uint PlayerIndex
	{
		set { m_playerIndex = value; }
	}

	UnityEngine.Canvas m_chatInputCanvas = null;
	UnityEngine.UI.InputField m_chatInputField = null;
	ServerSession m_session = null;

	uint m_playerIndex = 0;
}
