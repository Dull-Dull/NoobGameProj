using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
	public float speed = 6f;

	private void Awake()
	{
		floorMask = LayerMask.GetMask( "Floor" );
		anim = GetComponent<Animator>();
		playerRigidbody = GetComponent<Rigidbody>();

		session = GameObject.Find( "Manager" ).GetComponent<ServerSession>();
		chatCanvas = GameObject.Find( "ChatInputCanvas" ).GetComponent<Canvas>();
	}

	private void FixedUpdate()
	{
		float h = 0.0f;
		float v = 0.0f;

		if( chatCanvas.enabled == false )
		{
			h = Input.GetAxisRaw( "Horizontal" );
			v = Input.GetAxisRaw( "Vertical" );
		}

		Move( h, v );
		Turning();
		Animating( h, v );
		Reflection();
	}

	private void Move( float h, float v )
	{
		movement.Set( h, 0f, v );

		movement = movement.normalized * speed;

		playerRigidbody.MovePosition( transform.position + ( movement * Time.deltaTime ) );
	}

	private void Turning()
	{
		Ray camRay = Camera.main.ScreenPointToRay( Input.mousePosition );
		RaycastHit floorHit;
		if( Physics.Raycast ( camRay, out floorHit, camRayLength, floorMask ) )
		{
			Vector3 playerToMouse = floorHit.point - transform.position;
			playerToMouse.y = 0f;

			Quaternion newRotation = Quaternion.LookRotation( playerToMouse );
			playerRigidbody.MoveRotation( newRotation );
		}
	}

	private void Animating( float h, float v )
	{
		stateChanged = false;
		Noob.PLAYER_STATE preState = state;
		if( h != 0f || v != 0f )
			state = Noob.PLAYER_STATE.RUN;
		else
			state = Noob.PLAYER_STATE.STOP;
		anim.SetInteger( "State", (int)state );
		if( preState != state )
			stateChanged = true;
	}

	private void Reflection()
	{
		if( state == Noob.PLAYER_STATE.RUN )
			sendMoveTimeGap += Time.deltaTime;

		if( ( sendMoveTimeGap >= sendDelay )
			|| stateChanged )
		{
			sendMoveTimeGap = 0.0f;

			PlayerHud hud = GetComponent<PlayerHud>();
			Transform trans = GetComponent<Transform>();

			Noob.N_Move movePck = new Noob.N_Move();
			movePck.playerIndex = hud.index;
			movePck.transform.position.x = trans.position.x;
			movePck.transform.position.y = trans.position.z;
			movePck.transform.velocity.x = movement.x;
			movePck.transform.velocity.y = movement.z;

			movePck.animation.state = state;

			session.Send( movePck );

			return;
		}			
	}

	private ServerSession session;
	private Vector3 movement;
	private Animator anim;
	private Rigidbody playerRigidbody;
	private int floorMask;
	private float camRayLength = 100f;
	private Noob.PLAYER_STATE state = Noob.PLAYER_STATE.RUN;
	bool stateChanged = false;

	private float sendMoveTimeGap = 0.0f;
	private readonly float sendDelay = 0.1f;

	private Canvas chatCanvas = null;
}
