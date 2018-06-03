using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator.Generator.Language
{
	partial class CppGenerator
	{
		public string GetInt8()
		{
			return "char";
		}

		public string GetUInt8()
		{
			return "unsigned char";
		}

		public string GetInt16()
		{
			return "short";
		}

		public string GetUInt16()
		{
			return "unsigned short";
		}

		public string GetInt32()
		{
			return "int";
		}

		public string GetUInt32()
		{
			return "unsigned int";
		}

		public string GetInt64()
		{
			return "int64_t";
		}

		public string GetUInt64()
		{
			return "unsigned int64_t";
		}

		public string GetFloat32()
		{
			return "float";
		}

		public string GetFloat64()
		{
			return "double";
		}

		public string GetBool()
		{
			return "bool";
		}

		public string GetString()
		{
			return "::std::wstring";
		}

		public string GetList()
		{
			return "::std::vector";
		}

		public string GetSet()
		{
			return "::std::set";
		}

		public string GetHashSet()
		{
			return "::std::unordered_set";
		}

		public string GetTree()
		{
			return "::std::map";
		}

		public string GetHashTree()
		{
			return "::std::unordered_map";
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
