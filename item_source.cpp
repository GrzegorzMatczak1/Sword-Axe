#include <iostream>
#include "item.h"

using namespace std;

void Item::get_data() const
{
    cout << "Name: " << this->name << endl;
    cout << "Amount: " << this->amount << endl;
    cout << "Type: " << this->item_type << endl;
}

void Weapon::get_data() const
{
    Item::get_data();
    cout << "Damage: " << this->actual_damage << endl;
    cout << "Crit chance: " << this->crit_chance << endl;
}

void Armor::get_data() const
{
    Item::get_data();
    cout << "Defence: " << this->actual_defence << endl;
}

void Shield::get_data() const
{
    Item::get_data();
    cout << "Defence: " << this->actual_defence << endl;
}
