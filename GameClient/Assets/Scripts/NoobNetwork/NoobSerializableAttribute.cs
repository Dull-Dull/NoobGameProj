using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Noob
{
	[AttributeUsage( AttributeTargets.Class )]
	public class NoobSerializAbleAttribute : Attribute
	{
		public static void Init()
		{
			Assembly asm = typeof( NoobSerializAbleAttribute ).Assembly;

			foreach( var t in asm.GetTypes() )
			{
				Object[] attrObj = t.GetCustomAttributes( typeof( NoobSerializAbleAttribute ), false );
				if( attrObj.Length == 0 ||
					attrObj == null )
					continue;

				NoobSerializeFormatter.RegisterData( t );
				
				if( t.BaseType == typeof( Noob.Packet ) )
				{
					PacketFactory.RegisterPck( (uint)t.GetMethod( "GetIndex" ).Invoke( null, null ), t );
				}
			}

			NoobSerializeFormatter.Init();
		}
	}
}
