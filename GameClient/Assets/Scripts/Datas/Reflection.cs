using System;
using System.Collections.Generic;


[Noob.NoobSerializAble]
public enum PLAYER_STATE : uint
{
	STOP,
	RUN,
	DEAD,
	__MAX__
}

[Noob.NoobSerializAble]
public class PlayerTransform
{
	public UnityEngine.Vector2 position = new UnityEngine.Vector2();
	public UnityEngine.Vector2 velocity = new UnityEngine.Vector2();
}

[Noob.NoobSerializAble]
public class PlayerAnimation
{
	public PLAYER_STATE state = new PLAYER_STATE();
}
