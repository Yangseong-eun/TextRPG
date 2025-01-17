#include "pch.h"
#include "MonsterScene.h"
#include "./Scene/MainScene.h"
#include "BossMonster.h"
#include <iostream>

MonsterScene::MonsterScene(Player* player, Monster* monster)
    : m_Player(player), m_Monster(monster), m_IsBattleEnd(false) {
}

MonsterScene::~MonsterScene() {}

void MonsterScene::Start() {
    ConsoleRender::GetInst()->ScreenClear();
    std::cout << "몬스터가 나타났습니다: " << m_Monster->getName() << "!" << std::endl;
    std::cout << "전투를 시작합니다!" << std::endl;
}

void MonsterScene::Update(float DeltaTime)
{
    if (m_IsBattleEnd) {
        // 전투 종료 처리
        if (dynamic_cast<BossMonster*>(m_Monster) != nullptr) {
            // 보스 몬스터가 패배했을 경우
            std::cout << "축하합니다! 보스를 물리쳤습니다!" << std::endl;
            ConsoleRender::GetInst()->CreateScene(std::make_unique<MainScene>()); // 엔딩이 아닌 메인 화면으로 복귀
        }
        else {
            ConsoleRender::GetInst()->CreateScene(std::make_unique<MainScene>());
        }
        return;
    }

    std::cout << "1. 공격  2. 아이템 사용  3. 도망" << std::endl;

    int action;
    std::cin >> action;

    switch (action) {
    case 1: // 공격
        m_Monster->takeDamage(m_Player->getAtk());
        std::cout << m_Player->getName() << "이(가) " << m_Monster->getName() << "에게 "
            << m_Player->getAtk() << "의 데미지를 입혔습니다!" << std::endl;

        if (m_Monster->getHealth() <= 0) {
            std::cout << m_Monster->getName() << "을(를) 물리쳤습니다!" << std::endl;

            // 전투 보상 지급
            if (dynamic_cast<BossMonster*>(m_Monster) != nullptr) {
                // 보스 몬스터 보상

                std::cout << "보스를 물리치고 코딩의 수호자 칭호를 획득했습니다!" << std::endl;
            }
            else {
                // 일반 몬스터 보상
                m_Player->addGold(50);
                m_Player->addExp(30);
                std::cout << "일반 몬스터를 처치하고 50 골드와 경험치를 획득했습니다!" << std::endl;
            }
            m_Player->levelUp();

            m_IsBattleEnd = true;
        }
        else {
            // 몬스터 반격
            m_Player->takeDamage(m_Monster->getAttackPower());
            std::cout << m_Monster->getName() << "이(가) 반격하여 "
                << m_Monster->getAttackPower() << "의 데미지를 입혔습니다!" << std::endl;

            if (m_Player->getCurrHealth() <= 0) {
                std::cout << "플레이어가 사망했습니다. 게임 오버!" << std::endl;
                m_IsBattleEnd = true; // 전투 종료
            }
        }
        break;

    case 2: // 아이템 사용
        // TODO: 아이템 사용 로직
        break;

    case 3: // 도망
        if (dynamic_cast<BossMonster*>(m_Monster) != nullptr) {
            std::cout << "보스 몬스터와의 전투에서 도망칠 수 없습니다!" << std::endl;
        }
        else {
            std::cout << "도망쳤습니다!" << std::endl;
            m_IsBattleEnd = true; // 전투 종료
        }
        break;

    default:
        std::cout << "잘못된 입력입니다!" << std::endl;
        break;
    }
}

void MonsterScene::Render(float DeltaTime) {
    ConsoleRender::GetInst()->ScreenClear();
    std::cout << "==== 전투 상황 ====" << std::endl;
    std::cout << "플레이어 체력: " << m_Player->getCurrHealth() << " / " << m_Player->getMaxHealth() << std::endl;
    std::cout << "몬스터 체력: " << m_Monster->getHealth() << std::endl;
    std::cout << "플레이어 골드: " << m_Player->getGold() << std::endl;
}
