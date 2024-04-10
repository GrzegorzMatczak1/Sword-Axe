#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include "item.h"
#include "inventory.h"

using namespace std;

class Game
{


public:
    Inventory* I;
    bool isRunning;
    bool tutorial;
    map<int, string> operationOptions;
    Game()
    {
        isRunning = true;
        I = new Inventory();

        operationOptions[0] = "defaulut";
        operationOptions[0] = "inspect";
        operationOptions[0] = "swap";
    }
    void chagne_tutorial_state(bool changer)
    {
        if(changer != tutorial)
        {
            tutorial = changer;
        }
    }
    void run()
    {
        do{

        }while (isRunning);
    }
    void Game_display()
    {
        string user_input;

        cout << "[INVENTORY]  [SHOP]  [BLACKSMITH]  [EXPEDITION]" << endl;

        cout << "choose one option ";
        cin >> user_input;

        if(user_input[0] == 'i' || user_input[0] == 'I')
        {

        }
    }
};

int main()
{

    Inventory I;

    I.add_item(2, 4, Item(0, "", "1"));
    I.add_item(4, 1, Item(0, "", "2"));
    I.add_item(3, 8, Item(0, "", "3"));
    I.add_item(1, 4, Item(0, "", "4"));
    I.add_gear_to_main(1, 1, Boots(0, "", "B"));
    I.add_gear_to_main(1, 6, Weapon(0, "", "W"));

    I.display();

    I.swap_items("A6", "#5");

    I.add_gold(777);

    I.display();

    return 0;
}
