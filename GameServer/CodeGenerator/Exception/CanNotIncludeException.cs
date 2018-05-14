using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator.Exception
{

	[Serializable()]
	class CanNotIncludeException : System.Exception
	{
		public CanNotIncludeException() : base( "Include 실패, Include 는 항상 소스 상위에서 해야 합니다." ) { }
		//public CanNotIncludeException( string msg ) : base( msg ) { }
		//public CanNotIncludeException( string msg, System.Exception exc ) : base( msg, exc ) { }
		protected CanNotIncludeException( SerializationInfo info, StreamingContext context ) { }
	}

}
