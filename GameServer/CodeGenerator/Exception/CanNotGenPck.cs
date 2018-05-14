using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator.Exception
{

	[Serializable()]
	class CanNotGenPck : System.Exception
	{
		public CanNotGenPck() : base( "Packet 을 생성하려면 PckCodeRange 를 먼저 설정해야 합니다." ) { }
		protected CanNotGenPck( SerializationInfo info, StreamingContext context ) { }
	}

}
