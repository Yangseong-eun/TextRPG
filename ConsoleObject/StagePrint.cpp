#include "pch.h"
#include "StagePrint.h"
#include "ConsoleRender.h"

StagePrint::StagePrint(Scene* Owner) : ConsoleObject(Owner), m_IsStageLoaded(false) {}

void StagePrint::loadStageText(int stage) {
    m_vecText.clear();

    // 단계에 따른 파일 경로 설정
    std::filesystem::path path = std::filesystem::current_path() / "Stages";
    switch (stage) {
    case 1:
        path /= "C++.txt";
        break;
    case 2:
        path /= "Unreal.txt";
        break;
    case 3:
        path /= "Blueprint.txt";
        break;
    case 4:
        path /= "BossMonster.txt";
        break;
    default:
        m_IsStageLoaded = false;
        return;
    }

    m_FilePath = path.string();

    // 파일 읽기
    if (std::filesystem::is_regular_file(path)) {
        std::ifstream file(path);
        std::string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                m_vecText.push_back(line);
            }
            file.close();
            m_IsStageLoaded = true;
        }
    }
    else {
        m_IsStageLoaded = false;
    }
}

void StagePrint::renderStageText() {
    if (!m_IsStageLoaded || m_vecText.empty())
        return;

    m_hConsole = m_Render->getHandle();
    DWORD written;

    for (size_t i = 0; i < m_vecText.size(); ++i) {
        COORD position = { m_CursorPos.X, (SHORT)(m_CursorPos.Y + i) };
        SetConsoleCursorPosition(m_hConsole, position);
        std::wstring str = toUnicode(m_vecText[i]);
        WriteConsoleW(m_hConsole, str.c_str(), (DWORD)str.size(), &written, NULL);
    }

}