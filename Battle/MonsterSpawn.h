#pragma once
#include "Monster.h"


class MonsterSpawn
{
public:
    static MonsterSpawn& getInstance()
    {
        static MonsterSpawn instance;
        return instance;
    }

public:
    vector<Monster> StageSpawner(int _stage);



private:
    MonsterSpawn();
    // 복사/대입도 막음
    MonsterSpawn(const MonsterSpawn&) = delete;
    MonsterSpawn& operator=(const MonsterSpawn&) = delete;

};
