#include "fakelag.h"

bool Settings::FakeLag::enabled = false;

static int ticks = 0;
int ticksMax = 16;

void FakeLag::CreateMove(CUserCmd* cmd)
{
	if (!Settings::FakeLag::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (cmd->buttons & IN_ATTACK)
	{
		*bSendPacket = true;
		return;
	}

	if (ticks == ticksMax)
	{
		*bSendPacket = true;
		ticks = 0;
	}
	else
	{
		*bSendPacket = ticks < 5;
	}

	ticks++;
}