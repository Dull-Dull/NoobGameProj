using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

using CodeGenerator.Parser;
using CodeGenerator.Generator;

namespace CodeGenerator
{

    class Program
    {
        static int Main( string[] args )
        {
			if( ! ParseArgs( args ) )
				return 0;

			MetaFile metaFile = new MetaFile( dirPath );
			FileInfoIterator fileIter = new FileInfoIterator( dirPath );

			Console.WriteLine( "========== Start CodeGenerate ==========" );

			for( FileInfo item = fileIter.Next(); item != null; item = fileIter.Next() )
			{
				if( metaFile.CheckUpdatedFile( item ) )
				{
					FileGenerator fileGenerator = new FileGenerator( languages );
					FileParser fileParser = new FileParser( fileGenerator );

					try
					{
						Console.WriteLine( "compile : {0}", item.Name );
						fileParser.Parsing( item );
					}
					catch ( System.Exception exc )
					{
						Console.WriteLine( "Error at {0} : {1}",item.FullName ,exc.ToString() );
					}
				}
			}

			metaFile.Save();

			Console.WriteLine( "Updated : " + metaFile.CompiledCnt + "\tLatest : " + metaFile.LatestCnt );

			Console.WriteLine( "========== End CodeGenerate ==========" );

			return 0;
        }

		static bool ParseArgs( string[] args )
		{
			if( args.Length == 0 ||
				args[0].ToLower() == "help" )
			{
				PrintHelp();
				return false;
			}

			dirPath = args[0];

			if( args.Length == 1 )
			{
				languages = new string[numOfLanguages];
				languages[0] = "cpp";

				return true;
			}

			languages = new string[args.Length - 1];
			for( int i = 1; i < args.Length; ++i )
			{
				languages[i - 1] = args[i];
			}

			return true;
		}

		static void PrintHelp()
		{
			Console.WriteLine( "========== Noob CodeGenerator Help ==========" );
			Console.WriteLine( "CodeGenerator [Working Dir Path] [GenerateLanguages(Select)]" );
		}

		private static string dirPath = null;
		private static string[] languages = null;

		private const int numOfLanguages = 1;
    }

}
