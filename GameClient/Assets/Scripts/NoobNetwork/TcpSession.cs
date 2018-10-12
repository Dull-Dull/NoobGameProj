using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace Noob
{
	class TcpSession
	{
		public delegate void ConnectFunc( SocketError err );
		public delegate void DisconnectFunc();

		public TcpSession()
		{
			m_recvArgs = new SocketAsyncEventArgs();
			m_recvArgs.Completed += onRecvComplete;
			m_recvArgs.UserToken = this;
			m_recvArgs.SetBuffer( new byte[4096], 0, 4096 );

			m_sendArgs = new SocketAsyncEventArgs();
			m_sendArgs.Completed += onSendComplete;
			m_sendArgs.UserToken = this;
			m_sendArgs.SetBuffer( new byte[4096], 0, 4096 );
		}

		public void Connect( string ip, int port )
		{
			if( m_sock != null )
				return;

			m_sock = new Socket( AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP );

			m_sock.Connect( ip, port );
			onConnectComplete( null, null );
		}

		public void AsyncConnect( string ip, int port )
		{
			if( m_sock != null )
				return;

			m_sock = new Socket( AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP );

			SocketAsyncEventArgs connArgs = new SocketAsyncEventArgs();
			connArgs.RemoteEndPoint = new IPEndPoint( IPAddress.Parse( ip ), port );
			connArgs.UserToken = this;
			connArgs.Completed += onConnectComplete;

			if( m_sock.ConnectAsync( connArgs ) == false )
				onConnectComplete( null, connArgs );
		}

		private void onConnectComplete( Object sender, SocketAsyncEventArgs e )
		{
			SocketError err = SocketError.Success;

			if( e != null )
				err = e.SocketError;

			m_OnConnect( err );

			if( err == SocketError.Success )
				postRecv();
		}

		public bool IsConnected
		{
			get{
				if( m_sock == null )
					return false;
				else
					return m_sock.Connected;
			}			
		}

		public void Close()
		{
			if( m_sock == null )
				return;

			m_sock.Shutdown( SocketShutdown.Both );
			m_sock.Close();
		}

		public void Send( Packet pck )
		{
			bool pending = false;

			lock( m_sendLock )
			{
				m_sendPckQueue.Enqueue( pck );

				if( m_sendPckQueue.Count == 1 )
					pending = postSend();
				else
					return;
			}

			if( pending == false )
				onSendComplete( null, m_sendArgs );
		}

		private bool postSend()
		{
			if( m_sock == null )
				return true;

			Packet pck = m_sendPckQueue.Peek();
			
			m_sendMem.SetLength( HEADER_SIZE );
			m_sendMem.Seek( HEADER_SIZE, SeekOrigin.Begin );
			NoobSerializeFormatter.Write( m_sendMem, pck );

			Array.Copy( BitConverter.GetBytes( m_sendMem.Length ), 0, m_sendMem.GetBuffer(), 0, sizeof( uint ) );
			Array.Copy( BitConverter.GetBytes( pck.GetIndex() ), 0, m_sendMem.GetBuffer(), sizeof( uint ), sizeof( uint ) );

			m_sendArgs.SetBuffer( m_sendArgs.Offset, (int)m_sendMem.Length );
			Array.Copy( m_sendMem.GetBuffer(), 0, m_sendArgs.Buffer, m_sendArgs.Offset, m_sendMem.Length );

			return m_sock.SendAsync( m_sendArgs );
		}

		private void onSendComplete( Object sender, SocketAsyncEventArgs e )
		{
			if( e.BytesTransferred <= 0 || e.SocketError != SocketError.Success )
				return;

			while( true )
			{
				bool pending = false;
				lock( m_sendLock )
				{
					try
					{
						m_sendPckQueue.Dequeue();

						if( m_sendPckQueue.Count != 0 )
							pending = postSend();
						else
							return;
					}
					catch( InvalidOperationException ) { return; }
				}

				if( pending )
					return;
			}

		}

		public Packet TryPopPacket()
		{
			lock( m_recvPckQueue )
			{
				try
				{
					return m_recvPckQueue.Dequeue();
				}
				catch( InvalidOperationException )
				{
					return null;
				}				
			}
		}		

		private void postRecv()
		{
			bool pending = m_sock.ReceiveAsync( m_recvArgs );
			if( false == pending )
			{
				onRecvComplete( m_recvArgs, null );
			}
		}

		private void onRecvComplete( Object sender, SocketAsyncEventArgs e )
		{
			if( e.BytesTransferred <= 0 || e.SocketError != SocketError.Success )
			{
				onClose();
				return;
			}

			m_recvMem.Write( e.Buffer, e.Offset, e.BytesTransferred );

			while( true )
			{					
				if( m_recvMem.Length < HEADER_SIZE )
					break;

				uint pckLen = BitConverter.ToUInt32( m_recvMem.GetBuffer(), 0 );
				uint pckIndex = BitConverter.ToUInt32( m_recvMem.GetBuffer(), sizeof( uint ) );

				if( m_recvMem.Length < pckLen )
					break;

				Packet pck = PacketFactory.Create( pckIndex );
				m_recvMem.Position = HEADER_SIZE;
				Object tempObj = pck;
				NoobSerializeFormatter.Read( m_recvMem, ref tempObj );

				lock( m_recvPckQueue )
				{
					m_recvPckQueue.Enqueue( pck );
				}				

				m_recvMem.SetLength( m_recvMem.Length - pckLen );
				Array.Copy( m_recvMem.GetBuffer(), pckLen, m_recvMem.GetBuffer(), 0, m_recvMem.Length );
			}

			postRecv();
		}

		private void onClose()
		{
			m_sock = null;
			m_OnDisConnect();
		}

		public event ConnectFunc m_OnConnect = null;
		public event DisconnectFunc m_OnDisConnect = null;


		private SocketAsyncEventArgs m_recvArgs = null;
		private MemoryStream m_recvMem = new MemoryStream( 4096 );
		private Queue<Packet> m_recvPckQueue = new Queue<Packet>();

		private SocketAsyncEventArgs m_sendArgs = null;
		private Queue<Packet> m_sendPckQueue = new Queue<Packet>();
		MemoryStream m_sendMem = new MemoryStream( 4096 );
		private Object m_sendLock = new Object();

		private Socket m_sock = null;

		readonly int HEADER_SIZE = sizeof( uint ) * 2;
	}
}
