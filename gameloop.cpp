#include "pch.h"
#include <iostream>
#include <windows.h>
#include "Monster.h"
#include "Slime.h" // Slime 몬스터 클래스 포함

void gameLoop(Monster& monster) {
    while (monster.getHealth() > 0) {
        system("cls"); // 화면 지우기
        std::cout << "몬스터 등장!" << std::endl;
        monster.displayArt();
        std::cout << "체력: " << monster.getHealth() << std::endl;
        std::cout << "공격력: " << monster.getAttackPower() << std::endl;

        std::cout << "\n1. 공격  2. 도망가기" << std::endl;
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            monster.takeDamage(15); // 플레이어가 15의 데미지를 줌
            std::cout << "\n몬스터를 공격했다! 체력 감소!" << std::endl;
        }
        else if (choice == 2) {
            std::cout << "\n플레이어가 도망갔습니다!" << std::endl;
            break;
        }
        else {
            std::cout << "\n잘못된 선택입니다." << std::endl;
        }

        Sleep(1000); // 1초 대기
    }

    if (monster.getHealth() <= 0) {
        std::cout << "\n몬스터를 처치했다!" << std::endl;
    }
}

int main() {
    Slime slime(5); // 레벨 5의 슬라임 생성
    gameLoop(slime);
    return 0;
}
