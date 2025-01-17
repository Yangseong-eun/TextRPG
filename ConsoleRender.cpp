#include "pch.h"
#include "ConsoleRender.h"
#include "ConsoleObject.h"
#include "KeyMgr.h"
#include "Scene.h"
ConsoleRender::ConsoleRender() :
    m_Console{},
    m_cci{},
    m_Pos{}
{
}

ConsoleRender::~ConsoleRender()
{
    ScreenRelease();
}

bool ConsoleRender::Init()
{
    ScreenInit();
    return true;
}


void ConsoleRender::Update(float DeltaTime)
{
    m_Scene->Update(DeltaTime);
    CKeyMgr::GetInst()->update(getHandle());
}

void ConsoleRender::Render(float DeltaTime)
{
    ScreenClear();
    m_Scene->Render(DeltaTime);
    ScreenFlipping();
}

void ConsoleRender::SetTextColorAndBackGroundColor(WORD foregroundColor, WORD backgroundColor)
{
    WORD colorAttribute = foregroundColor | backgroundColor;
    SetConsoleTextAttribute(m_Console.hBuffer[m_Console.nBufferIdx], colorAttribute);
}

std::string ConsoleRender::InputText(const std::string& text)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    //HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hOutput2 = m_Console.hBuffer[m_Console.nBufferIdx];

    SetConsoleActiveScreenBuffer(hOutput2);
    if (hInput == INVALID_HANDLE_VALUE || hOutput2 == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error: Invalid console handle." << std::endl;
        return "Error: Invalid console handle.";
    }

    configureConsoleForRawInput(hInput);

    char inputBuffer[1024] = {};
    int bufferEnd = 0;
    DWORD bytesRead;
    std::string inputText = "";
    
    PrintText(hOutput2, text);
    while (inputBuffer[bufferEnd] == '\0')
    {
        //Render(0.f);
        PrintText(hOutput2, inputBuffer);
        // Read input
        if (ReadFile(hInput, inputBuffer, sizeof(inputBuffer) - 1, &bytesRead, NULL) && bytesRead > 0) 
        {
            inputBuffer[bytesRead] = '\0'; // Null-terminate input
            if (strchr(inputBuffer, '\r'))
            {
                inputText += '\0';
                PrintText(hOutput2, "\n");
                break;
            }
            else if(strchr(inputBuffer, '\b'))
            {
                if (inputText.size() > 0) inputText.pop_back();
            }
            else
                inputText += std::string(inputBuffer);
        }
        else {
            std::cerr << "Error: ReadFile failed." << std::endl;
            break;
        }
    }
    static std::unordered_set<char> escapeChars = { '\r', '\b', '\f', '\n', '\t', '\\' };
    std::string result;
    for (size_t i = 0; i < inputText.size(); ++i)
    {
        if (!escapeChars.count(inputText[i])) 
        {
            result += inputText[i];
        }
    }
    return result;
}

void ConsoleRender::configureConsoleForRawInput(HANDLE hInput)
{
    DWORD mode;
    if (!GetConsoleMode(hInput, &mode)) 
    {
        std::cerr << "Error: Could not get console mode." << std::endl;
        return;
    }

    // Disable line buffering and echo
    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    if (!SetConsoleMode(hInput, mode)) 
    {
        std::cerr << "Error: Could not set console mode." << std::endl;
    }
}

Scene* ConsoleRender::GetScene() const
{
    return m_Scene.get();
}

