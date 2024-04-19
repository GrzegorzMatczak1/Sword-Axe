#include <iostream>
#include "item.h"

using namespace std;

Item::Item(int amount, string name, string display_name, string item_type, string slot_type, string rarity)
    : amount{amount}, name{name}, display_name{display_name}, item_type{item_type}, slot_type{slot_type}, rarity{rarity}
{
    max_amount = 5;
}

Gear::Gear(int amount, string name, string display_name, string item_type, string slot_type, string rarity,
           vector<Item> components) : Item(amount, name, display_name, item_type, slot_type, rarity), components(components) {}

void Item::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Amount: " << this->amount << endl;
    cout << "Type: " << this->item_type << endl;
    cout << "Rarity: " << this->rarity << endl;
}

void Weapon::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->item_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Damage: " << this->actual_damage << endl;
    cout << "Crit chance: " << this->crit_chance << endl;
}



void Shield::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->item_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Defence: " << this->actual_defence << endl;
}

void Helmet::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->item_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
void Chestplate::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->item_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
void Leggins::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->item_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
void Boots::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->item_type << endl;
    cout << "Rarity: " << this->rarity << endl;
    cout << "Defence: " << this->actual_defence << endl;
}
