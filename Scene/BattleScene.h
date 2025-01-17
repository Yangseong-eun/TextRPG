#pragma once
#include "Scene.h"
class BattleScene :
    public Scene
{
public:
	BattleScene();
	BattleScene(class Monster* Monster);
private:
	class ConsoleRender* m_Render;
	class Monster*       m_Monster;
	class Player*        m_Player;
	std::string			 m_ItemName;
	float m_Time =0.f;
	float m_TimeMax = 1.f;
	bool m_bChangeFlag = false;
public:
	size_t GetCursorY(EBattleObjectType Obj);
public:
	virtual void Start() override;
	virtual void Update(float DeltaTime) override;
	virtual void Render(float DeltaTime) override;
public:
	void SetMonster(class Monster* Monster);
public:
	void Fight();
	void useItem();
	void runAway();
};

