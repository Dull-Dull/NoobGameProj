﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace CodeGenerator.FileParser
{
	partial class FileParser
	{
		private void ParsePckCodeRange( XmlNode node )
		{
			if( !m_includeAble )
				throw new Exception.CanNotPckCodeRangeException();

			if( node.HasChildNodes )
				throw new Exception.UnKnownKeywordException( node.FirstChild.Name );

			m_usingPck = true;
			m_minPckIndex = int.Parse( GetAttrValue( node, "min" ) );
			if( m_minPckIndex < 1 )
				m_minPckIndex = 1;

			m_maxPckIndex = int.Parse( GetAttrValue( node, "max" ) );

			if( m_maxPckIndex < m_minPckIndex )
				throw new Exception.InvalidPckCodeRangeException( m_minPckIndex, m_maxPckIndex );

			m_nowPckIndex = m_minPckIndex;
		}
	}
}
