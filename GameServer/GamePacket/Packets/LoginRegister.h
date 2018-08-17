#pragma once

#include<NoobNetwork\PacketRegister.h>
#include"Login.h"

REGIST_PACKET( SC_Hello );
REGIST_PACKET( CS_Hello );
REGIST_PACKET( CS_Login );
REGIST_PACKET( SC_Login );
REGIST_PACKET( SC_NewPlayer );
REGIST_PACKET( SC_Ping );
REGIST_PACKET( CS_Ping );
