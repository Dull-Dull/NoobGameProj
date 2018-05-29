using System;
using System.Collections.Generic;

namespace Noob
{

	[NoobSerializAbleAttibute]
	public class SC_Hello : Packet
	{
		public SC_Hello(){ index = 1; }
		public static uint GetIndex(){ return 1; }
	}

	[NoobSerializAbleAttibute]
	public class CS_Hello : Packet
	{
		public CS_Hello(){ index = 2; }
		public static uint GetIndex(){ return 2; }
	}

}