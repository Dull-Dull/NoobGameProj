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
		public void WriteInclude( string fileName )
		{
		}

		public void WriteData( string name, string extends, List<Value> valueList )
		{
			result += "\n";
			result += "\t[NoobSerializAbleAttibute]\n";
			result += "\tpublic class " + name + ( extends != null ? " : " + extends : "" ) + "\n\t{\n";
			
			foreach( var value in valueList )
			{
				result += "\t\tpublic " + ChangeType( value.type ) + " " + value.name + ";\n";
			}

			result += "\t}\n";
		}

		public void WritePacket( string name, string extends, int code, List<Value> valueList )
		{
			result += "\n";
			result += "\t[NoobSerializAbleAttibute]\n";
			result += "\tpublic class " + name + ( extends != null ? " : " + extends : " : " + "Packet" ) + "\n\t{\n";

			foreach( var value in valueList )
			{
				result += "\t\tpublic " + ChangeType( value.type ) + " " + value.name + ";\n";
			}

			result += "\n\t\tpublic uint GetIndex(){ return " + code + "; }\n";

			result += "\t}\n";
		}

		public void GenerateFile( string fullPath )
		{
			result += "\n}";
			System.IO.File.WriteAllText( fullPath + ".cs", result );
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

		private string result = "using System;\n" +
								"using System.Collections.Generic;\n\n" +
								"namespace Noob\n" +
								"{\n";
	}
}
