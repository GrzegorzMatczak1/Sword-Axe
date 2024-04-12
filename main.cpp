#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include "item.h"
#include "inventory.h"

using namespace std;

class Items
{
public:
    vector<Item> item_list;

    Items()
    {
        item_list = {
            Item(1, "Wood", "W", "Resourse", "General", "Common"),
            Item(1, "Stone", "S", "Resourse", "General", "Common"),
            Item(1, "Metal", "M", "Resourse", "General", "Uncommon"),
            Item(1, "Rope", "R", "Resourse", "General", "Uncommon"),
            Item(1, "Stick", "S", "Resourse", "General", "Common")
        };
    }
};

int main()
{
    
    Inventory I;
    Items It;

    I.add_item(2, 4, It.item_list[0]);
    I.add_item(4, 1, It.item_list[2]);
    I.add_item(3, 8, It.item_list[1]);
    I.add_item(1, 4, It.item_list[3]);

    I.display();

    cout << endl;

    I.getInfo("C8");

    cout << endl;

    //I.swap_items("D1", "C8");

    I.display();
    return 0;
}
