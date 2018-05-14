using System.Collections.Generic;
using System.IO;

namespace CodeGenerator
{
	class FileInfoIterator
	{
		enum NodeType
		{
			FILE,
			DIRECTORY
		}

		class Node
		{
			public DirectoryInfo[]     dirInfos;
			public FileInfo[]          fileInfos;

			public int			index;
		}

		public FileInfoIterator( string folderPath )
		{
			rootDir		= new DirectoryInfo( folderPath );
			nodeStack	= new Stack<Node>();

			NewDir( rootDir );
		}

		public FileInfo Next()
		{
			Node node = null;

			try
			{
				node = nodeStack.Peek();
			}
			catch( System.InvalidOperationException )
			{
				return null;
			}
			
			if( node.fileInfos != null )
			{
				if( node.fileInfos.Length == node.index )
				{
					node.fileInfos = null;
					node.index = 0;
				}
				else
				{
					return node.fileInfos[node.index++];
				}
			}

			if( node.fileInfos == null )
			{
				if( node.dirInfos.Length == node.index )
				{
					nodeStack.Pop();
					return Next();
				}
				else
				{
					NewDir( node.dirInfos[node.index++] );
					return Next();
				}
			}

			return null;
		}

		private void NewDir( DirectoryInfo dirInfo )
		{
			Node tempNode = new Node();
			tempNode.dirInfos = dirInfo.GetDirectories();
			tempNode.fileInfos = dirInfo.GetFiles();
			tempNode.index = 0;

			nodeStack.Push( tempNode );
		}



		private DirectoryInfo	rootDir		= null;
		private Stack<Node>		nodeStack	= null;
	}
}