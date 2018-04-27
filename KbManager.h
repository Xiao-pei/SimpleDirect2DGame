#pragma once
class KbManager
{
public:
	static WPARAM kb_message;
	static void SetKbmessage(WPARAM );
	static bool isSpaceDown();
};

