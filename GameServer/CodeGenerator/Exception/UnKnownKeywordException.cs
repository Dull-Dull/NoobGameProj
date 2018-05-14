using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator.Exception
{

	[Serializable()]
	class UnKnownKeywordException : System.Exception
	{
		//public UnKnownKeywordException() : base() { }
		public UnKnownKeywordException( string keyword ) : base( keyword + " 은(는) 없는 형식 입니다." ) { }
		//public UnKnownKeywordException( string msg, System.Exception exc ) : base( msg, exc ) { }
		protected UnKnownKeywordException( SerializationInfo info, StreamingContext context ) { }
	}

}
