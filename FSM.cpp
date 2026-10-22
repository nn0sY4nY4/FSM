#include <iostream>
#include <cmath>
using namespace std;

enum Status {
    patrol,
    chase,
    attack,
    running,
};

struct Character {
    float x;
    float y;
    int HP;
};

struct Guard {
    Status status = patrol;
    float chaseDistance = 4.f;
    float attackDistance = 1.f;
};

float getDistance(const Character& guard,
    const Character& player) {
    float dx = guard.x - player.x;
    float dy = guard.y - player.y;

    return sqrt(dx * dx + dy * dy);
}

void update(Guard& guard,
    const Character& guardCharacter,
    const Character& player) {
    float dist = getDistance(guardCharacter, player);

    if (guardCharacter.HP < player.HP) {
        guard.status = running;
        return;
    }

    switch (guard.status) {
    case patrol:
        if (dist <= guard.chaseDistance)
            guard.status = chase;
        break;

    case chase:
        if (dist <= guard.attackDistance)
            guard.status = attack;
        else if (dist > guard.chaseDistance)
            guard.status = patrol;
        break;

    case attack:
        if (dist > guard.chaseDistance)
            guard.status = patrol;
        else if (dist > guard.attackDistance)
            guard.status = chase;
        break;

    case running:
        guard.status = patrol;
        break;
    }
}

const char* getStatusName(Status status) {
    switch (status) {
    case patrol:   return "patrol";
    case chase:    return "chase";
    case attack:   return "attack";
    case running:  return "running";
    }

    return "ERROR";
}

int main() {
    Guard guard;

    Character player{ 0.f, 0.f, 100 };
    Character guardCharacter{ 0.f, 0.f, 100 };

    float distances[] = { 8, 4, 2, 1, 3, 7 };

    for (float dist : distances) {
        guardCharacter.x = dist;

        update(guard, guardCharacter, player);

        if (guard.status == attack) {
            player.HP -= 10;

            if (player.HP < 0)
                player.HP = 0;
        }

        cout << "Dist: " << dist
            << " | Guard HP: " << guardCharacter.HP
            << " | Player HP: " << player.HP
            << " | Status: " << getStatusName(guard.status)
            << '\n';
    }

    return 0;
}