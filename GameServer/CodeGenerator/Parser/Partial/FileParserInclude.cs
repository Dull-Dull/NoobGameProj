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
		private void ParseInclude( XmlNode node )
		{
			if( !includeAble )
				throw new Exception.CanNotIncludeException();

			//if( node.HasChildNodes )
			//	throw new Exception.UnKnownKeywordException( node.FirstChild.Name );

			fileGenerator.WriteInclude( node.InnerText );
		}
	}
}
