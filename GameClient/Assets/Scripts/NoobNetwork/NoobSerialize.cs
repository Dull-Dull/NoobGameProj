using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;

namespace Noob
{
	public class NoobSerializeFormatter
	{
		public delegate void WriteFunc( BinaryWriter writer, Object graph );
		public delegate void ReadFunc( BinaryReader reader, ref Object graph );

		public static void Init()
		{
			writeFuncCon.Add( typeof( int ),
				( BinaryWriter writer, Object graph ) =>
				{
					int val = (int)graph;
					writer.Write( val );
				} );
			writeFuncCon.Add( typeof( uint ),
				( BinaryWriter writer, Object graph ) =>
				{
					uint val = (uint)graph;
					writer.Write( val );
				} );
			writeFuncCon.Add( typeof( long ),
				( BinaryWriter writer, Object graph ) =>
				{
					long val = (long)graph;
					writer.Write( val );
				} );
			writeFuncCon.Add( typeof( ulong ),
				( BinaryWriter writer, Object graph ) =>
				{
					ulong val = (ulong)graph;
					writer.Write( val );
				} );
			writeFuncCon.Add( typeof( short ),
				( BinaryWriter writer, Object graph ) =>
				{
					short val = (short)graph;
					writer.Write( val );
				} );
			writeFuncCon.Add( typeof( ushort ),
				( BinaryWriter writer, Object graph ) =>
				{
					ushort val = (ushort)graph;
					writer.Write( val );
				} );
			writeFuncCon.Add( typeof( float ),
				( BinaryWriter writer, Object graph ) =>
				{
					float val = (float)graph;
					writer.Write( val );
				} );
			writeFuncCon.Add( typeof( double ),
				( BinaryWriter writer, Object graph ) =>
				{
					double val = (double)graph;
					writer.Write( val );
				} );
			writeFuncCon.Add( typeof( bool ),
				( BinaryWriter writer, Object graph ) =>
				{
					bool val = (bool)graph;
					writer.Write( val );
				} );
			writeFuncCon.Add( typeof( string ),
				( BinaryWriter writer, Object graph ) =>
				{
					string val = graph as string;
					writer.Write( val.Length );
					writer.Write( Encoding.Unicode.GetBytes( val + "\0" ) );
				} );
			writeFuncCon.Add( typeof( List<> ),
				( BinaryWriter writer, Object graph ) =>
				{
					Type nodeType = graph.GetType().GetGenericArguments()[0];

					MethodInfo methodInfo = typeof( NoobSerializeFormatter ).GetMethod( "WriteList" );
					var methodRef = methodInfo.MakeGenericMethod( nodeType );
					methodRef.Invoke( null, new Object[] { writer, graph } );

				} );
			writeFuncCon.Add( typeof( Dictionary<,> ),
				( BinaryWriter writer, Object graph ) =>
				{
					Type[] DicPairTypes = graph.GetType().GetGenericArguments();

					MethodInfo methodInfo = typeof( NoobSerializeFormatter ).GetMethod( "WriteDictionary" );
					var methodRef = methodInfo.MakeGenericMethod( DicPairTypes[0], DicPairTypes[1] );
					methodRef.Invoke( null, new Object[] { writer, graph } );				
				} );

			readFuncCon.Add( typeof( int ),
				( BinaryReader reader, ref Object graph ) =>
				{
					graph = reader.ReadInt32();
				} );
			readFuncCon.Add( typeof( uint ),
				( BinaryReader reader, ref Object graph ) =>
				{
					graph = reader.ReadUInt32();
				} );
			readFuncCon.Add( typeof( long ),
				( BinaryReader reader, ref Object graph ) =>
				{
					graph = reader.ReadInt64();
				} );
			readFuncCon.Add( typeof( ulong ),
				( BinaryReader reader, ref Object graph ) =>
				{
					graph = reader.ReadUInt64();
				} );
			readFuncCon.Add( typeof( short ),
				( BinaryReader reader, ref Object graph ) =>
				{
					graph = reader.ReadInt16();
				} );
			readFuncCon.Add( typeof( ushort ),
				( BinaryReader reader, ref Object graph ) =>
				{
					graph = reader.ReadUInt16();
				} );
			readFuncCon.Add( typeof( float ),
				( BinaryReader reader, ref Object graph ) =>
				{
					graph = reader.ReadSingle();
				} );
			readFuncCon.Add( typeof( double ),
				( BinaryReader reader, ref Object graph ) =>
				{
					graph = reader.ReadDouble();
				} );
			readFuncCon.Add( typeof( bool ),
				( BinaryReader reader, ref Object graph ) =>
				{
					graph = reader.ReadBoolean();
				} );
			readFuncCon.Add( typeof( string ),
				( BinaryReader reader, ref Object graph ) =>
				{
					int count = reader.ReadInt32();
					byte[] bytes = reader.ReadBytes( ( count + 1 ) * sizeof( char ) );
					graph = Encoding.Unicode.GetString( bytes );
				} );
			readFuncCon.Add( typeof( List<> ),
				( BinaryReader reader, ref Object graph ) =>
				{
					Type nodeType = graph.GetType().GetGenericArguments()[0];

					MethodInfo methodInfo = typeof( NoobSerializeFormatter ).GetMethod( "ReadList" );
					var methodRef = methodInfo.MakeGenericMethod( nodeType );
					methodRef.Invoke( null, new Object[] { reader, graph } );
				} );
			readFuncCon.Add( typeof( Dictionary<,> ),
				( BinaryReader reader, ref Object graph ) =>
				{
					Type[] DicPairTypes = graph.GetType().GetGenericArguments();

					MethodInfo methodInfo = typeof( NoobSerializeFormatter ).GetMethod( "ReadDictionary" );
					var methodRef = methodInfo.MakeGenericMethod( DicPairTypes[0], DicPairTypes[1] );
					methodRef.Invoke( null, new Object[] { reader, graph } );
				} );
		}

