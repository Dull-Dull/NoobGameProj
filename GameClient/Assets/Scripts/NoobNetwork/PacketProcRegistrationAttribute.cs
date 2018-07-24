using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Noob
{
	class IPacketConsumer
	{
		IPacketConsumer( Type childType )
		{
			MethodInfo[] methods = childType.GetMethods();

			foreach( MethodInfo info in methods )
			{
				Object[] attrObj = info.GetCustomAttributes( typeof( PacketProcRegistrationAttribute ), false );
				if( attrObj.Length == 0 )
					continue;

				PacketProcRegistrationAttribute attr = attrObj[0] as PacketProcRegistrationAttribute;

				if( m_pckProcCon.ContainsKey( attr.PckIndex ) == false )
				{
					m_pckProcCon.Add( attr.PckIndex, (Action<Packet>)Delegate.CreateDelegate( childType, info ) );
				}
			}
		}

		void runPckProc( Packet pck )
		{
			Action<Packet> pckProc;
			if( m_pckProcCon.TryGetValue( pck.index, out pckProc ) )
			{
				pckProc( pck );
			}
		}

		private Dictionary<uint, Action<Noob.Packet>> m_pckProcCon = new Dictionary<uint, Action<Noob.Packet>>();
	}

	[AttributeUsage( AttributeTargets.Method )]
	class PacketProcRegistrationAttribute : Attribute
	{
		PacketProcRegistrationAttribute( uint pckIndex )
		{
			m_pckIndex = pckIndex;
		}

		private uint m_pckIndex;
		public uint PckIndex
		{
			get { return m_pckIndex; }
		}
	}
}
