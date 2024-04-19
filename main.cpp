#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include "item.h"
#include "inventory.h"
#include <random>

// for platform specific functionality //  for now only clear() method in Game
#if defined(_WIN32)
#define PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM_MACOS
#else
#endif


using namespace std;

class Expedition
{
public:
    int enemy_hp;
    int enemy_damage;
    int enemy_defence;
    string enemy_name;

    Item** player_gear;
    int player_hp;
    int player_dmg;
    int player_defence;


    Expedition()
    {
        player_hp = 100; //adding basic values for player only hp will be permament
        player_dmg = 1;

        player_defence = 1;

        enemy_defence = 2; //adding basic damage to enemy. Later it will be randomly chosen from a list with some atributes given in between
        enemy_name = "Halpis";
        enemy_damage = 2;
        enemy_hp = 6;

        player_gear = new Item*[6];
        player_gear[0] = nullptr;
        player_gear[1] = nullptr;
        player_gear[2] = nullptr;
        player_gear[3] = nullptr;
        player_gear[4] = nullptr;
        player_gear[5] = nullptr;
    }

    void fill_gear(Inventory* inventory)
    {
        player_gear[0] = inventory->battle_slots[0];
        player_gear[1] = inventory->battle_slots[1];
        player_gear[2] = inventory->battle_slots[2];
        player_gear[3] = inventory->battle_slots[3];
        player_gear[4] = inventory->battle_slots[4];
        player_gear[5] = inventory->battle_slots[5];
    }

    void expedition_loop()
    {
        bool game_end = false;


        while(!game_end)
        {
            string message;
            string option_attack;

            cout << "Enemy stats:" << endl;
            cout << "Enemy name: " << enemy_name << endl;
            cout << "Enemy hp: " << enemy_hp << endl << endl;

            cout << "Player stats:" << endl;
            cout << "Player hp: " << player_hp << endl << endl;


            cout << "Choose one option:" << endl;
            cout << "1. Attack" << endl;
            cout << "2. Defend" << endl;
            cin >> option_attack;


            int enemy_attack = time(0) % 2; //enemy attack = 0 is for enemy attack and e... = 1 is for defence :)

            if(option_attack[0] == 'A' || option_attack[0] == 'a' || option_attack[0] == '1') //place holder just for now. later it will be replaced for wsad movement
            {
                string skipper;

                cout << "You chose attack!" << endl;
                cin >> skipper;

                if(enemy_attack == 0)
                {
                    cout << "Enemy chose attack!" << endl;
                    cin >> skipper;
                }
                else if(enemy_attack == 1)
                {
                    cout << "Enemy chose defend!" << endl;
                    cin >> skipper;
                }

                int damage_to_enemy = player_dmg - enemy_defence;
                if(damage_to_enemy < 0 && enemy_attack == 0) //if defence bigger than attack from player
                {
                    enemy_hp--;
                    message = "Enemy took only 1 hp of damage because of its huge defence";
                }
                else if(damage_to_enemy < 0 && enemy_attack == 1) //if enemy has huge defence and it chose defend
                {
                    message = "Enemy defended the attack!";
                }
                else if(enemy_attack == 0)
                {
                    enemy_hp = enemy_hp - damage_to_enemy;
                    message = "Proper attack!";
                }
                else if(enemy_attack == 1)
                {
                    enemy_hp = enemy_hp - (damage_to_enemy / 2);
                    message = "Enemy takes half of the damage!";
                }

                int damage_to_player = enemy_damage - player_defence;
                if(damage_to_player <= 0 && enemy_attack == 0)
                {
                    player_hp--;
                    message = "Player took only 1 hp of damage because of its huge defence";
                }
                else if(damage_to_player > 0 && enemy_attack == 0)
                {
                    player_hp = player_hp - damage_to_player;
                    message = "You took some damage!";
                }

                show_message(message);


            }
            else if(option_attack[0] == 'D' || option_attack[0] == 'd')  //place holder just for now. later it will be replaced for wsad movement
            {
                int damage_to_player = enemy_damage - player_defence;
                if(damage_to_player <= 0 && enemy_attack == 0)
                {
                    message = "Player defended the attack!";
                }
                else if(damage_to_player > 0 && enemy_attack == 0)
                {
                    player_hp = player_hp - (damage_to_player / 2);
                    message = "Player takes half of the damage!";
                }
            }
        }
    }