		public static void WriteList<TNode>( BinaryWriter writer, Object graph )
		{
			List<TNode> list = graph as List<TNode>;

			WriteFunc func = null;
			if( writeFuncCon.TryGetValue( typeof(TNode), out func ) )
			{
				writer.Write( list.Count );

				foreach( var node in list )
					func( writer, node );
			}			
		}

		public static void WriteDictionary<TKey,TValue>( BinaryWriter writer, Object graph )
		{
			Dictionary<TKey, TValue> dic = graph as Dictionary<TKey, TValue>;

			WriteFunc funcForKey = null;
			WriteFunc funcForVal = null;

			if( writeFuncCon.TryGetValue( typeof( TKey ), out funcForKey ) &&
				writeFuncCon.TryGetValue( typeof( TValue ), out funcForVal ) )
			{
				writer.Write( dic.Count );

				foreach( var pair in dic )
				{
					funcForKey( writer, pair.Key );
					funcForVal( writer, pair.Value );
				}
			}
		}

		public static void ReadList<TNode>( BinaryReader reader, Object graph )
		{
			List<TNode> list = graph as List<TNode>;			

			ReadFunc func = null;
			if( readFuncCon.TryGetValue( typeof(TNode), out func ) )
			{
				int count = reader.ReadInt32();

				for( int i = 0; i < count; ++i )
				{
					Object nodeGraph = Activator.CreateInstance( typeof( TNode ) );
					func( reader, ref nodeGraph );
					list.Add( (TNode)nodeGraph );
				}
			}
		}

		public static void ReadDictionary<TKey, TValue>( BinaryReader reader, Object graph )
		{
			Dictionary<TKey, TValue> dic = graph as Dictionary<TKey, TValue>;

			ReadFunc funcForKey = null;
			ReadFunc funcForVal = null;
			if( readFuncCon.TryGetValue( typeof( TKey ), out funcForKey ) &&
				readFuncCon.TryGetValue( typeof( TValue ), out funcForVal ) )
			{
				int count = reader.ReadInt32();

				for( int i = 0; i < count;  ++i )
				{
					Object keyGraph = Activator.CreateInstance( typeof( TKey ) );
					Object ValGraph = Activator.CreateInstance( typeof( TValue ) );

					funcForKey( reader, ref keyGraph );
					funcForVal( reader, ref ValGraph );

					dic.Add( (TKey)keyGraph, (TValue)ValGraph );
				}
			}
		}

		public static void Write( Stream stream, Object graph )
		{
			BinaryWriter writer = new BinaryWriter( stream );

			WriteFunc func = null;
			if( writeFuncCon.TryGetValue( graph.GetType(), out func ) )
			{
				func( writer, graph );
			}
		}

		public static void Read( Stream stream, ref Object graph )
		{
			BinaryReader reader = new BinaryReader( stream );

			ReadFunc func = null;
			if( readFuncCon.TryGetValue( graph.GetType(), out func ) )
			{
				func( reader, ref graph );
			}
		}

		public static void RegisterData( Type dataType )
		{
			writeFuncCon.Add( dataType, ( BinaryWriter writer, Object graph ) =>
			{
				FieldInfo[] fields = dataType.GetFields();

				foreach( FieldInfo field in fields )
				{
					if( field.IsLiteral && false == field.IsInitOnly )
						continue;

					Object fieldGraph = field.GetValue( graph );
					Type fieldType = fieldGraph.GetType();
					
					if( fieldType.IsGenericType )
						fieldType = fieldType.GetGenericTypeDefinition();

					WriteFunc func = null;
					if( NoobSerializeFormatter.writeFuncCon.TryGetValue( fieldType, out func ) )
					{
						func( writer, fieldGraph );
					}
				}
			} );

			readFuncCon.Add( dataType, ( BinaryReader reader, ref Object graph ) =>
			{
				FieldInfo[] fields = dataType.GetFields();

				foreach( FieldInfo field in fields )
				{
					if( field.IsLiteral && false == field.IsInitOnly )
						continue;

					Object fieldGraph = field.GetValue( graph );
					Type fieldType = fieldGraph.GetType();

					if( fieldType.IsGenericType )
						fieldType = fieldType.GetGenericTypeDefinition();

					ReadFunc func = null;
					if( NoobSerializeFormatter.readFuncCon.TryGetValue( fieldType, out func ) )
					{
						func( reader, ref fieldGraph );
						field.SetValue( graph, fieldGraph );
					}
				}
			} );
		}

		public static Dictionary<Type, WriteFunc> writeFuncCon = new Dictionary<Type, WriteFunc>();
		public static Dictionary<Type, ReadFunc> readFuncCon = new Dictionary<Type, ReadFunc>();
	}
}
