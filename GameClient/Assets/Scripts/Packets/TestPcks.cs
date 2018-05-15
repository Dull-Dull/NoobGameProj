using System;
using System.Collections.Generic;

namespace Noob
{

	[NoobSerializAbleAttibute]
	public class TestPck1 : Packet
	{
		public int val1;
		public int val2;
		public int val3;
		public List<int> list = new List<int>();

		public uint GetIndex(){ return 1; }
	}

	[NoobSerializAbleAttibute]
	public class TestPck2 : Packet
	{
		public int val1;

		public uint GetIndex(){ return 2; }
	}

	[NoobSerializAbleAttibute]
	public class TestData3
	{
		public int val1;
		public string val2;
	}

}