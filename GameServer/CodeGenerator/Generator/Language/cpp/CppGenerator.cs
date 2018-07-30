using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CodeGenerator.FileParser;


namespace CodeGenerator.Generator.Language
{
    partial class CppGenerator : GeneratorInterface, TypeInterface
    {
		public CppGenerator( string dstPath )
		{
			m_dstPath = dstPath;
			m_typeParser = new TypeParser( this );
		}

		public void WriteBegin()
		{
			m_result = "#pragma once\n\n";
			m_registeredPcks = "";
		}

		public void WriteInclude(string fileName)
        {
			m_result += "#include \"" + fileName + ".h\"\n";
        }

		public void WriteData( string name, string extends, List<Value> valueList )
		{
			//struct 생성
			m_result += "\n";
			m_result += "struct " + name + ( extends != null ? " : public " + extends : "" ) + "\n";
			m_result += "{\n";

			//	values 생성
			foreach( var value in valueList )
			{
				m_result += "\t" + m_typeParser.ChangeType( value.type ) + " " + value.name + ";\n";
			}

			//	GetName 생성
			m_result += "\n\tstatic std::wstring GetName(){ return L\"" + name + "\"; }\n";

			m_result += "};\n\n";
			//struct 생성 끝

			//operator >> 생성
			m_result += "inline StreamReader& operator>>( StreamReader& stream, " + name + "& val )\n";
			m_result += "{\n";
			m_result += "\treturn stream";

			if( extends != null )
				m_result += ">>(" + extends + "&)val";
			
			foreach( var value in valueList )
			{
				m_result += ">>val." + value.name;
			}

			m_result += ";\n}\n\n";
			//operator >> 생성 끝

			//operator << 생성
			m_result += "inline StreamWriter& operator<<( StreamWriter& stream, " + name + "& val )\n";
			m_result += "{\n";
			m_result += "\treturn stream";

			if( extends != null )
				m_result += "<<(" + extends + "&)val";

			foreach( var value in valueList )
			{
				m_result += "<<val." + value.name;
			}

			m_result += ";\n}\n";
			//operator << 생성 끝

		}

		public void WritePacket( string name, string extends, int index, List<Value> valueList )
		{
			//struct 생성
			m_result += "\n";
			m_result += "struct " + name + ( extends != null ? " : public " + extends : " : public ::Noob::Packet" ) + "\n";
			m_result += "{\n";

			//	values 생성
			foreach( var value in valueList )
			{
				m_result += "\t" + m_typeParser.ChangeType( value.type ) + " " + value.name + ";\n";
			}

			if( valueList.Count != 0 )
				m_result += "\n";

			//  생성자 생성
			m_result += "\t" + name + "()\n";
			m_result += "\t{\n";
			m_result += "\t\tindex = " + index + ";\n";
			m_result += "\t}\n";

			if( valueList.Count != 0 )
			{
				m_result += "\n\t" + name + "( ";

				for( int i = 0; i < valueList.Count; ++i )
				{
					m_result += m_typeParser.ChangeType( valueList[i].type ) + " _" + valueList[i].name;
					if( i != valueList.Count - 1 )
						m_result += ", ";
				}
				m_result += " )\n";
				m_result += "\t{\n";
				m_result += "\t\tindex = " + index + ";\n";
				foreach( var value in valueList )
				{
					m_result += "\t\t" + value.name + " = _" + value.name + ";\n";
				}
				m_result += "\t}\n";
			}

			//	GetName 생성
			m_result += "\n\tstd::wstring GetName(){ return L\"" + name + "\"; }\n";
			//	GetCode 생성
			m_result += "\tstatic unsigned int GetIndex(){ return " + index + "; }\n";

			m_result += "};\n\n";
			//struct 생성 끝

			//operator >> 생성
			m_result += "inline StreamReader& operator>>( StreamReader& stream, " + name + "& val )\n";
			m_result += "{\n";
			m_result += "\treturn stream";

			if( extends != null )
				m_result += ">>(" + extends + "&)val";

			foreach( var value in valueList )
			{
				m_result += ">>val." + value.name;
			}

			m_result += ";\n}\n\n";
			//operator >> 생성 끝

			//operator << 생성
			m_result += "inline StreamWriter& operator<<( StreamWriter& stream, " + name + "& val )\n";
			m_result += "{\n";
			m_result += "\treturn stream";

			if( extends != null )
				m_result += "<<(" + extends + "&)val";

			foreach( var value in valueList )
			{
				m_result += "<<val." + value.name;
			}

			m_result += ";\n}\n";
			//operator << 생성 끝

			m_registeredPcks += "REGIST_PACKET( " + name + " );\n";
		}

		public void WriteEnd()
		{

		}

		public void GenerateFile( string path )
		{			
			System.IO.FileInfo file = new System.IO.FileInfo( m_dstPath + path + ".h" );
			file.Directory.Create();

			System.IO.File.WriteAllText( m_dstPath + path + ".h", m_result );
			System.IO.File.WriteAllText( m_dstPath + path + "Register.h",
				"#pragma once\n\n#include<NoobNetwork\\PacketRegister.h>\n" +
				"#include\"" + System.IO.Path.GetFileName( m_dstPath + path + ".h" ) + "\"\n\n" +
				m_registeredPcks );
		}

		private string m_result = "";
		private string m_registeredPcks = "";
		private string m_dstPath = null;

		private TypeParser m_typeParser = null;
	}
}
