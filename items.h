#ifndef ITEMS_H
#define ITEMS_H
#include <iostream>
#include <vector>
#include <random>
#include "item.h"
#include "time.h"

using namespace std;

class Items
{
public:
    vector<Item> item_list;

    Items()
    {
        item_list = {
            Item("Wood", "W", "general", "Common", 10, 5),
            Item("Stone", "S", "general", "Common", 10, 5),
            Item("Metal", "M", "general", "Common", 10, 5),
            Item("Rope", "R", "general", "Common", 10, 5),
            Item("Stick", "S", "general", "Common", 10, 5),
            Item("Leather", "L", "general", "Common", 10, 5)
        };
    }

    int getRandomIndex()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, item_list.size() - 1);
        return dis(gen);
    }

    Item getRandomItem()
    {
        return item_list[(getRandomIndex() + time(0)) % item_list.size() ];
    }

    vector<Item> getItems()
    {
        return item_list;
    }
};

class Weapons
{
public:
    vector<Item> weapon_list;
    vector<Item> component_list;

    Weapons()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        weapon_list = {
            Item("Sword", "S", "weapon", "Common", 50, 30, {component_list[2], component_list[4]}, 19),
            Item("Axe", "A", "weapon", "Common", 50, 30, {component_list[0], component_list[1], component_list[3]}, 20),
            Item("Mace", "M", "weapon", "Common", 50, 30, {component_list[0], component_list[2], component_list[3]}, 23),
            Item("Spear", "S", "weapon", "Common", 50, 30, {component_list[4]}, 19),
            Item("Dagger", "D", "weapon", "Common", 50, 30, {component_list[2]}, 17),
            Item("Bat", "B", "weapon", "Common", 50, 30, {component_list[0], component_list[0]}, 20)
        };
    }

    int getRandomIndex()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, weapon_list.size() - 1);
        return dis(gen);
    }

    Item getRandomItem()
    {
        return weapon_list[(getRandomIndex() + time(0) + time(0)) % weapon_list.size()];
    }
};

class Shields
{
public:
    vector<Item> shield_list;
    vector<Item> component_list;

    Shields()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        shield_list = {
            Item("Wooden Shield", "S", "shield", "Common", 50, 30, {component_list[0], component_list[0], component_list[3]}, 0, 5),
            Item("Reinforced Shield", "S", "shield", "Common", 50, 30, {component_list[0], component_list[1], component_list[3]}, 0, 10),
            Item("Iron Shield", "S", "shield", "Common", 50, 30, {component_list[0], component_list[2], component_list[3]}, 0, 15)
        };
    }

    int getRandomIndex()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, shield_list.size() - 1);
        return dis(gen);
    }


    Item getRandomItem()
    {
        return shield_list[(getRandomIndex() + time(0) + time(0) + time(0)) % shield_list.size()];
    }
};

class Helmets
{
public:
    vector<Item> helmet_list;
    vector<Item> component_list;

    Helmets()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        helmet_list = {
            Item("Leather Helmet", "H", "helmet", "Common", 50, 30, {component_list[5], component_list[3]}, 0, 5),
            Item("Reinforced Helmet", "H", "helmet", "Common", 50, 30, {component_list[5], component_list[3], component_list[2]}, 0, 10),
            Item("Iron Helmet", "H", "helmet", "Common", 50, 30, {component_list[2], component_list[2], component_list[3]}, 0, 15)
        };
    }

    int getRandomIndex()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, helmet_list.size() - 1);
        return dis(gen);
    }

    Item getRandomItem()
    {
        return helmet_list[(getRandomIndex() + time(0) + time(0) + time(0) + time(0)) % helmet_list.size()];
    }
};

class Chestplates
{
public:
    vector<Item> chestplate_list;
    vector<Item> component_list;

    Chestplates()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        chestplate_list = {
            Item("Leather Chestplate", "C", "chestplate", "Common", 50, 30, {component_list[5], component_list[3]}, 0, 5),
            Item("Reinforced Chestplate", "C", "chestplate", "Common", 50, 30, {component_list[5], component_list[3], component_list[2]}, 0, 10),
            Item("Iron Chestplate", "C", "chestplate", "Common", 50, 30, {component_list[2], component_list[2], component_list[3]}, 0, 15)
        };
    }

    int getRandomIndex()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, chestplate_list.size() - 1);
        return dis(gen);
    }

    Item getRandomItem()
    {
        return chestplate_list[(getRandomIndex() + time(0) + time(0) + time(0) + time(0)) % chestplate_list.size()];
    }
};

class Legginses
{
public:
    vector<Item> leggins_list;
    vector<Item> component_list;

    Legginses()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        leggins_list = {
            Item("Leather Leggins", "L", "leggins", "Common", 50, 30, {component_list[5], component_list[3]}, 0, 5),
            Item("Reinforced Leggins", "L", "leggins", "Common", 50, 30, {component_list[5], component_list[3], component_list[2]}, 0, 10),
            Item("Iron Leggins", "L", "leggins", "Common", 50, 30, {component_list[2], component_list[2], component_list[3]}, 0, 15)
        };
    }

    int getRandomIndex()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, leggins_list.size() - 1);
        return dis(gen);
    }

    Item getRandomItem()
    {
        return leggins_list[(getRandomIndex() + time(0) + time(0) + time(0) + time(0) + time(0)) % leggins_list.size()];
    }
};

class Bootses
{
public:
    vector<Item> boots_list;
    vector<Item> component_list;

    Bootses()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        boots_list = {
            Item("Leather Boots", "B", "boots", "Common", 50, 30, {component_list[5], component_list[3]}, 0, 5),
            Item("Reinforced Boots", "B", "boots", "Common", 50, 30, {component_list[5], component_list[3], component_list[2]}, 0, 10),
            Item("Iron Boots", "B", "boots", "Common", 50, 30, {component_list[2], component_list[2], component_list[3]}, 0, 15)
        };
    }

    int getRandomIndex()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, boots_list.size() - 1);
        return dis(gen);
    }

    Item getRandomItem()
    {
        return boots_list[(getRandomIndex() + time(0) + time(0) + time(0) + time(0) + time(0) + time(0)) % boots_list.size()];
    }
};

#endif // ITEMS_H
