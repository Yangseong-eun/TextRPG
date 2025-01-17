#include <pch.h>
#include "Manager/GameManager.h"

BOOL WINAPI ConsoleHandler(DWORD signal) 
{
	if (signal == CTRL_CLOSE_EVENT) {

		GameManager::GetInst()->GameEnd();

		return TRUE; // 시스템에 신호를 처리했음을 알림
	}
	return FALSE;
}
int main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	SetConsoleCtrlHandler(ConsoleHandler, TRUE);
	SetConsoleOutputCP(CP_UTF8);

	int retVal = NULL;
	std::string mode = "mode con: cols=" + std::to_string(ConsoleWidth) + " lines=" + std::to_string(ConsoleHeight);
	system(mode.c_str());
	system("title Code-Cronos");
	if (GameManager::GetInst()->init())
		retVal = GameManager::GetInst()->Run();

	return retVal;
}