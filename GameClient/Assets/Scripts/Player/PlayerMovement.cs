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
		PLAYER_STATE preState = state;
		if( h != 0f || v != 0f )
			state = PLAYER_STATE.RUN;
		else
			state = PLAYER_STATE.STOP;
		anim.SetInteger( "State", (int)state );
		if( preState != state )
			stateChanged = true;
	}

	private void Reflection()
	{
		if( state == PLAYER_STATE.RUN )
			sendMoveTimeGap += Time.deltaTime;

		PlayerHud hud = GetComponent<PlayerHud>();

		if( ( sendMoveTimeGap >= sendDelay )
			|| stateChanged )
		{
			sendMoveTimeGap = 0.0f;

			N_Move movePck = new N_Move();
			movePck.playerIndex = hud.index;
			movePck.transform.position.x = transform.position.x;
			movePck.transform.position.y = transform.position.z;
			movePck.transform.velocity.x = movement.x;
			movePck.transform.velocity.y = movement.z;

			movePck.animation.state = state;

			session.Send( movePck );
		}

		bool rolling = Mathf.Abs( transform.rotation.eulerAngles.y - preDegree ) > 3.0f;
		sendRollTimeGap += Time.deltaTime;

		if( ( rolling != preRolling ) ||
			( rolling && ( sendRollTimeGap >= sendDelay ) ) )
		{
			N_Roll rollPck = new N_Roll();
			rollPck.playerIndex = hud.index;
			rollPck.degree = transform.rotation.eulerAngles.y;						
			session.Send( rollPck );
			
			preDegree = transform.rotation.eulerAngles.y;
			sendRollTimeGap = 0.0f;
		}

		preRolling = rolling;
	}

	private ServerSession session;
	private Vector3 movement;
	private Animator anim;
	private Rigidbody playerRigidbody;
	private int floorMask;
	private float camRayLength = 100f;
	private PLAYER_STATE state = PLAYER_STATE.RUN;
	private bool stateChanged = false;

	private float preDegree = 0.0f;
	private bool preRolling = false;

	private float sendMoveTimeGap = 0.1f;
	private float sendRollTimeGap = 0.1f;
	private readonly float sendDelay = 0.1f;

	private Canvas chatCanvas = null;
}
