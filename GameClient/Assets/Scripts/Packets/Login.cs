using System;
using System.Collections.Generic;

namespace Noob
{

	[NoobSerializAble]
	public class SC_Hello : Packet
	{
		public override uint GetIndex(){ return index; }
		public const uint index = 1;
	}

	[NoobSerializAble]
	public class CS_Hello : Packet
	{
		public override uint GetIndex(){ return index; }
		public const uint index = 2;
	}

	[NoobSerializAble]
	public class CS_Login : Packet
	{
		public string nick = "";

		public override uint GetIndex(){ return index; }
		public const uint index = 3;
	}

	[NoobSerializAble]
	public class SC_Login : Packet
	{
		public uint playerIndex = 0;
		public Vector2D spawnPosition = new Vector2D();

		public override uint GetIndex(){ return index; }
		public const uint index = 4;
	}

	[NoobSerializAble]
	public class SC_EnterPlayer : Packet
	{
		public uint playerIndex = 0;
		public string nick = "";
		public PlayerTransform transform = new PlayerTransform();
		public PlayerDirection direction = new PlayerDirection();
		public PlayerAnimation animation = new PlayerAnimation();

		public override uint GetIndex(){ return index; }
		public const uint index = 5;
	}

	[NoobSerializAble]
	public class SC_ExitPlayer : Packet
	{
		public uint playerIndex = 0;

		public override uint GetIndex(){ return index; }
		public const uint index = 6;
	}

	[NoobSerializAble]
	public class SC_Ping : Packet
	{
		public long tick = 0;

		public override uint GetIndex(){ return index; }
		public const uint index = 7;
	}

	[NoobSerializAble]
	public class CS_Ping : Packet
	{
		public long tick = 0;

		public override uint GetIndex(){ return index; }
		public const uint index = 8;
	}

}