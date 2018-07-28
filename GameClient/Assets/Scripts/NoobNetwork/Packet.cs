using System;
using System.Collections.Generic;
using System.Reflection;

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

	[AttributeUsage( AttributeTargets.Method )]
	class PacketProcRegistrationAttribute : Attribute
	{
		public PacketProcRegistrationAttribute( uint pckIndex )
		{
			m_pckIndex = pckIndex;
		}

		private uint m_pckIndex;
		public uint PckIndex
		{
			get { return m_pckIndex; }
		}
	}

	class PacketProcManager
	{
		public PacketProcManager( Object consumer )
		{
			Type consumerType = consumer.GetType();

			MethodInfo[] methods = consumerType.GetMethods();

			foreach( MethodInfo info in methods )
			{
				Object[] attrObj = info.GetCustomAttributes( typeof( PacketProcRegistrationAttribute ), false );
				if( attrObj.Length == 0 )
					continue;

				PacketProcRegistrationAttribute attr = attrObj[0] as PacketProcRegistrationAttribute;

				if( m_pckProcCon.ContainsKey( attr.PckIndex ) == false )
				{
					var del = (Action<Packet>)Delegate.CreateDelegate( typeof( Action<Packet> ), consumer, info );
					m_pckProcCon.Add( attr.PckIndex, del );
				}
			}
		}

		public void runPckProc( Packet pck )
		{
			Action<Packet> pckProc;
			if( m_pckProcCon.TryGetValue( pck.index, out pckProc ) )
			{
				pckProc( pck );
			}
		}

		private Dictionary<uint, Action<Noob.Packet>> m_pckProcCon = new Dictionary<uint, Action<Noob.Packet>>();
	}
}
