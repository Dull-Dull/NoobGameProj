using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace CodeGenerator.FileParser
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
		public FileParser( string srcPath, Generator.FileGenerator fileGenerator )
		{
			m_srcPath = srcPath;
			m_doc = new XmlDocument();
			this.m_fileGenerator = fileGenerator;
			m_includeAble = true;
			m_usingPck = false;
			m_minPckIndex = 0;
			m_maxPckIndex = 0;
			m_nowPckIndex = 0;
		}

		public void Parsing( System.IO.FileInfo xmlInfo )
		{
			m_doc.Load( xmlInfo.FullName );

			m_fileGenerator.WriteBegin();

			foreach( XmlNode node in m_doc.DocumentElement.ChildNodes )
			{
				if( node.Name != "Include" &&
					node.Name != "PckCodeRange" )
					m_includeAble = false;

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
					case "Enum":
						ParseEnum( node );
						break;
					default:
						throw new Exception.UnKnownKeywordException( node.Name );
				}
			}

			m_fileGenerator.WriteEnd();
			//int lastIndex = xmlInfo.DirectoryName.LastIndexOf( m_srcPath )	;
			string path = xmlInfo.DirectoryName.Substring( m_srcPath.Length );
			m_fileGenerator.GenerateFile( path + "\\" + System.IO.Path.GetFileNameWithoutExtension( xmlInfo.FullName ) );
		}

		private string GetAttrValue( XmlNode node, string attrName )
		{
			XmlAttribute attr = node.Attributes[attrName];
			if( attr == null )
				return null;

			return attr.Value;
		}

		private string m_srcPath = null;
		private XmlDocument m_doc = null;
		private Generator.FileGenerator m_fileGenerator = null;
		private bool m_includeAble;
		private bool m_usingPck;
		private int m_minPckIndex, m_maxPckIndex, m_nowPckIndex;
	}
}
