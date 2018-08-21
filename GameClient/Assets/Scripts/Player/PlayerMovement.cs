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
	}

	private void FixedUpdate()
	{
		float h = Input.GetAxisRaw( "Horizontal" );
		float v = Input.GetAxisRaw( "Vertical" );

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
		bool preState = walking;
		walking = h != 0f || v != 0f;
		anim.SetBool( "IsWalking", walking );
		if( preState != walking )
			stateChanged = true;
	}

	private void Reflection()
	{
		if( walking )
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
	bool walking = false;
	bool stateChanged = false;

	private float sendMoveTimeGap = 0.0f;
	private readonly float sendDelay = 0.2f;
}
