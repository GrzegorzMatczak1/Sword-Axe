#include <iostream>
#include "item.h"
#include "rarity.h"

using namespace std;

Item::Item(string name, string display_name, string slot_type, string rarity)
    :  name{name}, display_name{display_name}, slot_type{slot_type}, rarity{rarity}
{
    Rarities r;

    //r.applyRarity<Item>(this);
}

Gear::Gear(string name, string display_name, string slot_type, string rarity,
           vector<Item> components) : Item(name, display_name, slot_type, rarity), components(components) {}

void Item::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
}

void Weapon::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Damage: " << this->actual_damage << endl;
}

void Shield::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Defence: " << this->actual_defence << endl;
}

void Helmet::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
void Chestplate::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
void Leggins::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
void Boots::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->slot_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
