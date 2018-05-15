using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Noob
{
	[AttributeUsage( AttributeTargets.Class )]
	public class NoobSerializAbleAttibute : Attribute
	{
		public static void Init()
		{
			Assembly asm = typeof( NoobSerializAbleAttibute ).Assembly;

			foreach( var t in asm.GetTypes() )
			{
				Object[] attrObj = t.GetCustomAttributes( typeof( NoobSerializAbleAttibute ), false );
				if( attrObj.Length == 0 ||
					attrObj == null )
					continue;

				NoobSerializeFormatter.RegisterData( t );

				Type interfaceType = t.GetInterface( "Packet" );
				if( interfaceType != null )
				{
					Object pckGraph = Activator.CreateInstance( t );
					PacketFactory.RegisterPck( (uint)t.GetMethod( "GetIndex" ).Invoke( pckGraph, null ), t );
				}
			}

			NoobSerializeFormatter.Init();
		}
	}
}
