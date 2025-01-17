#include "pch.h"
#include "MainScene.h"
#include "ConsoleRender.h"
#include "KeyMgr.h"
#include "BattleManager.h"
#include "Player/Player.h"
#include "Monster.h" 
#include "Orc.h" 
#include "Goblin.h"
#include "Troll.h" 
#include "Slime.h"
#include "BossMonster.h"
#include "MonsterScene.h"
#include "FieldScene.h"
#include "Random.h"
#include "ShopScene.h"
#include "InventoryScene.h"
MainScene::~MainScene()
{
}

void MainScene::Start()
{
	m_vecText.push_back("1. 모험");
	m_vecText.push_back("2. 상점");
	m_vecText.push_back("3. 인벤토리");
	m_vecText.push_back("4. 게임종료");
	m_SelectMenu = 1;
}

void MainScene::Update(float DeltaTime)
{
    if (IS_TAB(KEY::W))
    {
        m_SelectMenu = m_SelectMenu > 1 ? m_SelectMenu - 1 : 1;
    }
    else if (IS_TAB(KEY::S))
    {
        uint32 size = (uint32)m_vecText.size();
        m_SelectMenu = m_SelectMenu < size ? m_SelectMenu + 1 : size;
    }
    else if (IS_TAB(KEY::SPACE))
    {
        switch ((EMainMenu)m_SelectMenu)
        {
        case EMainMenu::None:
            break;

        case EMainMenu::Field: 
        {
            CursorPos pos = Player::GetInst()->getFieldPos();
            ConsoleRender::GetInst()->CreateScene<FieldScene>();
            
            //Player* player = Player::GetInst();

            //if (player->getLevel() >= 10)
            //{
            //    RandomCreateBossMonster();
            //}
            //else
            //{
            //    RandomCreateMonster();
            //}
        }
        break;

        case EMainMenu::Store:
            ConsoleRender::GetInst()->CreateScene<ShopScene>();
            break;

        case EMainMenu::Inventory:
            // 인벤토리 추가
            ConsoleRender::GetInst()->CreateScene<InventoryScene>();
            break;

        case EMainMenu::Exit:
            std::cout << "게임을 종료합니다!" << std::endl;
            exit(0);
            break;

        default:
            break;
        }
    }
}


void MainScene::Render(float DeltaTime)
{
	HANDLE handle = ConsoleRender::GetInst()->getHandle();
	DWORD dw;
	CursorPos Pos(3,0);

	size_t size = NULL;

	for (const auto& iter : m_vecText)
	{
		SetConsoleCursorPosition(handle, Pos);
        std::wstring str = toUnicode(iter.c_str());

        WriteConsoleW(handle, str.c_str(), (DWORD)str.size(), &dw, nullptr);
		Pos.Y++;
	}
	Pos.Y = 0;
	Pos.X = 0;

    Pos.Y += (SHORT)(m_SelectMenu - 1);
	SetConsoleCursorPosition(handle, Pos);
    WriteConsoleW(handle, ">", (DWORD)1, &dw, nullptr);
}