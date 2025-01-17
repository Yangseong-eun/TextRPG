#pragma once
#include "ConsoleObject.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>

class StagePrint : public ConsoleObject {
private:
    std::string m_FilePath;              // 텍스트 파일 경로
    bool m_IsStageLoaded;                // 단계별 텍스트가 로드되었는지 확인

public:
    StagePrint(Scene* Owner);
    virtual ~StagePrint() = default;

    void loadStageText(int stage);       // 단계에 따라 텍스트 파일 로드
    void renderStageText();              // 텍스트 화면 출력
};