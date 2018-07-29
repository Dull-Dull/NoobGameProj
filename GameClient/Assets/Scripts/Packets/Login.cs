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
	public class SC_Ping : Packet
	{
		public long tick = 0;

		public override uint GetIndex(){ return index; }
		public const uint index = 3;
	}

	[NoobSerializAble]
	public class CS_Ping : Packet
	{
		public long tick = 0;

		public override uint GetIndex(){ return index; }
		public const uint index = 4;
	}

}