#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <vector>

using namespace std;

class Item
{
public:
    int amount;
    const int max_amount = 5;
    string name;
    string display_name;
    string item_type;
    string slot_type;

    Item(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "general")
        : amount{amount}, name{name}, display_name{display_name}, item_type{item_type}, slot_type{slot_type} {}

    virtual void get_data() const;

};

class Gear : public Item
{
public:
    int durability;
    string quality;

    Gear(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "",
         int durability = 0, string quality = "")
        : Item(amount, name, display_name, item_type, slot_type), durability(durability), quality(quality) {}
};

class Weapon : public Gear
{
public:
    int base_damage;
    int actual_damage;
    float crit_chance;

    Weapon(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "",
           int durability = 0, string quality = "", int base_damage = 0, float crit_chance = 0.0)
        : Gear(amount, name, display_name, item_type, slot_type, durability, quality),
        base_damage(base_damage), crit_chance(crit_chance) {}

    void get_data() const override;

};

class Armor : public Gear
{
public:
    int base_defence;
    int actual_defence;

    Armor(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "",
          int durability = 0, string quality = "", int base_defence = 0)
        : Gear(amount, name, display_name, item_type, slot_type, durability, quality), base_defence(base_defence) {}

    void get_data() const override;
};

class Helmet : public Armor
{
public:
    string slot_type = "helmet";
    Helmet(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "",
           int durability = 0, string quality = "", int base_defence = 0)
        : Armor(amount, name, display_name, item_type, slot_type, durability, quality, base_defence) {}
};

class Chestplate : public Armor
{
public:
    string slot_type = "chestplate";
    Chestplate(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "",
           int durability = 0, string quality = "", int base_defence = 0)
        : Armor(amount, name, display_name, item_type, slot_type, durability, quality, base_defence) {}
};

class Leggins : public Armor
{
public:
    string slot_type = "leggins";
    Leggins(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "",
               int durability = 0, string quality = "", int base_defence = 0)
        : Armor(amount, name, display_name, item_type, slot_type, durability, quality, base_defence) {}
};

class Boots : public Armor
{
public:
    string slot_type = "boots";
    Boots(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "",
               int durability = 0, string quality = "", int base_defence = 0)
        : Armor(amount, name, display_name, item_type, slot_type, durability, quality, base_defence) {}
};

class Shield : public Gear
{
public:
    int base_defence;
    int actual_defence;

    Shield(int amount = 0, string name = "none", string display_name = "", string item_type = "", string slot_type = "",
           int durability = 0, string quality = "", int base_defence = 0)
        : Gear(amount, name, display_name, item_type, slot_type, durability, quality), base_defence(base_defence) {}

    void get_data() const override;
};

#endif // ITEM_H
