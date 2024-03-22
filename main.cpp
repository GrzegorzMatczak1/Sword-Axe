#include <iostream>
//#include <vector>
#include <string>
//#include <iomanip>
#include <cctype> //I KNOW THAT THE INCLUDES ARE VERRY MESSY
#include <cstdlib>
#include <stdlib.h>
#include <memory>



using namespace std;

class Item //Item class
{
public:
    int id;           //its only used for testing reasons
    string name;
    string display_name; //name that will be displayed in the inventory
    string item_type; //like general, sword, axe, shield, helmet
    string slot_type; //like armor, weapon, shield
    int base_damage;  //how much damage the weapon normaly deals
    int base_defence; //how much does the item remove from damage
    string quality;   //Its like rarity but diffrent :) it just boost item stats like attack or defence
    int amount;       //amount of an item
    int durability;   //durability of an item
    string* traits;   // a list of 4 traits
    Item(int id = 0, string name = "NAN", string display_name = "!",  string item_type = "general", string slot_type = "NAN", int base_damage = 0, int base_defence = 0, string quality = "normal", int amount = 1, int durability = 10, string trait1 = "NAN", string trait2 = "NAN", string trait3 = "NAN", string trait4 = "NAN") : name{name}, display_name{display_name}, id{id}, item_type{item_type}, slot_type{slot_type}, base_damage{base_damage}, base_defence{base_defence}, quality{quality}, amount{amount}, durability{durability} //Item constructor
    {
        traits = new string[4];
        traits[0] = trait1;
        traits[1] = trait2;
        traits[2] = trait3;
        traits[3] = trait4;
    }
    void add_trait(string trait_name, int trait_slot = 1)
    {
        if(trait_slot - 1 <= 0)
        {
            traits[0] = trait_name;
        }
        else if(trait_slot - 1 >= 3)
        {
            traits[3] = trait_name;
        }
        else if(trait_slot - 1 == 1)
        {
            traits[1] = trait_name;
        }
        else if(trait_slot - 1 == 2)
        {
            traits[2] = trait_name;
        }
    }
};

