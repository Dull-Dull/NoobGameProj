using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

using CodeGenerator.FileParser;
using CodeGenerator.Generator;

namespace CodeGenerator
{

    class Program
    {
        static int Main( string[] args )
        {
			if( ! ParseArgs( args ) )
				return 0;

			MetaFile metaFile = new MetaFile( srcPath );
			FileInfoIterator fileIter = new FileInfoIterator( srcPath );
			FileGenerator fileGenerator = new FileGenerator( targetCon );

			Console.WriteLine( "========== Start CodeGenerate ==========" );

			for( FileInfo item = fileIter.Next(); item != null; item = fileIter.Next() )
			{
				if( metaFile.CheckUpdatedFile( item ) )
				{
					try
					{
						FileParser.FileParser fileParser = new FileParser.FileParser( srcPath, fileGenerator );
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
			
			srcPath = Path.GetDirectoryName( args[0] + '\\' );

			if( args.Length == 1 )
			{
				GenTarget genTarget = new GenTarget();
				genTarget.m_dstPath = srcPath;
				genTarget.m_language = "cpp";
				targetCon.Add( genTarget );

				return true;
			}

			for( int i = 1; i < args.Length; ++i )
			{
				string lowerArg = args[i].ToLower();
				string[] splitedArg = lowerArg.Split( ',' );
				
				GenTarget genTarget = new GenTarget();
				genTarget.m_language = splitedArg[0];
				genTarget.m_dstPath = Path.GetDirectoryName( splitedArg[1] + '\\' );
				targetCon.Add( genTarget );
			}

			return true;
		}

		static void PrintHelp()
		{
			Console.WriteLine( "========== Noob CodeGenerator Help ==========" );
			Console.WriteLine( "CodeGenerator [Src Path] [language/Dst Path] ..." );
			Console.WriteLine( "Language Type : cpp, cs" );

		}

		public class GenTarget
		{
			public string m_language;
			public string m_dstPath;
		}

		private static List<GenTarget> targetCon = new List<GenTarget>();

		private static string srcPath = null;
    }

}
