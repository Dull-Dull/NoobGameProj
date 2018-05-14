using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CodeGenerator.Parser;


namespace CodeGenerator.Generator.Language
{
    class CppGenerator : GeneratorInterface
    {
		public void WriteInclude(string fileName)
        {
			result += "#include \"" + fileName + "\"\n";
        }

		public void WriteData( string name, string extends, List<Value> valueList )
		{
			//struct 생성
			result += "\n";
			result += "struct " + name + ( extends != null ? " : public " + extends : "" ) + "\n";
			result += "{\n";

			//	values 생성
			foreach( var value in valueList )
			{
				result += "\t" + ChangeType( value.type ) + " " + value.name + ";\n";
			}

			//	GetName 생성
			result += "\n\tstatic std::wstring GetName(){ return L\"" + name + "\"; }\n";

			result += "};\n\n";
			//struct 생성 끝

			//operator >> 생성
			result += "inline StreamReader& operator>>( StreamReader& stream, " + name + "& val )\n";
			result += "{\n";
			result += "\treturn stream";

			if( extends != null )
				result += ">>(" + extends + "&)val";
			
			foreach( var value in valueList )
			{
				result += ">>val." + value.name;
			}

			result += ";\n}\n\n";
			//operator >> 생성 끝

			//operator << 생성
			result += "inline StreamWriter& operator<<( StreamWriter& stream, " + name + "& val )\n";
			result += "{\n";
			result += "\treturn stream";

			if( extends != null )
				result += "<<(" + extends + "&)val";

			foreach( var value in valueList )
			{
				result += "<<val." + value.name;
			}

			result += ";\n}\n";
			//operator << 생성 끝

		}

		public void WritePacket( string name, string extends, int index, List<Value> valueList )
		{
			//struct 생성
			result += "\n";
			result += "struct " + name + ( extends != null ? " : public " + extends : " : public ::Noob::Packet" ) + "\n";
			result += "{\n";

			//	values 생성
			foreach( var value in valueList )
			{
				result += "\t" + ChangeType( value.type ) + " " + value.name + ";\n";
			}

			//  생성자 생성
			result += "\n\t" + name + "()\n";
			result += "\t{\n";
			result += "\t\tindex = " + index + ";\n";
			result += "\t}\n";

			if( valueList.Count != 0 )
			{
				result += "\n\t" + name + "( ";

				for( int i = 0; i < valueList.Count; ++i )
				{
					result += ChangeType( valueList[i].type ) + " _" + valueList[i].name;
					if( i != valueList.Count - 1 )
						result += ", ";
				}
				result += " )\n";
				result += "\t{\n";
				result += "\t\tindex = " + index + ";\n";
				foreach( var value in valueList )
				{
					result += "\t\t" + value.name + " = _" + value.name + ";\n";
				}
				result += "\t}\n";
			}

			//	GetName 생성
			result += "\n\tstd::wstring GetName(){ return L\"" + name + "\"; }\n";
			//	GetCode 생성
			result += "\tstatic unsigned int GetIndex(){ return " + index + "; }\n";

			result += "};\n\n";
			//struct 생성 끝

			//operator >> 생성
			result += "inline StreamReader& operator>>( StreamReader& stream, " + name + "& val )\n";
			result += "{\n";
			result += "\treturn stream";

			if( extends != null )
				result += ">>(" + extends + "&)val";

			foreach( var value in valueList )
			{
				result += ">>val." + value.name;
			}

			result += ";\n}\n\n";
			//operator >> 생성 끝

			//operator << 생성
			result += "inline StreamWriter& operator<<( StreamWriter& stream, " + name + "& val )\n";
			result += "{\n";
			result += "\treturn stream";

			if( extends != null )
				result += "<<(" + extends + "&)val";

			foreach( var value in valueList )
			{
				result += "<<val." + value.name;
			}

			result += ";\n}\n";
			//operator << 생성 끝

			registeredPcks += "REGIST_PACKET( " + name + " );\n";
		}


		public void GenerateFile( string fullPath )
		{
			System.IO.File.WriteAllText( fullPath + ".h", result );
			System.IO.File.WriteAllText( fullPath + "Register.h",
				"#pragma once\n\n#include<NoobNetwork\\PacketRegister.h>\n" +
				"#include\"" + System.IO.Path.GetFileName( fullPath + ".h" ) + "\"\n\n" +
				registeredPcks );
		}

		private string ChangeType( string type )
		{
			string ret = type.Trim();
			ret = ret.Replace( '[', '<' );
			ret = ret.Replace( ']', '>' );

			ret = ret.Replace( "map", "::std::map" );
			ret = ret.Replace( "vector", "::std::vector" );
			ret = ret.Replace( "string", "::std::wstring" );

			ret = ret.Replace( "int64", "int64_t" );

			return ret;
		}

		private string result = "#pragma once\n\n";
		private string registeredPcks = "";
	}
}
