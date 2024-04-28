#ifndef RARITY_H
#define RARITY_H
#include <iostream>
#include <vector>

using namespace std;

class Rarity
{
public:
    string name;
    int defenceMultiplier;
    int damageMultiplier;
    int cost;

    Rarity(string name, int damageMultiplier, int defenceMultiplier, int cost)
        : name{name}, damageMultiplier{damageMultiplier}, defenceMultiplier{defenceMultiplier}, cost{cost} {}

    Rarity(string name = "nonexistent"){}

};

class Rarities
{
public:
    vector<Rarity> rarities;

    Rarities()
    {
        rarities = {
            Rarity("Common", 0, 0, 0),
            Rarity("Uncommon", 2, 2, 15),
            Rarity("Rare", 3, 3, 25),
            Rarity("Epic", 5, 5, 35),
            Rarity("Legendary", 7, 7, 50)
        };
    }

    Rarity getRarity(string name)
    {
        for (int i = 0; i < rarities.size(); i++)
        {
            if (rarities[i].name == name)
            {
                return rarities[i];
            }
        }
        return Rarity();
    }

    template <typename T>
    void applyRarity(T* item)
    {

        if (item->slot_type == "weapon")
        {
            item->actual_damage = item->base_damage + getRarity(item->rarity).damageMultiplier;
        } else if (item->slot_type == "general") {}
        else
        {
            item->actual_defence = item->base_defence + getRarity(item->rarity).defenceMultiplier;
        }
    }

};

#endif // RARITY_H
