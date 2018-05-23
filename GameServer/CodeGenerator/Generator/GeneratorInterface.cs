using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CodeGenerator.Parser;

namespace CodeGenerator.Generator
{
	interface GeneratorInterface
	{
		void WriteBegin();
		void WriteInclude( string fileName );
		void WriteData( string name, string extends, List<Value> valueList );
		void WritePacket( string name, string extends, int index, List<Value> valueList );
		void WriteEnd();

		void GenerateFile( string path );
	}
}
