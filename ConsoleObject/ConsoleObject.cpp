#include "pch.h"
#include "ConsoleObject.h"
#include "ConsoleRender.h"
#include "Logger.h"
ConsoleObject::ConsoleObject() :
	m_TextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY),
	m_BackGroundColor(NULL),
	m_Render(ConsoleRender::GetInst()),
	m_hConsole(NULL),
	m_vecText{},
	m_SelectMenu(NULL)
{
	
}

ConsoleObject::ConsoleObject(Scene* Owner) :
	m_TextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY),
	m_BackGroundColor(NULL),
	m_Render(ConsoleRender::GetInst()),
	m_hConsole(NULL),
	m_vecText{},
	m_SelectMenu(NULL)
{
	m_Owner = Owner;
}

ConsoleObject::ConsoleObject(ConsoleRender* Render) :
	m_TextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY),
	m_BackGroundColor(NULL),
	m_Render(Render),
	m_hConsole(NULL),
	m_vecText{},
	m_SelectMenu(NULL)
{
}

ConsoleObject::~ConsoleObject()
{

}

void ConsoleObject::init()
{
	m_TextColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	m_TextColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
}

void ConsoleObject::Update(float DeltaTime)
{
	if (m_Render == nullptr)
		m_Render = ConsoleRender::GetInst();
	m_hConsole = m_Render->getHandle();
}
void ConsoleObject::Render(float DeltaTime)
{
	if (m_vecText.empty())
		return;
	
	size_t size = m_vecText.size();
	m_Height = (uint32)size;
	DWORD dw;
	
	m_Render->SetTextColorAndBackGroundColor(m_TextColor, m_BackGroundColor);
	for (size_t i = 0; i < size; ++i)
	{
		m_Width = m_Width < (uint32)m_vecText[i].size() ? (uint32)m_vecText[i].size() : m_Width;
		SetConsoleCursorPosition(m_hConsole, CursorPos(m_CursorPos.X, m_CursorPos.Y + (SHORT)i));
		// UTF-16 출력
		DWORD written;

		std::wstring str = toUnicode(m_vecText[i]).c_str();
		if (!WriteConsoleW(m_hConsole, str.c_str(), (DWORD)str.size(), &written, NULL))
		{
			std::cerr << "Error: Failed to write to console.\n";
		}
	}
	m_Render->SetTextColorAndBackGroundColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void ConsoleObject::SetImage(MonsterType Type)
{
	m_vecText.clear();
	std::filesystem::path Path = std::filesystem::current_path();
	Path /= "Art";
	switch (Type)
	{
	case MonsterType::None:
		break;
	case MonsterType::Goblin:
		Path /= "Goblin.txt";
		break;
	case MonsterType::Orc:
		Path /= "Orc.txt";
		break;
	case MonsterType::Troll:
		Path /= "Troll.txt";
		break;
	case MonsterType::Slime:
		Path /= "Slime.txt";
		break;
	case MonsterType::Dragon:
		Path /= "Dragon.txt";
		break;
	default:
		break;
	}

	if (std::filesystem::is_regular_file(Path))
	{
		std::ifstream file(Path);
		std::string Line;
		if (file.is_open())
		{
			while (getline(file, Line))
			{
				m_vecText.push_back(Line + "\n ");
			}
			file.close();
		}
		else
		{
			CLogger::GetInst()->Log(LOG_CATEGORY::Error, "not serch aski image");
		}
	}
}

void ConsoleObject::SetImage(std::vector<std::string>& vec, const std::string& file)
{
	vec.clear();
	auto Path = std::filesystem::current_path() / "Art";
	for (auto iter : std::filesystem::directory_iterator(Path))
	{
		std::string FileName = iter.path().filename().string();
		if ((FileName == file + ".txt" || FileName == file + ".txt.txt") && iter.path().extension() == ".txt")
		{
			std::ifstream file(iter.path());
			std::string Line = "";
			if (file.is_open())
			{
				while (getline(file, Line))
				{
					vec.push_back(Line + "\n ");
				}
				file.close();
			}
		}
	}
}
void ConsoleObject::SetImage(std::vector<std::wstring>& vec, const std::string& file)
{
	vec.clear();
	auto Path = std::filesystem::current_path() / "Art";
	for (auto iter : std::filesystem::directory_iterator(Path))
	{
		std::string FileName = iter.path().filename().string();
		if ((FileName == file + ".txt" || FileName == file + ".txt.txt") && iter.path().extension() == ".txt")
		{
			std::ifstream file(iter.path());
			std::string Line = "";
			if (file.is_open())
			{
				while (getline(file, Line))
				{
					vec.push_back(toUnicode(Line) + L"\n ");
				}
				file.close();
			}
		}
	}
}

void ConsoleObject::SetScene(Scene* Scene)
{
	m_Owner = Scene;
}

void ConsoleObject::SetMonster(Monster* _Monster)
{
	m_Monster = _Monster;
}

const uint32 ConsoleObject::getWidth()
{
	if (m_vecText.empty())
		return 0;

	uint32 max = 0;
	for (const auto& iter : m_vecText)
	{
		max = iter.size() > max ? iter.size() : max;
	}
	return max;
	
}

const uint32 ConsoleObject::getHeight()
{
	if (m_vecText.empty())
		return 0;

	return m_vecText.size();
}
