using System;
using System.Collections.Generic;

namespace Noob
{

	[NoobSerializAble]
	public class TestPck1 : Packet
	{
		public int val1 = 0;
		public int val2 = 0;
		public int val3 = 0;
		public List<int> list = new List<int>();

		public TestPck1(){ index = 10000; }
		public static uint GetIndex(){ return 10000; }
	}

	[NoobSerializAble]
	public class TestPck2 : Packet
	{
		public int val1 = 0;

		public TestPck2(){ index = 10001; }
		public static uint GetIndex(){ return 10001; }
	}

	[NoobSerializAble]
	public class TestData3
	{
		public int val1 = 0;
		public string val2 = "";
	}

}