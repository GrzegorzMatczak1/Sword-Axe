#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <vector>
#include "item.h"
#include "inventory.h"
#include "items.h"
#include "shop.h"

// for platform specific functionality //  for now only clear() method in Game
#if defined(_WIN32)
#define PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM_MACOS
#else
#endif


using namespace std;

class Enemy //Youll split it later into different files you know //accualy we will leave it as it is
{
    string enemy_name;
    string introduction;
    string win_message;
    string loose_message;
    int enemy_hp;
    int enemy_dmg;
    int enemy_defence;

public:

    Enemy(string enemy_name = "Nameless", int enemy_hp = 10, int enemy_dmg = 1, int enemy_defence = 1, string introduction = "I am Namless the little prick", string win_message = "Didnt even try", string loose_message = "Whaa... I... I have lost! NOOOOOOO!") : enemy_name{enemy_name}, enemy_hp{enemy_hp}, enemy_dmg{enemy_dmg}, enemy_defence{enemy_dmg}, introduction{introduction}, win_message{win_message}, loose_message{loose_message}
    {

    }

    string return_name()
    {
        return enemy_name;
    }
    string return_introduction()
    {
        return introduction;
    }
    string return_win_message()
    {
        return win_message;
    }
    string return_loose_message()
    {
        return loose_message;
    }
    int return_hp()
    {
        return enemy_hp;
    }
    int return_dmg()
    {
        return enemy_dmg;
    }
    int return_defence()
    {
        return enemy_defence;
    }
};


class Game
{
public:
    Inventory* I;
    Shop* S;
    bool isRunning;
    string currentOperation;
    string logsMessage;
    enum class Operations
    {
        Default,
        Swap,
        Inspect,
        Drop,
        Blacksmith,
        Upgrade,
        Disassemble,
        Shop,
        Sell,
        Buy,
        Reroll,
        Check,
        Expedition,
        Exit,
        Error
    };
    map<Operations, string> typesOfOperations;

    Game()
    {
        I = new Inventory();
        S = new Shop();
        isRunning = true;
        logsMessage = "Welcome!";
        currentOperation = "default";

        Items It;
        Weapons W;
        Helmets H;
        Bootses B;

        I->add_item(2, 4, It.getRandomItem());
        I->add_item(4, 1, It.getRandomItem());
        I->add_item(3, 8, It.getRandomItem());
        I->add_item(1, 4, It.getRandomItem());
        I->add_item(2, 7, It.getRandomItem());
        I->add_item(1, 1, W.getRandomItem());
        I->add_item(1, 6, H.getRandomItem());
        I->add_item(3, 3, B.getRandomItem());


        typesOfOperations[Operations::Default] = "default";
        typesOfOperations[Operations::Swap] = "swap";
        typesOfOperations[Operations::Inspect] = "inspect";
        typesOfOperations[Operations::Drop] = "drop";
        typesOfOperations[Operations::Blacksmith] = "blacksmith";
        typesOfOperations[Operations::Upgrade] = "upgrade";
        typesOfOperations[Operations::Disassemble] = "disassemble";
        typesOfOperations[Operations::Shop] = "shop";
        typesOfOperations[Operations::Sell] = "sell";
        typesOfOperations[Operations::Buy] = "buy";
        typesOfOperations[Operations::Reroll] = "reroll";
        typesOfOperations[Operations::Check] = "check";
        typesOfOperations[Operations::Expedition] = "expedition";
        typesOfOperations[Operations::Exit] = "exit";

    }

