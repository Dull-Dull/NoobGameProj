using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace CodeGenerator.Parser
{
	class Value
	{
		public string type { get; set; } = null;
		public string name { get; set; } = null;

		public Value( string type, string name )
		{
			this.type = type;
			this.name = name;
		}
	}

	partial class FileParser
	{
		public FileParser( Generator.FileGenerator fileGenerator )
		{
			doc = new XmlDocument();
			this.fileGenerator = fileGenerator;
			includeAble = true;

			usingPck = false;
			minPckIndex = 0;
			maxPckIndex = 0;
			nowPckIndex = 0;
		}

		public void Parsing( System.IO.FileInfo xmlInfo )
		{
			doc.Load( xmlInfo.FullName );
			
			System.Console.WriteLine( doc.DocumentElement.Name );

			foreach( XmlNode node in doc.DocumentElement.ChildNodes )
			{
				if( node.Name != "Include" &&
					node.Name != "PckCodeRange" )
					includeAble = false;

				switch( node.Name )
				{
					case "Include":
						ParseInclude( node );
						break;
					case "Data":
						ParseData( node );
						break;
					case "Packet":
						ParsePacket( node );
						break;
					case "PckCodeRange":
						ParsePckCodeRange( node );
						break;
					default:
						throw new Exception.UnKnownKeywordException( node.Name );
				}
			}

			fileGenerator.GenerateFile( xmlInfo.DirectoryName + "\\" + System.IO.Path.GetFileNameWithoutExtension( xmlInfo.FullName ) );
		}

		private string GetAttrValue( XmlNode node, string attrName )
		{
			XmlAttribute attr = node.Attributes[attrName];
			if( attr == null )
				return null;

			return attr.Value;
		}

		private XmlDocument doc;
		private Generator.FileGenerator fileGenerator;
		private bool includeAble;

		bool usingPck;
		int minPckIndex, maxPckIndex, nowPckIndex;
	}
}
