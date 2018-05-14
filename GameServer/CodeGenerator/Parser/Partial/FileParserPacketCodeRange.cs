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
			if( !m_includeAble )
				throw new Exception.CanNotPckCodeRangeException();

			if( node.HasChildNodes )
				throw new Exception.UnKnownKeywordException( node.FirstChild.Name );

			m_usingPck = true;
			m_minPckIndex = int.Parse( GetAttrValue( node, "min" ) );
			m_maxPckIndex = int.Parse( GetAttrValue( node, "max" ) );
			m_nowPckIndex = m_minPckIndex;
		}
	}
}
