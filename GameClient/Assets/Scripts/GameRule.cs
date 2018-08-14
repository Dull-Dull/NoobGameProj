using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameRule : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public void OnLoginButtonClick()
	{
		Debug.Log( "Button Clicked!!" );

		GameObject nick = GameObject.Find( "NickNameField/Text" );
		var nickField = nick.GetComponent<UnityEngine.UI.Text>();
		if( nickField.text == "" )
			return;

		GameObject button = GameObject.Find( "LoginButton" );
		button.GetComponent<UnityEngine.UI.Button>().interactable = false;

		GameObject manager = GameObject.Find( "Manager" );
		var session = manager.GetComponent<ServerSession>();

		Noob.CS_Login login = new Noob.CS_Login();
		login.nick = nickField.text;

		session.Send( login );
	}

	public List<Vector2> m_spawnSpot = new List<Vector2>();
}