    void show_message(string message)
    {

        cout << message << endl;


        /* //dont need the code but i just cant get rid of it (put too much work to it)
        int last_space = 0;
        vector<string> word_list;
        int counter = 0;
        for(int i = 0; i < message.size(); i++) //this loop splits string into diffrent words by space (i know i could have done it by not splitting that but then there will be a problem if a string is to long for a display window) yea i love bringing my self pain
        {
            if(message[i] == ' ')
            {
                string word;
                int counter2 = 0;
                for(int y = last_space; y < i; y++) //some calculations 0-5 "sring| is |good"// its useles now :3 // i was trying to figure out how to split that string
                {
                    word[counter2] = message[y];
                    counter2++;
                }
                if(i - 1 == last_space)
                {
                    char letter = message[i - 1];
                    string letter_string(1, letter);
                    word_list.push_back(letter_string);
                }
                else
                {
                    word_list.push_back(word);
                }
                last_space += i + 1;
                counter++;
            }
        }

        //cout << "=============================================================" << endl << endl; //this thing has 61 characters and 55 to look nicely
        //cout << "|  "; //yeaaaa its part of that code :|
        //cout << "   "; //<< but spaces look better// XD i automaticaly wrote it as cout element. imma leave it
        //int counter_int = 0; // you know the drill. Its part of that code

        //for(int k = 0; k < message.size(); k++) //this loop wil print out all of the words letter by letter
        //{

        //}
    }*/

};

class Items
{
public:
    vector<Item> item_list;

    Items()
    {
        item_list = {
            Item(1, "Wood", "W", "Resourse", "general", "Common"),
            Item(1, "Stone", "S", "Resourse", "general", "Common"),
            Item(1, "Metal", "M", "Resourse", "general", "Uncommon"),
            Item(1, "Rope", "R", "Resourse", "general", "Uncommon"),
            Item(1, "Stick", "S", "Resourse", "general", "Common")
        };
    }

    int getRandomIndex()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, item_list.size() - 1); // nwm jak to działa. ale przynajmniej nie zwraca takich samych wartości jak sie wywoła kilka razy w tej samej sekundzie
        return dis(gen);
    }

    Item getRandomItem()
    {
        return item_list[getRandomIndex()];
    }

    void setRandomAmount(int itemIndex) // can be specific or random
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, item_list.size());

        for (int i = 0; i < item_list.size(); i++)
        {
            int randAmount = dis(gen);
            item_list[i].amount = randAmount;
        }
    }
};

class Game
{
public:
    Inventory* I;
    bool isRunning;
    string currentOperation;
    string logsMessage; // logs info //  example: "Swap successful", "Couldn't inspect an item. Wrong input!" etc
    enum class Operations
    {
        Default,
        Swap,
        Inspect,
        Drop,

        Exit,
        Error
    };
    map<Operations, string> typesOfOperations;

    Game()
    {
        I = new Inventory();
        isRunning = true;
        logsMessage = "Welcome!";
        currentOperation = "default";

        Items It;

        I->add_item(2, 4, It.getRandomItem());
        I->add_item(4, 1, It.getRandomItem());
        I->add_item(3, 8, It.getRandomItem());
        I->add_item(1, 4, It.getRandomItem());
        I->add_gear_to_main(1, 1, Boots(0, "", "B"));
        I->add_gear_to_main(1, 6, Weapon(0, "", "W"));

        // this all will basically be used for displaying specific operations
        // when we select some, the terminal will be cleared and display the specific menu
        // that way we have only what's necessary on display
        // example: during inputing an item to inspect, we don't need to have a shop displayed

        typesOfOperations[Operations::Default] = "default"; // display main menu
        typesOfOperations[Operations::Swap] = "swap";
        typesOfOperations[Operations::Inspect] = "inspect";
        typesOfOperations[Operations::Drop] = "drop";

        typesOfOperations[Operations::Exit] = "exit";

        //we'll probably need to add: delete/disassemble, exit menu, shop, blacksmith, combat(fighting enemies or whatever) and maybe something else
        }

