#pragma once
class Scene;

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	GameManager(GameManager&) = delete;
	virtual ~GameManager() override;
public:
	bool init();
	unsigned int Run();
	void GameEnd();
	void Cicle();
private:
	void Update(float DeltaTime);
	void Render(float DeltaTime);
private:
	bool                   m_GameEnd;
	class BattleManager*   m_BattleManager;
	class StoreManager*    m_StoreManager;
	class ConsoleRender*   m_ConsoleRender;
	class Player*          m_Player;
};

