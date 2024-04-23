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
            Item("Wood", "W", "general", "Common"),
            Item("Stone", "S", "general", "Common"),
            Item("Metal", "M", "general", "Uncommon"),
            Item("Rope", "R", "general", "Uncommon"),
            Item("Stick", "S", "general", "Common")
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
        component_list = I.getItems(); // [0] - wood, [1] - stone, [2] - metal, [3] - rope, [4] - stick

        weapon_list = {
            Weapon("Sword", "S", "weapon", "Common", {component_list[2], component_list[4]}, 19),
            Weapon("Axe", "A", "weapon", "Common", {component_list[0], component_list[1], component_list[3]}, 20),
            Weapon("Mace", "M", "weapon", "Common", {component_list[0], component_list[2], component_list[3]}, 23),
            Weapon("Spear", "S", "weapon", "Common", {component_list[4]}, 19),
            Weapon("Dagger", "D", "weapon", "Common", {component_list[2]}, 17),
            Weapon("Bat", "B", "weapon", "Common", {component_list[0], component_list[0]}, 20)
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
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick

        shield_list = {
            Shield("Wooden Shield", "S", "shield", "Common", {component_list[0], component_list[0], component_list[3]}, 15),
            Shield("Reinforced Wooden Shield", "R", "shield", "Epic", {component_list[0], component_list[1], component_list[3]}, 17),
            Shield("Iron Shield", "I", "shield", "Uncommon", {component_list[0], component_list[2], component_list[3]}, 20)
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
        Item randItem = shield_list[getRandomIndex()];

        vector<string> rarities = {
            "Common", "Uncommon", "Rare", "Epic", "Legendary"
        };
        auto randomRarity = [](vector<string> rarities)
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, rarities.size() - 1);
            return dis(gen);
        };

        randItem.rarity = randomRarity(rarities);

        return randItem;
    }
};

class Helmets
{
    vector<Shield> helmet_list;
    vector<Item> component_list;

    Helmets()
    {
        Items I;
        component_list = I.getItems(); // 0 - wood, 1 - stone, 2 - metal, 3 - rope, 4 - stick

        helmet_list = {
            Shield("Wooden Shield", "S", "shield", "Common", {component_list[0], component_list[0], component_list[3]}, 15),
            Shield("Reinforced Wooden Shield", "R", "shield", "Epic", {component_list[0], component_list[1], component_list[3]}, 17),
            Shield("Iron Shield", "I", "shield", "Uncommon", {component_list[0], component_list[2], component_list[3]}, 20)
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

#endif // ITEMS_H
