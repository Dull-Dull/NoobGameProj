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

	public void SetActiveHud( bool active )
	{
		m_hud.SetActive( active );
		Update();
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
	private Vector3 m_offset = new Vector3( 0.0f, 4.5f, 0.0f );
	private uint m_index = 0;
	private bool m_controled = false;
}
