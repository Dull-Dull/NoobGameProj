using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator.Exception
{

	[Serializable()]
	class InvalidPckCodeRangeException : System.Exception
	{
		public InvalidPckCodeRangeException(int min, int max) : base( $"min({min})이 max({max})보다 큽니다." ) { }
		protected InvalidPckCodeRangeException( SerializationInfo info, StreamingContext context ) { }
	}

}
