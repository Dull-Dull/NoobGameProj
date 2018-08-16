using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace CodeGenerator.FileParser
{
	partial class FileParser
	{
		private void ParseEnum( XmlNode node )
		{
			string name = null;

			name = GetAttrValue( node, "name" );

			if( name == null )
				throw new Exception.AttributeNotFoundException( "Enum/name" );

			List<Value> valueList = new List<Value>();
			XmlNodeList elements = node.ChildNodes;

			if( elements == null )
				throw new Exception.NoValueException();

			foreach( XmlNode element in elements )
			{
				Value tempValue = new Value( null, GetAttrValue( element, "name" ) );
				if( tempValue.name == null )
					throw new Exception.AttributeNotFoundException( "Enum/Val/name" );

				valueList.Add( tempValue );
			}
			
			m_fileGenerator.WriteEnum( name, valueList );

		}
	}
}
