using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator.Exception
{
	[Serializable()]
	class AttributeNotFoundException : System.Exception
	{
		public AttributeNotFoundException(string attrName ) : base( "주요 Attr " + attrName + "을(를) 찾을 수 없습니다." ) { }
		protected AttributeNotFoundException( SerializationInfo info, StreamingContext context ) { }
	}
}
