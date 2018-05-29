using System;
using System.Collections.Generic;

namespace Noob
{
	public class Packet
	{
		public uint index;
	}

	public class PacketFactory
	{
		public delegate Packet CreateFunc();

		public static Packet Create( uint index )
		{
			CreateFunc func = null;
			if( PckCreateFuncCon.TryGetValue( index, out func ) )
			{
				return func();
			}

			return null;
		}

		public static void RegisterPck( uint index, Type pckType )
		{
			PckCreateFuncCon.Add( index, () =>
			{
				Object graph = Activator.CreateInstance( pckType );
				return graph as Packet;
			} );
		}

		private static Dictionary<uint, CreateFunc> PckCreateFuncCon = new Dictionary<uint, CreateFunc>();
	}
	
}
