using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator.Generator
{
	class TypeParser
	{
		public TypeParser( TypeInterface typeInterface )
		{
			m_typeInteface = typeInterface;

			m_typeChangeFuncCon = new Dictionary<string, ChangeTypeDeligate>();
			m_typeChangeFuncCon.Add( "int8", typeInterface.GetInt8 );
			m_typeChangeFuncCon.Add( "uint8", typeInterface.GetUInt8 );
			m_typeChangeFuncCon.Add( "int16", typeInterface.GetInt16 );
			m_typeChangeFuncCon.Add( "uint16", typeInterface.GetUInt16 );
			m_typeChangeFuncCon.Add( "int32", typeInterface.GetInt32 );
			m_typeChangeFuncCon.Add( "uint32", typeInterface.GetUInt32 );
			m_typeChangeFuncCon.Add( "int64", typeInterface.GetInt64 );
			m_typeChangeFuncCon.Add( "uint64", typeInterface.GetUInt64 );
			m_typeChangeFuncCon.Add( "float32", typeInterface.GetFloat32 );
			m_typeChangeFuncCon.Add( "float64", typeInterface.GetFloat64 );
			m_typeChangeFuncCon.Add( "bool", typeInterface.GetBool );
			m_typeChangeFuncCon.Add( "string", typeInterface.GetString );
			m_typeChangeFuncCon.Add( "list", typeInterface.GetList );
			m_typeChangeFuncCon.Add( "set", typeInterface.GetSet );
			m_typeChangeFuncCon.Add( "hash_set", typeInterface.GetHashSet );
			m_typeChangeFuncCon.Add( "tree", typeInterface.GetTree );
			m_typeChangeFuncCon.Add( "hash_tree", typeInterface.GetHashTree );
		}

		public string ChangeType( string type )
		{
			string result = "";
			string temp = "";

			if( type.IndexOf( '[' ) == -1 )
				return change( type );

			foreach( var c in type )
			{
				switch( c )
				{
					case '[':
						result += change( temp );
						result += m_typeInteface.GetOpenBracket();
						temp = "";
						break;
					case ']':
						result += change( temp );
						result += m_typeInteface.GetCloseBracket();
						temp = "";
						break;
					case ',':
						result += change( temp );
						result += ',';
						temp = "";
						break;
					default:
						temp += c;
						break;
				}
			}

			return result;
		}

		private string change( string type )
		{
			type = type.Trim();
			if( m_typeChangeFuncCon.ContainsKey( type ) )
				return m_typeChangeFuncCon[type]();
			else
				return type;
		}
		
		private delegate string ChangeTypeDeligate();
		private TypeInterface m_typeInteface = null;
		private Dictionary<string, ChangeTypeDeligate> m_typeChangeFuncCon = null;
	}

	interface TypeInterface
	{
		string GetInt8();
		string GetUInt8();
		string GetInt16();
		string GetUInt16();
		string GetInt32();
		string GetUInt32();
		string GetInt64();
		string GetUInt64();

		string GetFloat32();
		string GetFloat64();

		string GetBool();

		string GetString();
		string GetList();
		string GetSet();
		string GetHashSet();
		string GetTree();
		string GetHashTree();

		string GetOpenBracket();
		string GetCloseBracket();
	}
}
