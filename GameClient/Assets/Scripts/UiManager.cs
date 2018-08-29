using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UiManager : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void  FixedUpdate() {
		GameObject button = GameObject.Find( "NickNameField" );
		if( button != null &&
			button.GetComponent<UnityEngine.UI.InputField>().isFocused &&
			Input.GetKeyDown( KeyCode.Return ) )
		{
			OnLoginButtonClick();
		}
	}

	public void OnLoginButtonClick()
	{
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
}
