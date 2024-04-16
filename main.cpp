#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include "item.h"
#include "inventory.h"
#include<windows.h>

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

            cout << "1. Attack" << endl;
            cout << "2. Defend" << endl;
            cin >> option_attack;


            int enemy_attack = time(0) % 2; //enemy attack = 0 is for enemy attack and e... = 1 is for defence :)

            if(option_attack[0] == 'A' || option_attack[0] == 'a') //place holder just for now. later it will be replaced for wsad movement
            {

                int damage_to_enemy = player_dmg - enemy_defence;
                if(damage_to_enemy < 0 && enemy_attack == 0) //if defence bigger than attack
                {
                    enemy_hp--;
                }
                else if(enemy_attack == 0)
                {
                    enemy_hp = enemy_hp - damage_to_enemy;
                }
                else if(enemy_attack == 1)
                {
                    enemy_hp = enemy_hp - (damage_to_enemy / 2);
                }

                int damage_to_player = enemy_damage - player_defence;
                if(damage_to_player < 0 && enemy_attack == 0)
                {
                    player_hp--;
                }
                else if(enemy_attack == 0)
                {
                    player_hp = player_hp - damage_to_player;
                }

            }
            else if(option_attack[0] == 'D' || option_attack[0] == 'd')  //place holder just for now. later it will be replaced for wsad movement
            {
                int damage_to_player = enemy_damage - player_defence;
                if(damage_to_player < 0 && enemy_attack == 0)
                {
                    string message = "Player defended the attack!";
                }
            }
        }
    }

    void show_message(string message)
    {
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
        }*/

        cout << "=============================================================" << endl << endl; //this thing has 61 characters and 55 to look nicely
        //cout << "|  "; //yeaaaa its part of that code :|
        cout << "   "; //<< but spaces look better// XD i automaticaly wrote it as cout element. imma leave it
        //int counter_int = 0; // you know the drill. Its part of that code
        for(int k = 0; k < message.size(); k++) //this loop wil print out all of the words letter by letter
        {

        }
    }

};

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
    void Game_loop()
    {
        string user_input;

        cout << "=============================================================" << endl << endl;
        cout << "[INVENTORY]  [SHOP]  [BLACKSMITH]  [EXPEDITION]  [CLOSE GAME]" << endl << endl;
        cout << "=============================================================" << endl;

        cout << "choose one option: ";
        getline(cin, user_input);
        cout << endl;


            string inventory_user_input;
            I->display();

            cout << endl << "Enter a command: ";
            getline(cin, inventory_user_input);
            cout << endl;

            if(inventory_user_input[0] == 's'|| inventory_user_input[1] == 'S')
            {
                string first_cords;
                string second_cords;

                cout << "Enter first coordinates: ";
                getline(cin, first_cords);
                cout << endl;
            }
            else
            {
                Expedition exp;
                exp.fill_gear(I);
            }
        }

};



int main()
{
    /*   //test code
    Inventory I;

    I.add_item(2, 4, Item(0, "", "1"));
    I.add_item(4, 1, Item(0, "", "2"));
    I.add_item(3, 8, Item(0, "", "3"));
    I.add_item(1, 4, Item(0, "", "4"));
    I.add_gear_to_main(1, 1, Boots(0, "", "B"));
    I.add_gear_to_main(1, 6, Weapon(0, "", "W"));


    I.swap_items("A6", "#5");

    I.add_gold(777);
    */
    Game g;
    g.Game_loop();

    return 0;
}
