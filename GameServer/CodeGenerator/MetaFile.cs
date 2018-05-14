using System;
using System.IO;
using System.Collections.Generic;
using System.Diagnostics;

namespace CodeGenerator
{

	class MetaFile
	{
		public MetaFile( string folderPath )
		{
			rootPath = Path.GetFullPath( folderPath );
			metaFile = Path.Combine( rootPath, @"NoobGenerator.meta" );
			metaData = new Dictionary<string, DateTime>();
			existFile = new HashSet<string>();
			compiledCnt = 0;
			latestCnt = 0;

			if( File.Exists( metaFile ) )
				Read();
		}

		private void CreateMetaFile()
		{
			try
			{
				File.Create( metaFile );

				FileAttributes fileAttr = File.GetAttributes( metaFile );
				if( ( fileAttr & FileAttributes.Hidden ) != FileAttributes.Hidden )
				{
					fileAttr = fileAttr | FileAttributes.Hidden;
					File.SetAttributes( metaFile, fileAttr );
				}
			}
			catch( System.Exception ex )
			{
				Debug.Assert( false, ex.ToString() );
			}
		}

		private void Read()
		{
			try
			{
				using( StreamReader readStream = new StreamReader( metaFile ) )
				{
					string line;
					while( ( line = readStream.ReadLine() ) != null )
					{
						string[] param = line.Split(new char[] {'\t'});
						metaData.Add( param[0], DateTime.Parse( param[1] ) );
					}
				}					
			}
			catch( System.Exception exc )
			{
				Debug.Assert( false, exc.ToString() );
			}
		}



		public bool CheckUpdatedFile( FileInfo fileInfo )
		{
			if( fileInfo.Extension == ".xml" )
			{
				string fileName = fileInfo.FullName.Substring( rootPath.Length );

				existFile.Add( fileName );

				if( metaData.ContainsKey( fileName ) )
				{
					if( fileInfo.LastWriteTime.ToString() != metaData[fileName].ToString() )
					{
						metaData[fileName] = fileInfo.LastWriteTime;
						compiledCnt++;
						return true;
					}
					latestCnt++;
				}
				else
				{
					metaData.Add( fileName, fileInfo.LastWriteTime );
					compiledCnt++;
					return true;
				}

			}

			return false;
		}

		public void Save()
		{
			try
			{
				Reveal();

				using( System.IO.StreamWriter file = new System.IO.StreamWriter( metaFile, false ) )
				{
					foreach( var iter in metaData )
					{
						if( existFile.Contains( iter.Key ) )
						{
							file.WriteLine( iter.Key + '\t' + iter.Value );
						}
					}
				}
			}
			catch( System.Exception exc )
			{
				Debug.Assert( false, exc.ToString() );
			}
			finally
			{
				Hide();
			}
		}

		private void Hide()
		{
			if( File.Exists( metaFile ) )
			{
				FileAttributes fa = File.GetAttributes( metaFile );
				if( ( fa & FileAttributes.Hidden ) != FileAttributes.Hidden )
				{
					fa = fa | FileAttributes.Hidden;
					File.SetAttributes( metaFile, fa );
				}
			}
		}

		private void Reveal()
		{
			if( File.Exists( metaFile ) )
			{
				FileAttributes fa = File.GetAttributes( metaFile );
				if( ( fa & FileAttributes.Hidden ) == FileAttributes.Hidden )
				{
					fa = fa & ~FileAttributes.Hidden;
					File.SetAttributes( metaFile, fa );
				}
			}
		}

		private string rootPath;
		private string metaFile;
		private Dictionary<string, DateTime> metaData;
		private HashSet<string> existFile;
		private int compiledCnt;
		private int latestCnt;

		public int CompiledCnt
		{
			get
			{
				return compiledCnt;
			}
		}

		public int LatestCnt
		{
			get
			{
				return latestCnt;
			}
		}
	}

}