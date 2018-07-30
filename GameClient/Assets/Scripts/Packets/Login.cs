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
		public string Nick = "";

		public override uint GetIndex(){ return index; }
		public const uint index = 3;
	}

	[NoobSerializAble]
	public class SC_Login : Packet
	{
		public uint PlayerIndex = 0;
		public Vector2D SpawnPosition = new Vector2D();

		public override uint GetIndex(){ return index; }
		public const uint index = 4;
	}

	[NoobSerializAble]
	public class SC_Ping : Packet
	{
		public long Tick = 0;

		public override uint GetIndex(){ return index; }
		public const uint index = 5;
	}

	[NoobSerializAble]
	public class CS_Ping : Packet
	{
		public long Tick = 0;

		public override uint GetIndex(){ return index; }
		public const uint index = 6;
	}

}