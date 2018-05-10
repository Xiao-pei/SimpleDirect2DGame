#include "stdafx.h"
#include "KbManager.h"

WPARAM KbManager::kb_message = 0;

void KbManager::SetKbmessage(WPARAM wparam)
{
	kb_message = wparam;
}

bool KbManager::isSpaceDown()
{
	if (kb_message == VK_SPACE)
	{
		kb_message = 0;
		return true;
	}
	else
		return false;
}

bool KbManager::isLeftArrowDown()
{
	if (kb_message == VK_LEFT)
	{
		kb_message = 0;
		return true;
	}
	else
		return false;
}

bool KbManager::isRightArrowDown()
{
	if (kb_message == VK_RIGHT)
	{
		kb_message = 0;
		return true;
	}
	else
		return false;
}

bool KbManager::isAKeyDown()
{
	if (kb_message == 0x41)
	{
		kb_message = 0;
		return true;
	}
	else
		return false;
}

bool KbManager::isZKeyDown()
{
	if (kb_message == 0x5A)
	{
		kb_message = 0;
		return true;
	}
	else
		return false;
}
