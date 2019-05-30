#pragma once

#include<NoobNetwork/PacketRegister.h>
#include"Login.h"

REGISTER_PACKET( SC_Hello );
REGISTER_PACKET( CS_Hello );
REGISTER_PACKET( CS_Login );
REGISTER_PACKET( SC_Login );
REGISTER_PACKET( SC_EnterPlayer );
REGISTER_PACKET( SC_ExitPlayer );
