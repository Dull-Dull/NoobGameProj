using System;
using System.Collections.Generic;

namespace Noob
{

	[NoobSerializAble]
	public class N_Move : Packet
	{
		public uint playerIndex = 0;
		public PlayerTransform transform = new PlayerTransform();
		public PlayerAnimation animation = new PlayerAnimation();

		public override uint GetIndex(){ return index; }
		public const uint index = 101;
	}

	[NoobSerializAble]
	public class N_Chat : Packet
	{
		public uint playerIndex = 0;
		public string message = "";

		public override uint GetIndex(){ return index; }
		public const uint index = 102;
	}

}