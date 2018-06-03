using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator.Generator.Language
{
	partial class CsGenerator
	{
		public string GetInt8()
		{
			return "sbyte";
		}

		public string GetUInt8()
		{
			return "byte";
		}

		public string GetInt16()
		{
			return "short";
		}

		public string GetUInt16()
		{
			return "ushort";
		}

		public string GetInt32()
		{
			return "int";
		}

		public string GetUInt32()
		{
			return "uint";
		}

		public string GetInt64()
		{
			return "long";
		}

		public string GetUInt64()
		{
			return "ulong";
		}

		public string GetFloat32()
		{
			return "float";
		}

		public string GetBool()
		{
			return "bool";
		}

		public string GetFloat64()
		{
			return "double";
		}

		public string GetString()
		{
			return "string";
		}

		public string GetList()
		{
			return "List";
		}

		public string GetSet()
		{
			return "SortedSet";
		}

		public string GetHashSet()
		{
			return "SortedSet";
		}

		public string GetTree()
		{
			return "Dictionary";
		}

		public string GetHashTree()
		{
			return "Dictionary";
		}

		public string GetOpenBracket()
		{
			return "<";
		}

		public string GetCloseBracket()
		{
			return ">";
		}
	}
}
