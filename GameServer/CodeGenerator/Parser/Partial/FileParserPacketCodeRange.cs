using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace CodeGenerator.Parser
{
	partial class FileParser
	{
		private void ParsePckCodeRange( XmlNode node )
		{
			if( !includeAble )
				throw new Exception.CanNotPckCodeRangeException();

			if( node.HasChildNodes )
				throw new Exception.UnKnownKeywordException( node.FirstChild.Name );

			usingPck = true;
			minPckIndex = int.Parse( GetAttrValue( node, "min" ) );
			maxPckIndex = int.Parse( GetAttrValue( node, "max" ) );
			nowPckIndex = minPckIndex;
		}
	}
}
