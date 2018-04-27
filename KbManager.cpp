#include "stdafx.h"
#include "KbManager.h"

WPARAM KbManager::kb_message = 0;
void KbManager::SetKbmessage(WPARAM wparam)
{
	kb_message = wparam;
}

bool KbManager::isSpaceDown()
{
	if(kb_message== VK_SPACE)
	{
		kb_message = 0;
		return true;
	}
	else
		return false;
}
