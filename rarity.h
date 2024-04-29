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
    int worthIncrease;

    Rarity(string name, int damageMultiplier, int defenceMultiplier, int cost, int worthIncrease)
        : name{name}, damageMultiplier{damageMultiplier}, defenceMultiplier{defenceMultiplier}, cost{cost}, worthIncrease{worthIncrease} {}

    Rarity(string name = "nonexistent"){}

};

class Rarities
{
public:
    vector<Rarity> rarities;

    Rarities()
    {
        rarities = {
            Rarity("Common", 0, 0, 0, 0),
            Rarity("Uncommon", 2, 2, 15, 10),
            Rarity("Rare", 3, 3, 25, 20),
            Rarity("Epic", 5, 5, 35, 30),
            Rarity("Legendary", 7, 7, 50, 45)
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
            item->worth = item->worth + getRarity(item->rarity).worthIncrease;
        } 
        else if (item->slot_type == "general")
        {
            item->worth = item->worth + getRarity(item->rarity).worthIncrease;
        }
        else
        {
            item->actual_defence = item->base_defence + getRarity(item->rarity).defenceMultiplier;
            item->worth = item->worth + getRarity(item->rarity).worthIncrease;
        }
    }

};

#endif // RARITY_H
