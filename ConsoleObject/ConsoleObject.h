#pragma once
class CConsoleRender;

class ConsoleObject
{
protected:
	friend class ConsoleRender;
protected:
	ConsoleObject();
	//ConsoleObject(const ConsoleObject&) = delete;
	ConsoleObject(class Scene* Owner);
	ConsoleObject(class ConsoleRender* Render);
public:
	virtual ~ConsoleObject();
protected:
	virtual void init();
public:
	virtual void Update(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual void SetImage(std::vector<std::string>& vec,const std::string& Name);
	virtual void SetImage(std::vector<std::wstring>& vec,const std::string& Name);
	virtual void SetImage(MonsterType Type);

protected:
	CursorPos                m_CursorPos;
	std::vector<std::string> m_vecText;
	class ConsoleRender*	 m_Render;
	HANDLE                   m_hConsole;
	WORD                     m_TextColor;
	WORD                     m_BackGroundColor;
	int                      m_SelectMenu;
	class Scene*             m_Owner;
	class Monster*           m_Monster;
	uint32                   m_Width;
	uint32                   m_Height;
	float                    m_Time;
	bool                     m_Reverse;
public:
	void SetScene(class Scene* Scene);
	void SetTextColor(const WORD& Color) { m_TextColor = Color; }
	void SetTextBackGroundColor(const WORD& Color) { m_BackGroundColor = Color; }
	void SetCursorPos(const CursorPos& Pos) { m_CursorPos = Pos; }
	virtual void SetMonster(class Monster* _Monster);
public:
	const CursorPos& GetCursorPos() const { return m_CursorPos; }
	size_t GetCursorY() const { return m_vecText.size(); }
	const uint32 getWidth();
	const uint32 getHeight();
};

