using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator.Exception
{

	[Serializable()]
	class CanNotPckCodeRangeException : System.Exception
	{
		public CanNotPckCodeRangeException() : base( "PckCodeRange 실패, PckCodeRange 는 항상 소스 상위에서 해야 합니다." ) { }
		protected CanNotPckCodeRangeException( SerializationInfo info, StreamingContext context ) { }
	}

}