    void run()
    {
        while(isRunning){
            clear();
            gameDisplay();
        }

        clear();

        cout << endl;
        cout << "-----------------------------------------" << endl;
        cout << "  Thanks for playing!" << endl;
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
        case Operations::Blacksmith:
            blacksmithMenu();
            break;
        case Operations::Upgrade:
            upgradeMenu();
            break;
        case Operations::Disassemble:
            disassembleSelectMenu();
            break;
        case Operations::Shop:
            shopMenu();
            break;
        case Operations::Sell:
            sellMenu();
            break;
        case Operations::Reroll:
            rerollMenu();
            break;
        case Operations::Buy:
            buyMenu();
            break;
        case Operations::Check:
            checkMenu();
            break;
        case Operations::Expedition:
            expeditionMenu();
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
                return pair.first;
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
        cout << "  4. Visit the blacksmith" << endl;
        cout << "  5. Visit Shop" << endl;
        cout << "  6. Go on an expedition" << endl;
        cout << "  7. Exit game." << "\n\n";

        string input;
        cout << "  Input: ";
        cin >> input;
        cout << endl;

        if (input == "1")
        {
            currentOperation = "swap";
            logsMessage = "Item swapping!";
        }
        else if (input == "2")
        {
            currentOperation = "inspect";
            logsMessage = "Item inspecting!";
        }
        else if (input == "3")
        {
            currentOperation = "drop";
            logsMessage = "Item dropping!";
        }
        else if (input == "4")
        {
            currentOperation = "blacksmith";
            logsMessage = "Welcome to the blacksmith!";
        }
        else if (input == "5")
        {
            currentOperation = "shop";
            logsMessage = "Welcome to the Shop!";
        }
        else if (input == "6")
        {
            currentOperation = "expedition";
            logsMessage = "Expedition!";
        }

        else if (input == "7")
        {
            currentOperation = "exit";
        }
        else
        {
            logsMessage = "Couldn't pick an option. Your input must be invalid! Try typing a number!";
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
        inventoryDisplay();

        string input;
        cout << "  Select an item: ";
        cin >> input;

        cout << endl;

        logsMessage = I->getInfo(input);

        cout << endl;
        string input1;
        cout << "  Type anything to continue: ";
        cin >> input1;

        currentOperation = "default";
    }

    void blacksmithMenu()
    {
        inventoryDisplay();

        cout << "  Chose an operation you'd like to perform." << endl;
        cout << "  1. Upgrade an item." << endl;
        cout << "  2. Disassemble an item." << endl;
        cout << "  3. Exit." << endl << endl;

        string input;
        cout << "  Input: ";
        cin >> input;

        if (input == "1")
        {
            logsMessage = "Upgrading!";
            currentOperation = "upgrade";
        }
        else if (input == "2")
        {
            logsMessage = "Disassembling!";
            currentOperation = "disassemble";
        }
        else if (input == "3")
        {
            logsMessage = "Blacksmith exited.";
            currentOperation = "default";
        }
        else
        {
            logsMessage = "Nonexistent input! Try again.";
            currentOperation = "blacksmith";
        }
    }

    void upgradeMenu()
    {
        inventoryDisplay();
        I->displayGold();

        cout << endl << "  Costs:"  << endl;
        cout << "  Common->Uncommon - 15" << endl;
        cout << "  Uncommon->Rare - 25" << endl;
        cout << "  Rare->Epic - 35" << endl;
        cout << "  Common->Uncommon - 50" << endl << endl;

        string input;
        cout << "  Select an item to upgrade: ";
        cin >> input;

        logsMessage = I->upgradeAnItem(input, &I->gold);

        currentOperation = "blacksmith";
    }

    void disassembleSelectMenu()
    {
        inventoryDisplay();

        string input;
        cout << "  Select an item to disassemble: ";
        cin >> input;
        cout << endl;

        if (I->validItem(input) != "correct")
        {
            logsMessage = I->validItem(input);
        }
        else
        {
            disassembleConfirmation(input);
        }

        currentOperation = "blacksmith";
    }

    void disassembleConfirmation(string userInput)
    {
        clear();
        logsDisplay();
        inventoryDisplay();

        cout << endl << "  Selected item's components:" << "\n\n";
        I->displayItemComponents(userInput);
        cout << "\n\n";

        string choice;
        cout << "  Would you like to disassemble the item?  [y/n]  : ";
        cin >> choice;
        cout << endl;

        if (choice == "y")
        {
            logsMessage = I->disassembleAnItem(userInput);
        }
        else if (choice == "n")
        {
            logsMessage = "Canceled.";
        }
        else
        {
            logsMessage = "Invalid choice!";
            disassembleConfirmation(userInput);
        }

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

    void shopMenu()
    {
        shopDisplay();
        I->displayGold();

        cout << "  Possible actions:" << endl;
        cout << "  1. Sell your item." << endl;
        cout << "  2. Buy an item." << endl;
        cout << "  3. Reroll the shop stock. Cost - 50 gold" << endl;
        cout << "  4. See item info." << endl;
        cout << "  5. Exit." << endl << endl;

        string input;
        cout << "  Input: ";
        cin >> input;

        if (input == "1")
        {
            currentOperation = "sell";
            logsMessage = "Shop exited.";
        }
        else if (input == "2")
        {
            currentOperation = "buy";
            logsMessage = "Buy an item.";
        }
        else if (input == "3")
        {
            currentOperation = "reroll";
            logsMessage = "Rerolling.";
        }
        else if (input == "4")
        {
            currentOperation = "check";
            logsMessage = "Item info.";
        }
        else if (input == "5")
        {
            currentOperation = "default";
            logsMessage = "Shop exited.";
        }
        else
        {
            currentOperation = "shop";
            logsMessage = "Invalid input. Please try again.";
        }
    }

    void sellMenu()
    {
        inventoryDisplay();
        I->displayGold();

        string input;
        cout << "  Which item would you like to sell: ";
        cin >> input;

        logsMessage = I->sellAnItem(input);

        currentOperation = "shop";
    }
    void buyMenu()
    {
        shopDisplay();
        I->displayGold();

        string input;
        cout << "  Which item would you like to buy: ";
        cin >> input;

        logsMessage = S->buyAnItem(input, I, &I->gold);

        currentOperation = "shop";
    }

    void rerollMenu()
    {
        logsMessage = S->rerollShop(&I->gold);
        currentOperation = "shop";
    }

    void checkMenu()
    {
        shopDisplay();

        string input;
        cout << "  Get info of: ";
        cin >> input;
        cout << endl;

        logsMessage = S->check(input);

        string whatever;
        cout << endl << "  Type anything when you're done: ";
        cin >> whatever;

        currentOperation = "shop";
    }


    ///===============================================================================================================

    void expeditionMenu()
    {
         string skipper;

        clear();
        
        bool game_end = false;
        bool game_won;

        Enemy enemy = generate_enemy();

        int enemy_hp = enemy.return_hp();
        int enemy_damage = enemy.return_dmg();
        int enemy_defence = enemy.return_defence();
        string enemy_name = enemy.return_name();
        string enemy_introduction = enemy.return_introduction();
        string enemy_win_message = enemy.return_win_message();
        string enemy_loose_message = enemy.return_loose_message();

        int player_hp = 100;
        int player_dmg = 10; //dont forget to add damage and defence things
        int player_defence = 10;

        clear();
        
        cout << enemy_name << ": " << enemy_introduction << endl;
        cout << "Type anything to continue: ";
        cin >> skipper;
        cout << endl;

        while(!game_end)
        {
            string message;
            string option_attack;
            
            clear();

            cout << "Enemy stats:" << endl;
            cout << "Enemy name: " << enemy_name << endl;
            cout << "Enemy hp: " << enemy_hp << endl << endl;

            cout << "Player stats:" << endl;
            cout << "Player hp: " << player_hp << endl << endl;


            cout << "Choose one option:" << endl;
            cout << "1. Attack" << endl;
            cout << "2. Defend" << endl;
            cout << "3. Give up" << endl;
            cout << "Your option: ";
            cin >> option_attack;
            cout << endl;


            int enemy_attack = time(0) % 2; //enemy attack = 0 is for enemy attack and e... = 1 is for defence :)

            if(option_attack[0] == 'A' || option_attack[0] == 'a' || option_attack[0] == '1') //place holder just for now. later it will be replaced for wsad movement //you replace it with your option thingy later
            {
                string skipper;

                clear();

                cout << "You chose to attack!" << endl;
                cout << "Type anything to continue: ";
                cin >> skipper;
                cout << endl;

                if(enemy_attack == 0)
                {

                    clear();
                    
                    cout << enemy_name <<" chose to attack!" << endl;
                    cout << "Type anything to continue: ";
                    cin >> skipper;
                    cout << endl;
                }
                else if(enemy_attack == 1)
                {
                    clear();
                    
                    cout << enemy_name <<" chose to defend!" << endl;
                    cout << "Type anything to continue: ";
                    cin >> skipper;
                    cout << endl;
                }

                int damage_to_enemy = player_dmg - enemy_defence;
                if(damage_to_enemy < 0 && enemy_attack == 0) //if defence bigger than attack from player
                {
                    enemy_hp--;
                    message = enemy_name + " took only 1 hp of damage because of their huge defence";
                }
                else if(damage_to_enemy < 0 && enemy_attack == 1) //if enemy has huge defence and it chose defend
                {
                    message = enemy_name + " defended the attack!";
                }
                else if(enemy_attack == 0)
                {
                    enemy_hp = enemy_hp - damage_to_enemy;
                    message = "You have landed a perfect attack!";
                }
                else if(enemy_attack == 1)
                {
                    enemy_hp = enemy_hp - (damage_to_enemy / 2);
                    message = enemy_name + " takes half of the damage!";
                }

                clear();
                
                show_message(message);
                cout << "Type anything to continue: ";
                cin >> skipper;
                cout << endl;

                int damage_to_player = enemy_damage - player_defence;
                if(damage_to_player <= 0 && enemy_attack == 0)
                {
                    player_hp--;
                    message = "You took only 1 hp of damage because of your huge defence";
                }
                else if(damage_to_player > 0 && enemy_attack == 0)
                {
                    player_hp = player_hp - damage_to_player;
                    message = enemy_name + " landed a perfect attack!";
                }

                clear();
                
                show_message(message);
                cout << "Type anything to continue: ";
                cin >> skipper;
                cout << endl;
                //logsMessage = message;



            }
            else if(option_attack[0] == 'D' || option_attack[0] == 'd' || option_attack[0] == '2')  //place holder just for now. later it will be replaced for wsad movement // same as above :)
            {
                int damage_to_player = enemy_damage - player_defence;
                if(damage_to_player <= 0 && enemy_attack == 0)
                {
                    message = "You have defended the attack!";
                }
                else if(damage_to_player > 0 && enemy_attack == 0)
                {
                    player_hp = player_hp - (damage_to_player / 2);
                    message = "You take half of the damage!";
                }
                else if(enemy_attack == 1)
                {
                    message = "Bough you and enemy chose to defend!";
                }
                
                clear();
                
                show_message(message);
                cout << "Type anything to continue: ";
                cin >> skipper;
                cout << endl;
            }
            else if(option_attack[0] == 'G' || option_attack[0] == 'g' || option_attack[0] == '3')
            {
                string option_give_up;

                clear();
                
                cout << "Are you sure you want to give up?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                
                cout << "Your option: ";
                cin >> option_give_up;
                cout << endl;

                if(option_give_up[0] == 'Y' || option_attack[0] == 'y' || option_attack[0] == '1')
                {
                    game_end = true;
                    game_won = false;
                }
                else
                {
                    string skipper;

                    clear();

                    cout << "Game contiues" << endl;
                    
                    cout << "Type anything to continue: ";
                    cin >> skipper;
                    cout << endl;
                }
            }
            else {
                string skipper;

                clear();
                
                cout << "Wrong input! Type attack or defence or their corresponding numers!" << endl;
                cout << "Type anything to continue: ";
                cin >> skipper;
                cout << endl;
            }
            
            if(player_hp <= 0)
            {
                game_end = true;
                game_won = false;
            }
            else if(enemy_hp <= 0)
            {
                game_end = true;
                game_won = true;
            }
        }

        if(game_won == true)
        {
            string skipper;
            
            clear();
            
            show_message("You have won!");
            //logsMessage = "You have won!";
            cout << "Type anything to continue: ";
            cin >> skipper;
            cout << endl;

            clear();
            
            cout << enemy_name << ": " << loose_message << endl;
            cout << "Type anything to continue: ";
            cin >> skipper;
            cout << endl;

            //add gold here :)

            currentOperation = "default";
        }
        else
        {
            string skipper;

            clear();
            
            show_message("You have lost!");
            //logsMessage = "You have lost!";
            cout << "Type anything to continue: ";
            cin >> skipper;
            cout << endl;

            clear();
            
            cout << enemy_name << ": " << win_message << endl;
            cout << "Type anything to continue: ";
            cin >> skipper;
            cout << endl;

            currentOperation = "default";
        }
    }

 Enemy generate_enemy() //Generates random enemy. Hopefuly
    {
        vector<Enemy> enemy_list; //Used vector so we wont have any issues with that annoying vector isnt used thing


        //Enemy things stats ect go like that: name, hp, dmg, defence, introduction, win monolog, loose monolog
        enemy_list[0] = Enemy("Goblin", 11, 6, 2, "I'll rob ya from ya gold. YAHAHAHA", "Got ya soul and gold. AHAHAHAHAHA", "Nooo!. I just want some shiny coins :(");
        enemy_list[1] = Enemy("Ogre", 120, 30, 9, "Me Org the Gog! Me smash small human to puddle", "Orge did what he said he would do", "NOOO! Org not loose gore win! NOOOOOO!");
        enemy_list[2] = Enemy("Walter", 1000, 50, 30, "Chemistry is the studdy of matter, but I prefer to see it as the study of change.", "Rememer to wear a respirator when cooking :3", "I am proud of you! You can cook now, all by yourself!"); //:). I had to do it
        enemy_list[3] = Enemy("Sigma", 1, 1, 1, "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU", "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU", ":(");
        enemy_list[4] = Enemy("Elf", 50, 20, 5, "I will pierce you with my bow and arrow, and then I will finish you with my sword", "You didn't even stand a chance. Poor you", "Impossible...");
        enemy_list[5] = Enemy("Zork", 160, 40, 11, "Me Zork! Me make human 2 pieces, then me make human to puddle", "Zork did what he said he would do", "ME ZORK ME NOT LOOSEE! NOOOOO! ZORK MUST WIN OR MUM IS NOT HAPPY!");
        enemy_list[6] = Enemy("Barbarrian", 60, 40, 2, "I will make you into thin slices with my swords", "Barbarrian has cut you into chips", "How did you even.. NOOOOOOOO");
        enemy_list[7] = Enemy("Palladin", 50, 20, 12, "My sword will easily cut you in half", "No shield or sword will protect you from my sword of destiny", "NOOO! EVEN DESTINY DIDN'T PROTECT ME (Destiny is his sword)");
        enemy_list[8] = Enemy("Mage", 6, 100, 0, "FIREBALL", "HAHAHAHAHA! FIREBALL! FIREBALL! F I R E B A L L", "Died 1d4 Introverted"); //Died of emotional damage 💀
        enemy_list[9] = Enemy("Spider", 20, 30, 2, "SSSSKASKKAS *translating: Can I bite you pls? It wont hurt that much :3*", "SKASSA SAKA *translating: Told ya it wont hurt that much. Anywas youll be a tasty snack :3*", "*You step on the spider killing it*");
        enemy_list[10] = Enemy("Queen spider", 100, 6, 10, "GET OUT OF MY LAND YOU LITTLE PESSANT!", "SHOULDNT HAVE CAME HERE IN THE FRIST PLACE. NOW LOOK AT YOU! ALL BROKEN AND SMASHED TO THE GROUND", "IMPOSSIBLE! KILLED BY A PESSANT! NOOOOOOOO!");
        enemy_list[11] = Enemy("Greg", 150, 30, 17, "Hi my name is Greg!", "That was a nice battle! Hope there is a cleric nearby.", "Well... Thought i couldn't be beaten. But here we are");
        enemy_list[12] = Enemy("Gnome", 10, 3, 1, "OOH!", "YAHOOOO", ":(");
        enemy_list[13] = Enemy("Executioneer", 120, 34, 7, "Can you place your head on that stand, please. It won't hurt", "Tank you for listening *cuts your head off*", "WHY ARENT YOU LISTENING TO ME *Impales himself on his axe*");
        enemy_list[14] = Enemy("Miner", 65, 15, 4, "I was strong back in my days. But the coal dust made me weak.", "Thought i would be dead. But I was wrong", "Finally peace! Thank you");
        enemy_list[15] = Enemy("Archer", 50, 50, 0, "I have never missed a shot in my life", "360 NOSCOPE HEADSHOT", "*You dodged his arrow* Whelp good game");
        enemy_list[16] = Enemy("Hunter", 130, 39, 16, "You are my pray! This will be an easy fight", "You will do as a nice decoration to my wall", "NOOOO! PlEaSe DoN't KiiL mE!");
        enemy_list[17] = Enemy("Bear", 250, 35, 17, "ROOAR *translation: LEAVE MY KIDS ALONE!*", "ROAAR *translation: THATS WHAT YOU GET FOR GETTING CLOSE TO MY KIDS*", "roar? *translation: Who will protect my little bearcubs now?*");
        enemy_list[18] = Enemy("Mugger", 110, 15, 9, "I will mugg ya", "HA HA MUGGED", ":( all I wanted is to mug you");
        enemy_list[19] = Enemy("Priest", 210, 30, 10, "DO NOT CHALLAGNE THE REALITY OF CHRISTIANITY", "CHRISTIANY RULES YOU HERETIC", "WHA... BUT ALL I DID IS ROB POOR PEOPLE");
        enemy_list[20] = Enemy("Hooligan", 70, 10, 3, "What will you do. CrY oN Me? AHHAHAAHAHAH", "PlEaSe DoNt hUrTmE! AHAHAHAA EASY YOU LITTLE PESANT", "WWWWAAAAAAAA! I SHOULD ONLY WIN! HOOOW! WAAAAAAAA!");
        enemy_list[21] = Enemy("Genious", 200, 20, 13, "The apple falls because of GRAVITY", "If you punch something, the same force is acting against you. Remember it for our next battle.", "I can't figure out how stocks work :(. Im broke now :("); //The Isac Newton accoualy got broke because of stocks. XD
        enemy_list[22] = Enemy("Blacksmith", 210, 40, 20, "Punching iron for 10 years makes you superbuff.", "OOOPS! I didn't mean to punch off the head from you.", "Bravo! Didn't expect such great battle from you");
        enemy_list[23] = Enemy("Left handed", 300, 38, 17, "Left hand is the superior one", "Nothing beats left hand", "WAIT! YOU CAN FIGHT WITH TWO HANDS! Bye!");
        enemy_list[24] = Enemy("King", 300, 30, 20, "I was the best knight in the whole kingdom. So i politely took the throne", "Knew you couldn't stand the king himself", "Impossible... HOW DID YOU BEAT ME!");
        enemy_list[25] = Enemy("Knight", 200, 25, 13, "I am loyal to the king. The best of knights", "Didn't even try", "You are worthy of the fight with the KING!");
        enemy_list[26] = Enemy("Cleric", 50, 10, 7, "I exist just to heal! Not to fight", "Whaa... Impossible! I, I HAVE WON!", "Yea, just kill me. I didn't even stand a chance.");
        enemy_list[27] = Enemy("Wolf", 130, 20, 25, "WOOF! *translating: You will be a tasty snack!*", "AUUUUU! *translating: Letss gooo!/That was easy!*", "wof? *translating: how?*"); //Huge defence because of its agility
        enemy_list[28] = Enemy("Predator", 400, 60, 40, "*Breaks a stick*", "Collects your skull. Because it was a worthy fight", "*Predator has a hart attack from your Intimidation*");
        enemy_list[29] = Enemy("AMOGUS", 150, 25, 12, "AMOGUS! *translating: PREPRARE FOR DOOM!*", "A... AMOGUS! *translating: YES!... I HAVE WON!/I AM VICRORIOUS*", "amogus. *translating: You were an opponent worthy of fighting*"); //Had a blast of inspiration :3
        enemy_list[30] = Enemy("THE GREAT MOGUS AMOGUS", 300, 49, 21, "AAAAAMMMOOOOGGGGUS! *translating: YOU THINK YOU CAN CHALLANGE ME? THE GREAT MOGUS AMOGUS? THINK TWICE ABOUT THAT!*", "Amogus. *translating: Why you just didn't give up earlier. I wouldn't hurt that much*", "A... MOGUS? *translating: WHAT!.. HOW DID THAT HAPPEN?*");
        enemy_list[31] = Enemy("Impostor", 200, 30, 9, "AMONG US! *translating: I HAVE KILLED ALL OF MY CREW WITH OUT ANYONE NOTICING SO I WILL KILL YOU TOO!*", "AAMOGUS! *translating: I WILL STAY AND ALWAYS BE VICTORIOUS*", "MOGUS!? *translating: HOW DID YOU FIND A PORTAL TO THE OUTER SPACE!?*"); //Just after i started making this character amongus drip remix started playnig on spotify XDDDDDDDd
        enemy_list[32] = Enemy("Chicken", 7, 2, 1, "POG! POG! POG! KPOOOOO! *translating: EAT! EAT! EAT! EEEEAAAAATTT!*", "POG POG POG *translating: EAT! EAT! EAT! (Im starting to wonder if that chicken knows any other words than eat)*", "POG! POG! POG! *translating: EAT! EAT! EAT!*");


        Enemy enemy = enemy_list[time(0) % enemy_list.size()];
        return enemy;
    }

    void show_message(string message) //With out my old code :(. Anyways it displays a message if you attacked or not ect i will make it look preatier later :) (the message)
    {

        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "  " << message << endl;
        cout << "--------------------------------------------------------------------------------" << endl << endl;

    }






    ///===============================================================================================================

    void logsDisplay()
    {
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "  " << logsMessage << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "\n";
    }

    void shopDisplay()
    {
        cout << endl << "  Shop Stock:" << endl;
        S->display();
        cout << "\n\n";
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
        delete S;
    }
};

int main()
{

    Game game;
    game.run();

    return 0;
}
