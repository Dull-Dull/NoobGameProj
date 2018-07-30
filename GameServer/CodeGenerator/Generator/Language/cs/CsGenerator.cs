﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CodeGenerator.FileParser;

namespace CodeGenerator.Generator.Language
{
	partial class CsGenerator : GeneratorInterface, TypeInterface
	{
		public CsGenerator( string dstPath )
		{			
			m_dstPath = dstPath;
			m_typeParser = new TypeParser( this );
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
			m_result += "\t[NoobSerializAble]\n";
			m_result += "\tpublic class " + name + ( extends != null ? " : " + extends : "" ) + "\n\t{\n";
			
			foreach( var value in valueList )
			{
				m_result += "\t\tpublic " + m_typeParser.ChangeType( value.type ) + " " + value.name + " = " + GetDefaultVal( value.type ) + ";\n";
			}

			m_result += "\t}\n";
		}

		public void WritePacket( string name, string extends, int index, List<Value> valueList )
		{
			m_result += "\n";
			m_result += "\t[NoobSerializAble]\n";
			m_result += "\tpublic class " + name + ( extends != null ? " : " + extends : " : " + "Packet" ) + "\n\t{\n";

			foreach( var value in valueList )
			{
				m_result += "\t\tpublic " + m_typeParser.ChangeType( value.type ) + " " + value.name + " = " + GetDefaultVal( value.type ) + ";\n";
			}

			if( valueList.Count != 0 )
				m_result += "\n";

			m_result += "\t\tpublic override uint GetIndex(){ return index; }\n";
			m_result += $"\t\tpublic const uint index = {index};\n";

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

		private string GetDefaultVal( string type )
		{
			type = type.Trim();

			if( type.IndexOf( "int8" ) == 0 || type.IndexOf( "uint8" ) == 0 ||
				type.IndexOf( "int16" ) == 0 || type.IndexOf( "uint16" ) == 0 ||
				type.IndexOf( "int32" ) == 0 || type.IndexOf( "uint32" ) == 0 ||
				type.IndexOf( "int64" ) == 0 || type.IndexOf( "uint64" ) == 0 )
			{
				return "0";
			}
			else if( type.IndexOf( "float32" ) == 0 ||
				type.IndexOf( "float64" ) == 0 )
			{
				return "0.0f";
			}
			else if( type.IndexOf( "string" ) == 0 )
			{
				return "\"\"";
			}
			else if( type.IndexOf( "bool" ) == 0 )
			{
				return "false";
			}
			else
			{
				return "new " + m_typeParser.ChangeType( type ) + "()";
			}
		}

		private string m_result = "";
		private string m_dstPath = null;

		private TypeParser m_typeParser = null;
	}
}
