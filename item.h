#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <vector>

using namespace std;

class Item
{
public:
    int id;
    int amount;
    const int max_amount = 64;
    string name;
    string display_name;
    string item_type;
    string slot_type;

    Item(int id = 0, int amount = 1, string name = "Wood", string display_name = "W",  string item_type = "Recourse", string slot_type = "General")
        : id{id}, amount{amount}, name{name}, display_name{display_name}, item_type{item_type}, slot_type{slot_type} {}

};

class Gear : public Item
{
public:
    int durability;
    string gear_type; // weapon, armor, shield or whatever
    string quality; // perfect, good, mid, bad, terrible - is that what quality is???
    vector<string> traits; // Chatgpt said that vectors are much better and less of a pain in the ass
    
    Gear(int id = 2, int amount = 1, string name = "Wood", string display_name = "W", string item_type = "Resource", string slot_type = "General",
         int durability = 0, string gear_type = "", string quality = "")
        : Item(id, amount, name, display_name, item_type, slot_type), durability(durability), gear_type(gear_type), quality(quality) {}
    
    void add_trait(string trait_name); // what are traits btw? What do they do?
};

class Weapon : public Gear
{
public:
    int base_damage; // I'm guessing this is damage of a weapon before any things that increase or decrease it, right? shouldn't it be float to decrease dealt damage to a player?
    float crit_chance; // debatable attribute. can delete if you want
    
    Weapon(int id = 0, int amount = 1, string name = "Ancient trident", string display_name = "T", string item_type = "weapon", string slot_type = "Attack" /*can be weapon idc*/,
           int durability = 75, string gear_type = "Melee", string quality = "rusty", int base_damage = 0, float crit_chance = 0.1 /*aka 10%*/)
        : Gear(id, amount, name, display_name, item_type, slot_type, durability, gear_type, quality),
        base_damage(base_damage), crit_chance(crit_chance) {}
    
};

class Armor : public Gear
{
public:
    int base_defence; // same as base damage?
    
    // can shield be classified as an armor? because it doesn't do any damage and instead protects a player just like helmets, chestplates etc. do
    
    Armor(int id = 0, int amount = 1, string name = "Spartan helmet", string display_name = "H", string item_type = "Armor", string slot_type = "Armor" /*if the slot is different than general, it means that the item can be put in that slot + general inventory like anything else*/,
          int durability = 50, string gear_type = "helmet", string quality = "new", int base_defence = 1)
        : Gear(id, amount, name, display_name, item_type, slot_type, durability, gear_type, quality), base_defence(base_defence) {}
};

#endif // ITEM_H