class Inventory //Inventory Class
{
public:
    Item*** tab; //tab is the main inventory
    Item** battle_slots; //for the slots like shield weapon ect
    int rows;
    int cols;
    string letters;
    Inventory(int rows = 4, int cols = 9) : rows{rows}, cols{cols} //Inventory Constructor
    {
        tab = new Item**[rows];
        letters = "ABCDEFGHIJKRSTUVWYZ";
        int a = 0;
        for(int i = 0; i < rows; i++)
        {
            tab[i] = new Item*[cols];
        }

        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                tab[i][j] = new Item(a, "NAN"); //NAN means Not A Name which lets me hide the item later
                a++;
            }
        }
        battle_slots = new Item*[6];
        battle_slots[0] = new Item(44, "NAN", "☺", "helmet", "helmet"); //PROBLEMATIC LINE idk i saved and everything worked again XDDDD
        battle_slots[1] = new Item(45, "NAN", "⍞", "chestplate", "chestplate");
        battle_slots[2] = new Item(46, "NAN", "ℿ", "leggings", "leggings");
        battle_slots[3] = new Item(47, "NAN", "ೲ", "boots", "boots");
        battle_slots[4] = new Item(48, "NAN", "⸸", "NAN", "weapon");
        battle_slots[5] = new Item(49, "NAN", "⛉", "shield", "shield");

    }
    ~Inventory() //Inventory Destructor
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                delete tab[i][j];
            }
        }
        for(int i = 0; i < rows; i++)
        {
            delete[] tab[i];
        }
        delete[] tab;

    }
    void display_name()
    {
        cout << "------------------------------------------------------" << endl; // Spacer: its used to separate the code and makes it easier to see changes to the inventory
        cout << "  ";
        for(int y = 0; y < cols; y++)
        {
            cout << "  " << y + 1 << "   ";
        }
        cout << endl;
        for(int i = 0; i < rows; i++)
        {
            cout << letters[i] << "  ";
            for(int j = 0; j < cols; j++)
            {
                if(tab[i][j]->name == "NAN") //Its used to make blank spaces instead of making no item (it was easier to code in a lesson)
                {
                    cout << "[ ]   ";
                }
                else
                {
                    cout << "[" << tab[i][j]->display_name << "]   ";
                }
            }
            cout << endl;
        }
        cout << "X  ";
        for(int a = 0; a < 6; a++) // a because of armor
        {
            if(battle_slots[a]->name == "NAN")
            {
                cout << "{ }   ";
            }
            else
            {
                cout << "{" << battle_slots[a]->display_name << "}   ";
            }
        }
        cout << endl;
    }
    void display_id() //Used for testing reasons (to show if the items are added corectly)
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                cout << "[" << tab[i][j]->id << "]  ";
            }
            cout << endl;
        }
    }

    void add_item_test(int row_cords, int col_cords) //This code adds temprorary items to the inventory
    {
        tab[row_cords - 1][col_cords - 1] = new Item(11, "!");
    }

    int translate_rows(char letter) //This code is used to translade A B inputs to letters
    {
        for(int i = 0; i < letters.size(); i++)
        {
            if(letters[i] == letter)
            {
                return i + 1;
            }
        }
        return -1;
    }

    void swap_item(char row_cords1, int col_cords1, char row_cords2, int col_cords2) //I am using rows1 ect to make my brain visualate the code
    {
        char row_cords1_upper = toupper(row_cords1); //making inputs uppercase because the display board (letters string) is made of capital letters
        char row_cords2_upper = toupper(row_cords2);

        int row_trans1 = translate_rows(row_cords1_upper); //translating A, B to numbers so it would be 1, 2
        int row_trans2 = translate_rows(row_cords2_upper);

        int col_cords1_smol = col_cords1 - 1;
        int col_cords2_smol = col_cords2 - 1;

        unique_ptr<int[]> free_spot(new int[2]);


        string* slot_type_list = new string[7];
        slot_type_list[0] = "helmet";
        slot_type_list[1] = "chestplate";
        slot_type_list[2] = "leggings";
        slot_type_list[3] = "boots";
        slot_type_list[4] = "weapon";
        slot_type_list[5] = "shield";
        slot_type_list[6] = "general";

        //cout<<"GOT HERE1" << endl;

        if(((row_trans1 == -1) && (row_cords1_upper != 'X')) || ((row_trans2 == -1) && (row_cords2_upper != 'X')))
        {
            cout << "Incorrect row value! You should enter cordinates like in chess for example: a1, b3" << endl;

        }

        else if((row_cords1_upper == 'X') && (row_cords2_upper == 'X'))
        {
            cout << "YOU CAN NOT SWAP ITEMS IN THIS INVENTORY" << endl;

        }
        //cout<<"GOT HERE2" << endl;
        else if(row_cords1_upper == 'X')
        {
            if((tab[row_trans2 - 1][col_cords2 - 1]->slot_type == "helmet") && (slot_type_list[col_cords1 - 1] == "helmet"))
            {
                swap(battle_slots[col_cords1 - 1], tab[row_trans2 - 1][col_cords2 - 1]);
            }
            else if((tab[row_trans2 - 1][col_cords2 - 1]->slot_type == "chestplate") && (slot_type_list[col_cords1 - 1] == "chestplate"))
            {
                swap(battle_slots[col_cords1 - 1], tab[row_trans2 - 1][col_cords2 - 1]);
            }
            else if((tab[row_trans2 - 1][col_cords2 - 1]->slot_type == "leggings") && (slot_type_list[col_cords1 - 1] == "leggings"))
            {
                swap(battle_slots[col_cords1 - 1], tab[row_trans2 - 1][col_cords2 - 1]);
            }
            else if((tab[row_trans2 - 1][col_cords2 - 1]->slot_type == "boots") && (slot_type_list[col_cords1 - 1] == "boots"))
            {
                swap(battle_slots[col_cords1 - 1], tab[row_trans2 - 1][col_cords2 - 1]);
            }
            else if((tab[row_trans2 - 1][col_cords2 - 1]->slot_type == "weapon") && (slot_type_list[col_cords1 - 1] == "weapon"))
            {


                if(tab[row_trans2 - 1][col_cords2 - 1]->item_type == "axe")
                {
                    int* free_spot = find_smallest_free_spot();


                    if((free_spot[0] == -1) || (free_spot[1] == -1))
                    {
                        cout << "INVENTORY IS FULL CAN NOT SWAP ITEM AXE WITH SHIELD" << endl;

                    }
                    else
                    {
                        swap(battle_slots[col_cords1 - 1], tab[row_trans2 - 1][col_cords2 - 1]);
                        swap(battle_slots[5], tab[free_spot[0]][free_spot[1]]);                    //DONT LISTEN TO POTETNIAL MEMORY LEAKS

                    }
                }
                else
                {
                    swap(battle_slots[col_cords1 - 1], tab[row_trans2 - 1][col_cords2 - 1]);

                }

            }
            else if((tab[row_trans2 - 1][col_cords2 - 1]->slot_type == "shield") && (slot_type_list[col_cords1 - 1] == "shield"))
            {
                if(battle_slots[4]->item_type == "axe")
                {
                    cout << "CANNOT SWAP ITEMS. AXE IS EQUIPED" << endl;
                }
                else
                {
                    swap(battle_slots[col_cords1 - 1], tab[row_trans2 - 1][col_cords2 - 1]);
                }
            }
            else
            {
                cout << "CANNOT SWAP ITEMS. WRONG ITEM TYPE" << endl;

            }
        }
        //cout<<"GOT HERE3" << endl;
        else if(row_cords2_upper == 'X')
        {
            //cout<<"GOT HERE11" << endl;
            if((tab[row_trans1 - 1][col_cords1 - 1]->slot_type == "helmet") && (slot_type_list[col_cords2 - 1] == "helmet"))  // this part crashes my program HERE
            {
                swap(tab[row_trans1 - 1][col_cords1 - 1], battle_slots[col_cords2 - 1]);
            }
            //cout<<"GOT HERE12" << endl;
            else if((tab[row_trans1 - 1][col_cords1 - 1]->slot_type == "chestplate") && (slot_type_list[col_cords2 - 1] == "chestplate"))
            {
                swap(tab[row_trans1 - 1][col_cords1 - 1], battle_slots[col_cords2 - 1]);
            }
            //cout<<"GOT HERE13" << endl;
            else if((tab[row_trans1 - 1][col_cords1 - 1]->slot_type == "leggings") && (slot_type_list[col_cords2 - 1] == "leggings"))
            {
                swap(tab[row_trans1 - 1][col_cords1 - 1], battle_slots[col_cords2 - 1]);
            }
            //cout<<"GOT HERE14" << endl;
            else if((tab[row_trans1 - 1][col_cords1 - 1]->slot_type == "boots") && (slot_type_list[col_cords2 - 1] == "boots"))
            {
                swap(tab[row_trans1 - 1][col_cords1 - 1], battle_slots[col_cords2 - 1]);
            }
            //cout<<"GOT HERE15" << endl;
            else if((tab[row_trans1 - 1][col_cords1 - 1]->slot_type == "weapon") && (slot_type_list[col_cords2 - 1] == "weapon"))
            {

                if(tab[row_trans1 - 1][col_cords1 - 1]->item_type == "axe")
                {

                    if((free_spot[0] == -1) || (free_spot[1] == -1))
                    {
                        cout << "INVENTORY IS FULL CAN NOT SWAP ITEM" << endl;

                    }
                    else
                    {
                        swap(tab[row_trans1 - 1][col_cords1 - 1], battle_slots[col_cords2 - 1]);
                        swap(battle_slots[5], tab[free_spot[0]][free_spot[1]]);                 //DONT LISTEN TO POTETNIAL MEMORY LEAKS

                    }
                }
                else
                {
                    //cout<<"GOT HERE6" << endl;
                    swap(tab[row_trans1 - 1][col_cords1 - 1], battle_slots[col_cords2 - 1]);
                    //cout<<"GOT HERE7" << endl;
                }
            }
            //cout<<"GOT HERE16" << endl;
            if((tab[row_trans1 - 1][col_cords1 - 1]->slot_type == slot_type_list[5]) && (slot_type_list[col_cords2 - 1] == slot_type_list[5]))
            {
                if(battle_slots[4]->item_type == "axe")
                {
                    cout << "CANNOT SWAP ITEMS. AXE IS EQUIPED" << endl;
                }
                else
                {
                    swap(tab[row_trans1 - 1][col_cords1 - 1], battle_slots[col_cords2 - 1]);
                }
            }
            else if((tab[row_trans1 - 1][col_cords1 - 1]->slot_type == slot_type_list[6]))
            {
                cout << "CANNOT SWAP ITEMS. WRONG ITEM TYPE" << endl;


            }
        }
        //cout<<"GOT HERE4" << endl;
        else if((row_trans1 > rows) || (row_trans2 > rows))
        {
            cout << "Row input to big" << endl;

        }
        //cout<<"GOT HERE5" << endl;
        else if((col_cords1 > cols) || (col_cords2 > cols))
        {
            cout << "Cols input to big" << endl;

        }

        else
        {
            swap(tab[row_trans1 - 1][col_cords1 - 1], tab[row_trans2 - 1][col_cords2 - 1]); // Almost forgot to swich the rows_cords to translated ones XDDD

        }
    }

    int* find_smallest_free_spot()
    {
        int* cords = new int[2];
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(tab[i][j]->name == "NAN")
                {
                    cords[0] = i;
                    cords[1] = j;
                    return cords;
                }
            }
        }
        cords[0] = -1;
        cords[1] = -1;
        return cords;
    }
    //had to add id because i had to :(
    void add_specific_item(int id = 0, string name = "NAN", string display_name = "!", string item_type = "general", string slot_type = "NAN", int base_damage = 0, int base_defence = 0, string quality = "normal", int amount = 1, int durability = 10, string trait1 = "NAN", string trait2 = "NAN", string trait3 = "NAN", string trait4 = "NAN")
    {
        int* smallest_item = find_smallest_free_spot();
        if(smallest_item[0] == -1 or smallest_item[1] == -1) //its the same as free spot ealier
        {
            cout << "INVENTORY IS FULL! ITEM LOST!" << endl;
        }
        else
        {
            tab[smallest_item[0]][smallest_item[1]]  = new Item(11, name, display_name, item_type, slot_type, base_damage, base_defence, quality, amount, durability, trait1, trait2, trait3, trait4);
        }
    }

    void add_random_item()
    {
        int* smallest_item = find_smallest_free_spot();
        if(smallest_item[0] == -1 or smallest_item[1] == -1) //its the same as free spot ealier
        {
            cout << "INVENTORY IS FULL! ITEM LOST!" << endl;
        }
        else
        {

            //random_device rd; //this code creates random engine
            //mt19937 gen(rd());  // Mersenne Twister pseudo-random generator


            //uniform_int_distribution<> dis(1, 100);
            //int id = arc4random % 101 //id doesnt work :(
            string* names_list;
            string* display_names_list;
            string* slot_type_list;
            int truethful = 0; //Always tells truth


            //item name
            names_list = new string[11]; //IM SO STUPID I ENTERED HERE 10 INSTEAD OF 11 XXDDDDD

            names_list[0] = "THE LEGENDARY AXOMOGON SWORD";
            names_list[1] = "ICE BREAKER";
            names_list[2] = "MONEY";
            names_list[3] = "NOKIA 3310 ON A STICK";
            names_list[4] = "Jacek";
            names_list[5] = "ROBHERTHUS"; // aka bob
            names_list[6] = "Amoonguss";
            names_list[7] = "BIG BERTHA";
            names_list[8] = "Mieczyk";
            names_list[9] = "EIKMANANAB";
            names_list[10] = "GIANT TOTINO"; // i sencerly apologise for these names



            string name = names_list[arc4random() % 11];


            //display names
            display_names_list = new string[6]; //SAME HERE LMAOOO
            display_names_list[0] = "!";
            display_names_list[1] = "P";
            display_names_list[2] = "S";
            display_names_list[3] = "K";
            display_names_list[4] = "R";
            display_names_list[5] = "U";



            string display_name = display_names_list[arc4random() % 6];

            //slot types
            slot_type_list = new string[7];
            slot_type_list[0] = "general";
            slot_type_list[1] = "weapon";
            slot_type_list[2] = "helmet";
            slot_type_list[3] = "chestplate";
            slot_type_list[4] = "leggings";
            slot_type_list[5] = "boots";
            slot_type_list[6] = "shield";



            string slot_type = slot_type_list[arc4random() % 7];

            //item types
            string item_type;
            string* item_type_list;

            if(slot_type == "weapon")
            {
                item_type_list = new string[2];
                item_type_list[0] = "axe";
                item_type_list[1] = "sword";

                item_type = item_type_list[arc4random() % 2];
            }
            else if(slot_type == "shield")
            {
                item_type = "shield";
            }
            else if(slot_type == "helmet")
            {
                item_type = "helmet";
            }
            else if(slot_type == "chestplate")
            {
                item_type = "chestplate";
            }
            else if(slot_type == "leggings")
            {
                item_type = "leggings";
            }
            else if(slot_type == "boots")
            {
                item_type = "boots";
            }
            else
            {
                item_type = "NAN";
            }

            int base_damage = 0;
            int base_defence = 0;

            if(slot_type == "weapon")
            {
                base_damage = arc4random() % 21;

            }
            else if(slot_type != "NAN" and slot_type != "weapon")
            {
                base_defence = arc4random() % 21;
            }


            string quality;
            string* quality_list;
            quality_list = new string[6];
            quality_list[0] = "normal";
            quality_list[1] = "common";
            quality_list[2] = "uncommon";
            quality_list[3] = "rare";
            quality_list[4] = "epic";
            quality_list[5] = "legendary";



            int rarity = arc4random() % 101;
            if(rarity > 0 and rarity <= 20)
            {
                quality = quality_list[0];
            }
            else if(rarity > 20 and rarity <= 35)
            {
                quality = quality_list[1];
            }
            else if(rarity > 35 and rarity <= 50)
            {
                quality = quality_list[2];
            }
            else if(rarity > 50 and rarity <= 75)
            {
                quality = quality_list[3];
            }
            else if(rarity > 75 and rarity <= 90)
            {
                quality = quality_list[4];
            }
            else if(rarity > 90 and rarity <= 100)
            {
                quality = quality_list[5];
            }

            int amount = 1;

            int durability = 10 + (arc4random() % 51);

            string* trait_list;
            trait_list = new string[16];
            trait_list[0] = "destroyed";
            trait_list[1] = "blunt";
            trait_list[2] = "jagged edge";
            trait_list[3] = "sharp";
            trait_list[4] = "damascus steel";
            trait_list[5] = "perfectly balanced"; //spiffing brit refrence XD
            trait_list[6] = "tuff";
            trait_list[7] = "heavy";
            trait_list[8] = "badly forged";
            trait_list[9] = "light";
            trait_list[10] = "bad materials";
            trait_list[11] = "uncomfortable handle";
            trait_list[12] = "AMONGUS";
            trait_list[13] = "flaming edge";
            trait_list[14] = "made in china";
            trait_list[15] = "rusty";

            int traits_random_num1 = arc4random() % 101;
            int traits_random_num2 = arc4random() % 101;
            int traits_random_num3= arc4random() % 101;
            int traits_random_num4 = arc4random() % 101;
            string trait1 = "NAN";
            string trait2 = "NAN";
            string trait3 = "NAN";
            string trait4 = "NAN";

            if(traits_random_num1 == 14 or traits_random_num1 == 71 or traits_random_num1 == 33)
            {
                trait1 = trait_list[arc4random() % 16];
            }
            if(traits_random_num2 == 4 or traits_random_num2 == 20 or traits_random_num2 == 69)
            {
                trait2 = trait_list[arc4random() % 16];
            }
            if(traits_random_num3 == 98 or traits_random_num3 == 43 or traits_random_num3 == 34)
            {
                trait3 = trait_list[arc4random() % 16];
            }
            if(traits_random_num4 == 8 or traits_random_num4 == 16 or traits_random_num4 == 32)
            {
                trait4 = trait_list[arc4random() % 16];
            }



            int id = arc4random() % 101;



            tab[smallest_item[0]][smallest_item[1]] = new Item(id, name, display_name, item_type, slot_type, base_damage, base_defence, quality, amount, durability, trait1, trait2, trait3, trait4);

        }

    }

    bool has_traits_battle(int col_cords)
    {
        for(int i = 0; i < 4; i++)
        {
            if(battle_slots[col_cords]->traits[i] != "NAN")
                return true;
        }
        return false;
    }

    bool has_traits_tab(int row_cords, int col_cords)
    {
        for(int i = 0; i < 4; i++)
        {
            if(tab[row_cords][col_cords]->traits[i] != "NAN")
                return true;
        }
        return false;
    }

    void show_stats(char row_cords, int col_cords)
    {
        cout << "-----------------------------" << endl;
        cout << "Item stats:" << endl;
        char row_cords_upper = toupper(row_cords);

        int row_trans = translate_rows(row_cords_upper);

        if(row_trans == -1)
        {
            cout << "Incorrect row value! You should enter cordinates like in chess for example: a1, b3" << endl;
        }
        else if(row_trans > rows)
        {
            cout << "Row input to big" << endl;
        }
        else if(col_cords > cols)
        {
            cout << "Cols input to big" << endl;
        }
        else if(row_cords_upper == 'X')
        {
            col_cords = col_cords - 1;
            if(battle_slots[col_cords]->name == "NAN")
            {
                cout << "ITS AN EMPTY SLOT" << endl;
            }
            else
            {
                cout << "Name: " << battle_slots[col_cords]->name << endl;
            }
            cout << "Item type: " << battle_slots[col_cords]->item_type << endl;
            if(battle_slots[col_cords]->slot_type != "NAN")
            {
                cout << "Slot type: " << battle_slots[col_cords]->slot_type << endl;
            }
            if(battle_slots[col_cords]->base_damage != 0)
            {
                cout << "Base damage: " << battle_slots[col_cords]->base_damage << endl;
            }
            if(battle_slots[col_cords]->base_defence != 0)
            {
                cout << "Base defence: " << battle_slots[col_cords]->base_defence << endl;
            }
            if(battle_slots[col_cords]->quality != "normal")
            {
                cout << "Quality: " << battle_slots[col_cords]->quality << endl;
            }
            cout << "Durability: " << battle_slots[col_cords]->durability << endl;

            if(has_traits_battle(col_cords))
            {
                cout << "Traits:" << endl;
                int adder = 1;
                for(int i = 0; i < 4; i++)
                {
                    if(battle_slots[col_cords]->traits[i] != "NAN")
                    {
                        cout << adder << " trait: " << battle_slots[col_cords]->traits[i] << endl;
                        adder++;
                    }
                }
            }
        }
        else
        {
            row_trans = row_trans - 1;
            col_cords = col_cords - 1;

            if(tab[row_trans][col_cords]->name == "NAN")
            {
                cout << "ITS AN EMPTY SLOT" << endl;
            }
            else
            {
                cout << "Name: " << tab[row_trans][col_cords]->name << endl;

                cout << "Item type: " << tab[row_trans][col_cords]->item_type << endl;
                if(tab[row_trans][col_cords]->slot_type != "NAN")
                {
                    cout << "Slot type: " << tab[row_trans][col_cords]->slot_type << endl;
                }
                if(tab[row_trans][col_cords]->base_damage != 0)
                {
                    cout << "Base damage: " << tab[row_trans][col_cords]->base_damage << endl;
                }
                if(tab[row_trans][col_cords]->base_defence != 0)
                {
                    cout << "Base defence: " << tab[row_trans][col_cords]->base_defence << endl;
                }
                if(tab[row_trans][col_cords]->quality != "normal")
                {
                    cout << "Quality: " << tab[row_trans][col_cords]->quality << endl;
                }
                cout << "Durability: " << tab[row_trans][col_cords]->durability << endl;

                if(has_traits_tab(row_trans, col_cords))
                {
                    cout << "Traits:" << endl;
                    int adder = 1;
                    for(int i = 0; i < 4; i++)
                    {
                        if(tab[row_trans][col_cords]->traits[i] != "NAN")
                        {
                            cout << adder << " trait: " << tab[row_trans][col_cords]->traits[i] << endl;
                            adder++;
                        }
                    }
                }
            }
        }



    }

    void force_swap()
    {
        auto temp = tab[0][4];
        tab[0][4] = battle_slots[4];
        battle_slots[4] = temp;
    }
};


int main()
{
    //auto sth = new Inventory(); //forgot how to do classes properly :skull:
    //sth->display_name();
    Inventory something(4, 9); //Create inventory

    something.add_item_test(2, 6); //Adding test item (Yea with these old cords)
    something.display_name();



    something.swap_item('B', 6, 'C', 6); //Apparently '' and "" has a difference the '' is used for chars and "" is used for string XD
    something.swap_item('C', 6, 'a', 1);

    something.add_random_item();
    something.add_random_item();

    something.add_specific_item(0,"something", "F", "sword", "weapon");
    something.display_name();

    something.swap_item('A', 4, 'X', 5); //its crashing when im trying to execute this command

    //something.force_swap();

    something.display_name();
    something.show_stats('A', 3);

    return 0;
}
