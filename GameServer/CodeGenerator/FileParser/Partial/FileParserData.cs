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
		private void ParseData( XmlNode node )
		{
			string name = null;
			string extendsData = null;

			name = GetAttrValue( node, "name" );
			extendsData = GetAttrValue( node, "extends" );

			if( name == null )
				throw new Exception.AttributeNotFoundException( "Data/name" );

			List<Value> valueList = new List<Value>();

			XmlNodeList elements = node.ChildNodes;

			if( elements == null )
				throw new Exception.NoValueException();

			foreach( XmlNode element in elements )
			{
				Value tempValue = new Value( GetAttrValue( element, "type" ), GetAttrValue( element, "name" ) );
				if( tempValue.type == null || tempValue.name == null )
					throw new Exception.AttributeNotFoundException( "Data/Val/type or name" );

				valueList.Add( tempValue );
			}

			m_fileGenerator.WriteData( name, extendsData, valueList );
						
		}
	}
}
