using System;
using System.Collections.Generic;


[Noob.NoobSerializAble]
public class N_Move : Noob.Packet
{
	public uint playerIndex = 0;
	public PlayerTransform transform = new PlayerTransform();
	public PlayerAnimation animation = new PlayerAnimation();

	public override uint GetIndex(){ return index; }
	public const uint index = 101;
}

[Noob.NoobSerializAble]
public class N_Roll : Noob.Packet
{
	public uint playerIndex = 0;
	public float degree = 0.0f;

	public override uint GetIndex(){ return index; }
	public const uint index = 102;
}

[Noob.NoobSerializAble]
public class N_Chat : Noob.Packet
{
	public uint playerIndex = 0;
	public string message = "";

	public override uint GetIndex(){ return index; }
	public const uint index = 103;
}
