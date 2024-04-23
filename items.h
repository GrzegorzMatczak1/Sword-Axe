#ifndef ITEMS_H
#define ITEMS_H
#include <iostream>
#include <vector>
#include <random>
#include "item.h"

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
        return item_list[getRandomIndex()];
    }

    vector<Item> getItems()
    {
        return item_list;
    }
};

class Weapons
{
public:
    vector<Weapon> weapon_list;
    vector<Item> component_list;

    Weapons()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        weapon_list = {
            Weapon("Sword", "S", "weapon", "Common", 50, 30, {component_list[2], component_list[4]}, 19),
            Weapon("Axe", "A", "weapon", "Common", 50, 30, {component_list[0], component_list[1], component_list[3]}, 20),
            Weapon("Mace", "M", "weapon", "Common", 50, 30, {component_list[0], component_list[2], component_list[3]}, 23),
            Weapon("Spear", "S", "weapon", "Common", 50, 30, {component_list[4]}, 19),
            Weapon("Dagger", "D", "weapon", "Common", 50, 30, {component_list[2]}, 17),
            Weapon("Bat", "B", "weapon", "Common", 50, 30, {component_list[0], component_list[0]}, 20)
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
        return weapon_list[getRandomIndex()];
    }
};

class Shields
{
    vector<Shield> shield_list;
    vector<Item> component_list;

    Shields()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        shield_list = {
            Shield("Wooden Shield", "S", "shield", "Common", 50, 30, {component_list[0], component_list[0], component_list[3]}, 5),
            Shield("Reinforced Shield", "S", "shield", "Common", 50, 30, {component_list[0], component_list[1], component_list[3]}, 10),
            Shield("Iron Shield", "S", "shield", "Common", 50, 30, {component_list[0], component_list[2], component_list[3]}, 15)
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
       return shield_list[getRandomIndex()];
    }
};

class Helmets
{
    vector<Helmet> helmet_list;
    vector<Item> component_list;

    Helmets()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        helmet_list = {
            Helmet("Leather Helmet", "H", "helmet", "Common", 50, 30, {component_list[5], component_list[3]}, 5),
            Helmet("Reinforced Helmet", "H", "helmet", "Common", 50, 30, {component_list[5], component_list[3], component_list[2]}, 10),
            Helmet("Iron Helmet", "H", "helmet", "Common", 50, 30, {component_list[2], component_list[2], component_list[3]}, 15)
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
        return helmet_list[getRandomIndex()];
    }
};

class Chestplates
{
    vector<Chestplate> chestplate_list;
    vector<Item> component_list;

    Chestplates()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        chestplate_list = {
            Chestplate("Leather Chestplate", "C", "chestplate", "Common", 50, 30, {component_list[5], component_list[3]}, 5),
            Chestplate("Reinforced Chestplate", "C", "chestplate", "Common", 50, 30, {component_list[5], component_list[3], component_list[2]}, 10),
            Chestplate("Iron Chestplate", "C", "chestplate", "Common", 50, 30, {component_list[2], component_list[2], component_list[3]}, 15)
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
        return chestplate_list[getRandomIndex()];
    }
};

class Legginses
{
    vector<Leggins> leggins_list;
    vector<Item> component_list;

    Legginses()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        leggins_list = {
            Leggins("Leather Leggins", "L", "leggins", "Common", 50, 30, {component_list[5], component_list[3]}, 5),
            Leggins("Reinforced Leggins", "L", "leggins", "Common", 50, 30, {component_list[5], component_list[3], component_list[2]}, 10),
            Leggins("Iron Leggins", "L", "leggins", "Common", 50, 30, {component_list[2], component_list[2], component_list[3]}, 15)
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
        return leggins_list[getRandomIndex()];
    }
};

class Bootses
{
    vector<Boots> boots_list;
    vector<Item> component_list;

    Bootses()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick, 5 - leather

        boots_list = {
            Boots("Leather Boots", "B", "boots", "Common", 50, 30, {component_list[5], component_list[3]}, 5),
            Boots("Reinforced Boots", "B", "boots", "Common", 50, 30, {component_list[5], component_list[3], component_list[2]}, 10),
            Boots("Iron Boots", "B", "boots", "Common", 50, 30, {component_list[2], component_list[2], component_list[3]}, 15)
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
        return boots_list[getRandomIndex()];
    }
};

#endif // ITEMS_H
