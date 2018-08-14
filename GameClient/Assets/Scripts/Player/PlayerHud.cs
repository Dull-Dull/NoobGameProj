using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHud : MonoBehaviour {

	// Use this for initialization
	void Awake () {
		m_hud = Instantiate( Resources.Load( "Prefabs/PlayerHud" ) ) as GameObject;
	}
	
	// Update is called once per frame
	void Update () {
		Transform playerPos = GetComponent<Transform>();
		Transform hudPos = m_hud.GetComponent<Transform>();

		hudPos.position = playerPos.position + m_offset;
	}

	public string nick
	{
		get
		{
			return m_hud.GetComponent<Transform>().Find( "NickText" ).GetComponent<UnityEngine.UI.Text>().text;
		}

		set
		{
			m_hud.GetComponent<Transform>().Find( "NickText" ).GetComponent<UnityEngine.UI.Text>().text = value;
		}
	}

	private GameObject m_hud = null;
	private Vector3 m_offset = new Vector3( 0.0f, 4.5f, 0.0f );
}
