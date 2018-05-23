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
		public FileGenerator( List< Program.GenTarget > targetCon )
		{
			foreach( var target in targetCon )
			{
				switch( target.m_language )
				{
					case "cpp":
					case "c++":
						generatorCon.Add( new CppGenerator( target.m_dstPath ) );
						break;
					case "cs":
					case "c#":
						generatorCon.Add( new CsGenerator( target.m_dstPath ) );
						break;
					default:
						break;
				}
			}			
		}

		public void WriteBegin()
		{
			foreach( var generator in generatorCon )
				generator.WriteBegin();
		}

		public void WriteInclude(string fileName)
		{
			foreach( var generator in generatorCon )
				generator.WriteInclude( fileName );
		}

		public void WriteData( string name, string extends, List<Value> valueList )
		{
			foreach( var generator in generatorCon )
				generator.WriteData( name, extends, valueList );
		}

		public void WritePacket( string name, string extends, int index, List<Value> valueList )
		{
			foreach( var generator in generatorCon )
				generator.WritePacket( name, extends, index, valueList );
		}

		public void WriteEnd()
		{
			foreach( var generator in generatorCon )
				generator.WriteEnd();
		}

		public void GenerateFile( string path )
		{
			foreach( var generator in generatorCon )
				generator.GenerateFile( path );
		}

		private List<GeneratorInterface> generatorCon = new List<GeneratorInterface>();
	}
}
