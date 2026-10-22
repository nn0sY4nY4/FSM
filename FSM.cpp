#include <iostream>
using namespace std;

enum Status {
    patrol,
    chase,
    attack,
    running,
};

struct Player {
    int HP;
};

struct Guard {
    int HP;
    Status status = patrol;
    float chaseDistance = 4.f;
    float attackDistance = 1.f;
    float runDistance = 8.f;
};

void update(Guard& guard, float dist, Player& player) {
    switch (guard.status) {
    case patrol:
        if (dist <= guard.chaseDistance)
            guard.status = chase;
        break;

    case chase:
        if (guard.HP < player.HP)
            guard.status = running;
        else if (dist <= guard.attackDistance)
            guard.status = attack;
        else if (dist > guard.chaseDistance)
            guard.status = patrol;
        break;

    case attack:
        if (guard.HP < player.HP)
            guard.status = running;
        else if (dist > guard.chaseDistance)
            guard.status = patrol;
        else if (dist > guard.attackDistance)
            guard.status = chase;
        break;

    case running:
        if (dist >= guard.runDistance)
            guard.status = patrol;
        break;
    }
}

void printStatus(Status status) {
    switch (status) {
    case patrol:  cout << "patrol"; break;
    case chase:   cout << "chase"; break;
    case attack:  cout << "attack"; break;
    case running: cout << "running"; break;
    }
}

int main() {
    Player player{ 100 };
    Guard guard{ 120 };

    float distances[] = { 8, 4, 2, 1, 1, 3, 7, 9, 10, 5, 3, 1 };

    for (float dist : distances) {
        update(guard, dist, player);

        if (guard.status == attack) {
            player.HP -= 10;
            guard.HP -= 13;
        }

        cout << "Dist: " << dist
            << " | Guard HP: " << guard.HP
            << " | Player HP: " << player.HP
            << " | Status: ";

        printStatus(guard.status);
        cout << '\n';
    }

    return 0;
}