    void run()
    {
        while(isRunning){
            clear();



            gameDisplay();
        }

        clear();

        clear();

        cout << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Thanks for playing!" << endl;
        cout << "-----------------------------------------" << endl;
    }

    void gameDisplay()
    {

        logsDisplay();

        Operations op = getCurrentOperation(currentOperation);
        switch (op)
        {
        case Operations::Default:
            mainMenu();
            break;
        case Operations::Swap:
            swapMenu();
            break;
        case Operations::Inspect:
            inspectMenu();
            break;
        case Operations::Drop:
            dropMenu();
            break;

        case Operations::Exit:
            isRunning = !isRunning;
            break;
        case Operations::Error:
            cout << "Some kind of error!" << endl;
            break;
        default:
            cout << "Some kind of error!" << endl;
            break;
        }
    }

    Operations getCurrentOperation(string currentOperation)
    {
        for (const auto& pair : typesOfOperations)
        {
            if (pair.second == currentOperation)
            {
                return pair.first; // returns a enum operation value // will be used in gameDisplay
            }
        }
        return Operations::Error;
    }

    void mainMenu()
    {
        inventoryDisplay();

        cout << endl << "  Possible actions:" << endl;
        cout << "  1. Swap items." << endl;
        cout << "  2. Inspect an item." << endl;
        cout << "  3. Drop an item" << endl;
        cout << "  exit. Exit game." << "\n\n";

        string input;
        cout << "  Input: ";
        cin >> input;
        cout << endl;

        if (input == "1")
        {
            currentOperation = "swap";
        }
        else if (input == "2")
        {
            currentOperation = "inspect";
        }
        else if (input == "3")
        {
            currentOperation = "drop";
        }

        else if (input == "exit")
        {
            currentOperation = "exit";
        }
        else
        {
            logsMessage = "Couldn't pick an option. Your input must be invalid! Try typing a number next time!";
        }
    }

    void swapMenu()
    {
        inventoryDisplay();

        cout << endl << "  Enter two coordinates to swap." << endl;

        string cords1;
        string cords2;

        cout << "  First element: ";
        cin >> cords1;
        cout << endl;

        cout << "  Second element: ";
        cin >> cords2;
        cout << endl;

        logsMessage = I->swap_items(cords1, cords2);

        currentOperation = "default";
    }

    void inspectMenu()
    {
        // work in progress
    }

    void dropMenu()
    {
        inventoryDisplay();

        cout << endl << "  Enter coordinate to delete." << endl;

        string cords;

        cout << "  Delete an item: ";
        cin >> cords;
        cout << endl;

        logsMessage = I->delete_an_item(cords);

        currentOperation = "default";
    }

    void sortMenu()
    {
        // empty
    }

    void logsDisplay()
    {
        cout << "-----------------------------------------" << endl;
        cout << "  " << logsMessage << endl;
        cout << "-----------------------------------------" << endl;
        cout << "\n";
    }

    void inventoryDisplay()
    {
        cout << endl << "  Inventory:" << endl;
        I->display();
        cout << endl;
    }

    void clear()
    {
#ifdef PLATFORM_WINDOWS
        system("cls");
#elif defined(PLATFORM_MACOS)
        system("clear");
#else
#endif
    }

    ~Game()
    {
        delete I;
    }
};

int main()
{

    Game game;

    //game.gameDisplay();
    game.run();

    //Inventory I;
    //Items It;

    //I.add_item(2, 4, It.getRandomItem());
    //I.add_item(4, 1, It.getRandomItem());
    //I.add_item(3, 8, It.getRandomItem());
    //I.add_item(1, 4, It.getRandomItem());
    //I.add_gear_to_main(1, 1, Boots(0, "", "B"));
    //I.add_gear_to_main(1, 6, Weapon(0, "", "W"));

    return 0;
}
