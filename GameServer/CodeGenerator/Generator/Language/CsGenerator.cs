using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CodeGenerator.Parser;

namespace CodeGenerator.Generator.Language
{
	class CsGenerator : GeneratorInterface
	{
		public CsGenerator( string dstPath )
		{			
			m_dstPath = dstPath;
		}

		public void WriteBegin()
		{
			m_result = "using System;\n" +
						"using System.Collections.Generic;\n\n" +
						"namespace Noob\n" +
						"{\n";
		}

		public void WriteInclude( string fileName )
		{
		}

		public void WriteData( string name, string extends, List<Value> valueList )
		{
			m_result += "\n";
			m_result += "\t[NoobSerializAbleAttibute]\n";
			m_result += "\tpublic class " + name + ( extends != null ? " : " + extends : "" ) + "\n\t{\n";
			
			foreach( var value in valueList )
			{
				m_result += "\t\tpublic " + ChangeType( value.type ) + " " + value.name + " = " + GetDefaultVal( value.type ) + ";\n";
			}

			m_result += "\t}\n";
		}

		public void WritePacket( string name, string extends, int index, List<Value> valueList )
		{
			m_result += "\n";
			m_result += "\t[NoobSerializAbleAttibute]\n";
			m_result += "\tpublic class " + name + ( extends != null ? " : " + extends : " : " + "Packet" ) + "\n\t{\n";

			foreach( var value in valueList )
			{
				m_result += "\t\tpublic " + ChangeType( value.type ) + " " + value.name + " = " + GetDefaultVal( value.type ) + ";\n";
			}

			if( valueList.Count != 0 )
				m_result += "\n";

			m_result += "\t\tpublic " + name + "(){ index = " + index + "; }\n";
			m_result += "\t\tpublic static uint GetIndex(){ return " + index + "; }\n";

			m_result += "\t}\n";
		}

		public void WriteEnd()
		{
			m_result += "\n}";
		}

		public void GenerateFile( string path )
		{
			System.IO.FileInfo file = new System.IO.FileInfo( m_dstPath + path + ".cs" );
			file.Directory.Create(); 
			System.IO.File.WriteAllText( file.FullName, m_result );
		}

		private string ChangeType( string type )
		{
			string ret = type.Trim();
			ret = ret.Replace( '[', '<' );
			ret = ret.Replace( ']', '>' );

			ret = ret.Replace( "map", "Dictionary" );
			ret = ret.Replace( "vector", "List" );

			ret = ret.Replace( "unsigned ", "u" );
			ret = ret.Replace( "int64", "long" );

			return ret;
		}

		private string GetDefaultVal( string type )
		{
			string ret = "";

			if( type.IndexOf( "map" ) == 0 ||
				type.IndexOf( "vector" ) == 0 )
			{
				ret = "new " + ChangeType( type ) + "()";
			}				
			else if( type.IndexOf( "string" ) == 0 )
			{
				ret = "\"\"";
			}
			else
			{
				ret = "0";
			}

			return ret;
		}

		private string m_result = "";

		private string m_dstPath = null;
	}
}
