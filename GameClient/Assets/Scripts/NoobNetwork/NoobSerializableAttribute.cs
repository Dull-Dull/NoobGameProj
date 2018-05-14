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
		static void Init()
		{
			Assembly asm = typeof( NoobSerializAbleAttibute ).Assembly;

			foreach( var t in asm.GetTypes() )
			{
				Object[] attrObj = t.GetCustomAttributes( typeof( NoobSerializAbleAttibute ), false );
				if( attrObj == null )
					continue;

				NoobSerializeFormatter.RegisterData( t );

				Type parentType = t.BaseType;
				while( parentType != null )
				{
					if( parentType == typeof( Packet ) )
					{
						PacketFactory.RegisterPck( (uint)t.GetMethod( "GetIndex" ).Invoke( null, null ), t );
					}
						
				}
			}
		}
	}
}
