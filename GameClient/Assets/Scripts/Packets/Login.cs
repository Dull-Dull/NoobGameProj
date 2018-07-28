using System;
using System.Collections.Generic;

namespace Noob
{

	[NoobSerializAble]
	public class SC_Hello : Packet
	{
		public SC_Hello(){ index = 1; }
		public static uint GetIndex(){ return 1; }
	}

	[NoobSerializAble]
	public class CS_Hello : Packet
	{
		public CS_Hello(){ index = 2; }
		public static uint GetIndex(){ return 2; }
	}

	[NoobSerializAble]
	public class SC_Ping : Packet
	{
		public long tick = 0;

		public SC_Ping(){ index = 3; }
		public static uint GetIndex(){ return 3; }
	}

	[NoobSerializAble]
	public class CS_Ping : Packet
	{
		public long tick = 0;

		public CS_Ping(){ index = 4; }
		public static uint GetIndex(){ return 4; }
	}

}