void ConsoleRender::ScreenInit()
{
    m_cci.dwSize = 1;       // �����?����
    m_cci.bVisible = FALSE; //�ܼ� �����?

    m_Console.hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    m_Console.nBufferIdx = 0;

    m_Console.hInput = GetStdHandle(STD_INPUT_HANDLE);

    CONSOLE_CURSOR_INFO consoleCursor{ 1, FALSE };  // �ܼ��� Ŀ�� �������?�����մϴ�.
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo{};
    GetConsoleScreenBufferInfo(m_Console.hConsole, &consoleInfo);
    consoleInfo.dwSize.X = ConsoleWidth;                   
    consoleInfo.dwSize.Y = ConsoleHeight;                    
    consoleInfo.srWindow.Right = consoleInfo.dwSize.X - 1;
    consoleInfo.srWindow.Bottom = consoleInfo.dwSize.Y - 1;
    m_Console.rtConsole.nWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left;
    m_Console.rtConsole.nHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top;

    SetConsoleScreenBufferSize(m_Console.hInput, consoleInfo.dwSize);
    SetConsoleWindowInfo(m_Console.hInput, TRUE, &consoleInfo.srWindow);

    SetConsoleScreenBufferSize(m_Console.hConsole, consoleInfo.dwSize);
    SetConsoleWindowInfo(m_Console.hConsole, TRUE, &consoleInfo.srWindow);

    m_Console.hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleScreenBufferSize(m_Console.hBuffer[0], consoleInfo.dwSize);    
    SetConsoleWindowInfo(m_Console.hBuffer[0], TRUE, &consoleInfo.srWindow); 
    SetConsoleCursorInfo(m_Console.hBuffer[0], &consoleCursor);              

    m_Console.hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleScreenBufferSize(m_Console.hBuffer[1], consoleInfo.dwSize);
    SetConsoleWindowInfo(m_Console.hBuffer[1], TRUE, &consoleInfo.srWindow);
    SetConsoleCursorInfo(m_Console.hBuffer[1], &consoleCursor);
}

void ConsoleRender::ScreenFlipping()
{    
    SetConsoleActiveScreenBuffer(m_Console.hBuffer[m_Console.nBufferIdx]);
    m_Console.nBufferIdx = (int)!m_Console.nBufferIdx;
}

void ConsoleRender::PrintText(HANDLE hOutput, const std::string& string)
{
    DWORD dw;
    WriteFile(m_Console.hBuffer[m_Console.nBufferIdx], string.c_str(), (DWORD)string.size(), &dw, NULL);
}

void ConsoleRender::ScreenClear()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo{};
    GetConsoleScreenBufferInfo(m_Console.hBuffer[m_Console.nBufferIdx], &consoleInfo);

    COORD pos{};
    DWORD dwWritten = 0;
    unsigned size = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;

    FillConsoleOutputCharacter(m_Console.hBuffer[m_Console.nBufferIdx], ' ', size, pos, &dwWritten);
    SetConsoleCursorPosition(m_Console.hBuffer[m_Console.nBufferIdx], pos);
}

void ConsoleRender::ScreenAllClear()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo{};
    GetConsoleScreenBufferInfo(m_Console.hBuffer[m_Console.nBufferIdx], &consoleInfo);

    COORD pos{};
    DWORD dwWritten = 0;
    unsigned size = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;
    
    for (int i = 0; i < 2;++i)
    {
        FillConsoleOutputCharacter(m_Console.hBuffer[i], ' ', size, pos, &dwWritten);
        SetConsoleCursorPosition(m_Console.hBuffer[i], pos);
    }

}

void ConsoleRender::setCursorPosition(const short x, const short y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(m_Console.hBuffer[m_Console.nBufferIdx], pos);
}

void ConsoleRender::ScreenRelease()
{
    if (m_Console.hBuffer[0])
    {
        CloseHandle(m_Console.hBuffer[0]);
    }
    if (m_Console.hBuffer[1])
    {
        CloseHandle(m_Console.hBuffer[1]);
    }
}

void ConsoleRender::ScreenPrint(const std::string& str)
{
    DWORD dw;
    WriteFile(m_Console.hBuffer[m_Console.nBufferIdx], str.c_str(), (DWORD)str.size(), &dw, NULL);
}
void ConsoleRender::ScreenPrintln(const std::string& str)
{
    DWORD dw;
    std::string result = str.c_str();
    result +="\n";
    WriteFile(m_Console.hBuffer[m_Console.nBufferIdx], result.c_str(), (DWORD)result.size(), &dw, NULL);
}

void ConsoleRender::CreateScene(std::unique_ptr<class Scene> Scene)
{
    if (m_NextScene.get())
        m_NextScene.reset();

    m_NextScene = std::move(Scene);
    m_NextScene->Start();
    m_ChangeFlag = true;
}

bool ConsoleRender::ChangeScene()
{
    if (m_NextScene.get())
    {
        if(m_Scene.get())
            m_Scene.reset();

        m_Scene = std::move(m_NextScene);
        return true;
    }
    return false;
}
