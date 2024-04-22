#ifndef RARITY_H
#define RARITY_H
#include <iostream>
#include <vector>

class Item;
class Weapon;
class Shield;
class Armor;

using namespace std;

class Rarity
{
public:
    string name;
    float defenceMultiplier;
    float damageMultiplier;

    Rarity(string name, float defenceMultiplier, float damageMultiplier)
        : name{name}, defenceMultiplier{defenceMultiplier}, damageMultiplier{damageMultiplier} {}

    Rarity(string name = "nonexistent"){}


};

class Rarities
{
public:
    vector<Rarity> rarities;

    Rarities()
    {
        rarities = {
            Rarity("Common", 0.0, 0.0),
            Rarity("Uncommon", 0.075, 0.075),
            Rarity("Rare", 0.15, 0.15),
            Rarity("Epic", 0.225, 0.225),
            Rarity("Legendary", 0.4, 0.4)
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
/*
    template<typename T>
    void applyRarity(T* item)
    {


        if (is_same<T, Weapon>::value)
        {
            item->actual_damage = int(item->base_damage + (item->base_damage * getRarity(item->rarity).damageMultiplier));
        } else if (is_same<T, Shield>::value || is_same<T, Armor>::value)
        {
            item->actual_defence = int(item->base_defence + (item->base_defence * getRarity(item->rarity).defenceMultiplier));
        }
    }
*/
};

#endif // RARITY_H
