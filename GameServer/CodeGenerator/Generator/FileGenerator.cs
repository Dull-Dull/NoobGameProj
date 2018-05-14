using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CodeGenerator.Generator.Language;
using CodeGenerator.Parser;

namespace CodeGenerator.Generator
{
	class FileGenerator : GeneratorInterface
	{
		public FileGenerator( string[] languages )
		{
			generatorList = new Dictionary<string, GeneratorInterface>();

			foreach( string language in languages )
			{
				language.ToLower();
				switch( language )
				{
					case "cpp":
					case "c++":
						if( ! generatorList.ContainsKey("cpp") )
							generatorList.Add("cpp",new CppGenerator());
						break;
					case "cs":
					case "c#":
						if( ! generatorList.ContainsKey( "cs" ) )
							generatorList.Add( "cs", new CsGenerator() );
						break;
					default:
						break;
				}
			}
		}

		public void WriteInclude(string fileName)
		{
			foreach( var generator in generatorList )
				generator.Value.WriteInclude( fileName );
		}

		public void WriteData( string name, string extends, List<Value> valueList )
		{
			foreach( var generator in generatorList )
				generator.Value.WriteData( name, extends, valueList );
		}

		public void WritePacket( string name, string extends, int code, List<Value> valueList )
		{
			foreach( var generator in generatorList )
				generator.Value.WritePacket( name, extends, code, valueList );
		}

		public void GenerateFile( string fullPath )
		{
			foreach( var generator in generatorList )
				generator.Value.GenerateFile( fullPath );
		}

		private Dictionary<string,GeneratorInterface> generatorList = null;
	}
}
