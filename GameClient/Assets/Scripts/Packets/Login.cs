using System;
using System.Collections.Generic;


[Noob.NoobSerializAble]
public class SC_Hello : Noob.Packet
{
	public override uint GetIndex(){ return index; }
	public const uint index = 2;
}

[Noob.NoobSerializAble]
public class CS_Hello : Noob.Packet
{
	public override uint GetIndex(){ return index; }
	public const uint index = 3;
}

[Noob.NoobSerializAble]
public class CS_Login : Noob.Packet
{
	public string nick = "";

	public override uint GetIndex(){ return index; }
	public const uint index = 4;
}

[Noob.NoobSerializAble]
public class SC_Login : Noob.Packet
{
	public uint playerIndex = 0;
	public UnityEngine.Vector2 spawnPosition = new UnityEngine.Vector2();

	public override uint GetIndex(){ return index; }
	public const uint index = 5;
}

[Noob.NoobSerializAble]
public class SC_EnterPlayer : Noob.Packet
{
	public uint playerIndex = 0;
	public string nick = "";
	public PlayerTransform transform = new PlayerTransform();
	public PlayerAnimation animation = new PlayerAnimation();
	public float degree = 0.0f;

	public override uint GetIndex(){ return index; }
	public const uint index = 6;
}

[Noob.NoobSerializAble]
public class SC_ExitPlayer : Noob.Packet
{
	public uint playerIndex = 0;

	public override uint GetIndex(){ return index; }
	public const uint index = 7;
}
