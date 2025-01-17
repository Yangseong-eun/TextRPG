#include "pch.h"
#include <iostream>
#include "Goblin.h"

int main() {
    // 플레이어 레벨 5에 해당하는 Goblin 객체 생성
    Goblin goblin(5);

    // Goblin ASCII Art 출력
    std::cout << "Goblin이 등장했습니다!" << std::endl;
    goblin.displayArt();

    return 0;
}
