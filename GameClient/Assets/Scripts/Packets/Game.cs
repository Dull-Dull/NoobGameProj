using System;
using System.Collections.Generic;

namespace Noob
{

	[NoobSerializAble]
	public class N_Move : Packet
	{
		public PlayerTransform transform = new PlayerTransform();
		public PlayerAnimation animation = new PlayerAnimation();

		public override uint GetIndex(){ return index; }
		public const uint index = 101;
	}

}