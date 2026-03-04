#pragma once
#include <array>
#include <vector>

// 

class modelsDirectory
{
public:
    std::vector<Model> models{};
};

namespace Globals
{
    modelsDirectory mDirectory{};
}

class Player
{
private:
    std::array<double, 3> m_pos{};
    int m_health{100};

public:
    std::array<double, 3> getPos() const
    {
        return m_pos;
    }

    void changeHealth(int value, bool add)
    {
        if (add)
        {
            m_health += value;
        }
        else
        {
            m_health -= value;
        }
    }
};


class Game
{
private:
    Player m_player{};

    int difficultyLevel{};
public:
    Player& getPlayer()
    {
        return m_player;
    }

    void render(Model)
    {

    }
};


class Model
{

};

//

class Monster
{
public:
    enum Type
    {
        drowner,
        ghoul,
        troll,
        wraith,
        golem,
        wyvern,
        barghest,
        werewolf
    };

    enum State
    {
        idle,
        alerted,
        agressive
    };
private:
    static inline int s_id{ 1 };

    const int m_id{ s_id++ };
    
    Type m_type{};

    std::array<double, 3> m_pos{};

    int m_health{};

    int m_damage{};

    int m_movementSpeed{};

    State m_state{};
    
    Model m_model{};

    const int m_renderDistance{ 10000 };

    const int m_alarmDistance{ 150 };

    const int m_agressiveDistance{ 70 };

public:
    Monster(Type, std::array<double, 3>);

    ~Monster() {};

    Monster(const Monster&);

    Monster& operator=(const Monster&);

    void render(Game&) const;

    void move(Game&, std::array<double, 3>);

    void attack(Game&) const;

    void changeState(Game&);

    Type getType() const
    {
        return m_type;
    }

    int getHealth() const
    {
        return m_health;
    }

    int getDamage() const
    {
        return m_damage;
    }

    int getMS() const
    {
        return m_movementSpeed;
    }

    State getState() const
    {
        return m_state;
    }

    Model getModel() const
    {
        return m_model;
    }

    std::array<double, 3> getPos() const
    {
        return m_pos;
    }

};
