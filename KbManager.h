#pragma once
class KbManager
{
public:
	static WPARAM kb_message;
	static void SetKbmessage(WPARAM);
	static bool isSpaceDown();
	static bool isLeftArrowDown();
	static bool isRightArrowDown();
	static bool isAKeyDown();
	static bool isZKeyDown();
	static bool isActionKeyDown();
};
