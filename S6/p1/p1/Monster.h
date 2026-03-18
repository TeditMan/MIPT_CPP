#pragma once
#include <array>

// Выбранный объект - противник в рамках какой-нибудь игры (например, Witcher 3)
// Основной функционал - взаимодействие с игроком (нанесение урона, изменение состояния в зависимости от относительного расположения с игроком),
// взаимодействие с движком игры (перемещение, рендер), а также базовые вещи типа геттера и конструктора

// Несколько служебных классов для того, чтобы реализация методов имела какой-то смысл

class Model
{
    int a{};
};

class modelsDirectory
{
public:
    std::array<Model, 5> models{};
};

namespace Globals
{
    inline modelsDirectory mDirectory{};
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

    int getHealth() const
    {
        return m_health;
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
    Game(Player player, int dLevel)
        :m_player{player}
    {
        switch (dLevel)
        {
        case 1:
            player.changeHealth(player.getHealth(), true);
            break;
        case 2:
            break;
        case 3:
            player.changeHealth(player.getHealth() / 2, false);
            break;
        }
    }
    
    Player& getPlayer()
    {
        return m_player;
    }

    void render(Model)
    {

    }
};




// Объявление класса и реализация элементарных методов

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

    void move(std::array<double, 3>);

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
