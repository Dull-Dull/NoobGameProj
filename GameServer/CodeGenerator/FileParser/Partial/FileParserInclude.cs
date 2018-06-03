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
		private void ParseInclude( XmlNode node )
		{
			if( !m_includeAble )
				throw new Exception.CanNotIncludeException();

			//if( node.HasChildNodes )
			//	throw new Exception.UnKnownKeywordException( node.FirstChild.Name );

			m_fileGenerator.WriteInclude( node.InnerText );
		}
	}
}
