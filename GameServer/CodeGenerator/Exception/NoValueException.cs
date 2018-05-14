using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator.Exception
{

	[Serializable()]
	class NoValueException : System.Exception
	{
		public NoValueException() : base("Value 가 없습니다.") { }
		protected NoValueException( SerializationInfo info, StreamingContext context ) { }
	}

}
