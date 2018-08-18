using System;
using System.Collections.Generic;

namespace Noob
{

	[NoobSerializAble]
	public enum PLAYER_STATE : uint
	{
		STOP,
		RUN,
		__MAX__
	}

	[NoobSerializAble]
	public class PlayerTransform
	{
		public Vector2D position = new Vector2D();
		public Vector2D velocity = new Vector2D();
	}

	[NoobSerializAble]
	public class PlayerDirection
	{
		public Vector2D direction = new Vector2D();
		public float angularVelocity = new float();
	}

	[NoobSerializAble]
	public class PlayerAnimation
	{
		public PLAYER_STATE state = new PLAYER_STATE();
	}

}