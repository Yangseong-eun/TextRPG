#include "pch.h"
#include "ShopScene.h"
#include "DisplayItems.h"
#include "Item/Item.h"
#include "KeyMgr.h"
#include "ConsoleRender.h"
#include "MainScene.h"
DisplayItems::DisplayItems(Scene* Scene) :
	ConsoleObject(Scene)
{
	m_Shop = dynamic_cast<ShopScene*>(m_Owner);
	m_vecItem = m_Shop->GetItems();

	for (const auto& item : m_vecItem)
	{
		m_vecText.push_back(item->getName());
		m_vecPrice.push_back(std::to_string(item->getPrice()));
	}
	
	m_SelectString.push_back("산다");
	m_SelectString.push_back("판다");
	m_SelectString.push_back("취소");

	m_CursorPos = { 60, 10};
	m_SelectMenu = 1;
	m_SelectShop = 0;
	m_bSelect = false;
}

void DisplayItems::Update(float DeltaTime)
{
	ConsoleObject::Update(DeltaTime);
	if (!m_bSelect)
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
			m_bSelect = true;
			
		}
		else if (IS_TAB(KEY::ENTER))
		{
			ConsoleRender::GetInst()->CreateScene<MainScene>();
		}
	}
	else
	{
		if (IS_TAB(KEY::A))
		{
			m_SelectShop = m_SelectShop > 0 ? m_SelectShop - 1 : 0;
		}
		else if (IS_TAB(KEY::D))
		{
			uint32 size = (uint32)m_SelectString.size();
			m_SelectShop = m_SelectShop < size-1 ? m_SelectShop + 1 : size-1;
		}
		else if (IS_TAB(KEY::SPACE))
		{
			switch (m_SelectShop)
			{
			case 0 : 
				m_Shop->buyItem(m_vecItem[m_SelectMenu-1]->getName());
				break;
			case 1:
				m_Shop->sellItem(m_vecItem[m_SelectMenu - 1]->getName());
				break;
			case 2:
				m_bSelect = false;
				m_SelectMenu = 1;
				break;
			default:
				break;
			}
		}
	}
}

void DisplayItems::Render(float DeltaTime)
{
	ConsoleObject::Render(DeltaTime);
	DWORD writeln;
	int count = 0;
	for (const auto& iter : m_vecPrice)
	{
		std::wstring wstr = toUnicode(iter);
		SetConsoleCursorPosition(m_hConsole, CursorPos(m_CursorPos.X + 10, m_CursorPos.Y + count));
		WriteConsoleW(m_hConsole, wstr.c_str(), (DWORD)wstr.size(), &writeln, NULL);
		++count;
	}
	SetConsoleCursorPosition(m_hConsole, CursorPos(m_CursorPos.X - 1, m_CursorPos.Y + m_SelectMenu-1));
	WriteConsoleW(m_hConsole, L">", (DWORD)1, &writeln, NULL);

	if (m_bSelect)
	{
		count = 0;
		int width = m_CursorPos.X - 40+1;
		const int blank = 3;
		for (const auto& iter : m_SelectString)
		{
			std::wstring wstr = toUnicode(iter);
			// 기본 위치 + 글자사이즈 
			
			SetConsoleCursorPosition(m_hConsole, CursorPos(width+count, m_CursorPos.Y + 20));
			WriteConsoleW(m_hConsole, wstr.c_str(), (DWORD)wstr.size(), &writeln, NULL);
			width += wstr.size() + blank;
			++count;
		}
		width = m_CursorPos.X - 40 + m_SelectShop * (blank + 3);
		SetConsoleCursorPosition(m_hConsole, CursorPos(width, m_CursorPos.Y + 20));
		WriteConsoleW(m_hConsole, L">", (DWORD)1, &writeln, NULL);
	}
}
