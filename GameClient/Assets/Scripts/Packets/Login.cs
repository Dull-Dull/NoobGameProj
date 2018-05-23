using System;
using System.Collections.Generic;

namespace Noob
{

	[NoobSerializAbleAttibute]
	public class SC_Hello : Packet
	{

		public uint GetIndex(){ return 1; }
	}

	[NoobSerializAbleAttibute]
	public class CS_Hello : Packet
	{

		public uint GetIndex(){ return 2; }
	}

}