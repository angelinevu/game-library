#include "game.h"

//Angeline Vu, 03/05/2024, CS302-001, Program 3
//This file has functions related to the client and user
//interface

//Main menu
char menu()
{
    char selection = ' ';
    do
    {
        cout << "\n一一一一一一一一一"
            "\nGame Library\n"
            "\n1. Insert Game"
            "\n2. Display All"
            "\n3. Find Word"
            "\n4. Find Number"
            "\n5. Find Component"
            "\n6. Search Crossplay"
            "\n7. Quit\n"
            "\nSelection: ";
        cin >> selection;
        cin.ignore(100, '\n');
    } while (selection < '1' || selection > '7');
    return selection;
}

//Submenu: choose what kind of game to add
char game_menu()
{
    char selection = ' ';
    do
    {
        cout << "\n一一一一一一一一一"
            "\nInsert Game\n"
            "\n1. Videogame"
            "\n2. Card Game"
            "\n3. Boardgame\n"
            "\nSelection: ";
        cin >> selection;
        cin.ignore(100, '\n');
    } while (selection < '1' || selection > '3');
    return selection;
}

//Get a string from the user
void get_string(string & search)
{
    cout << "Enter a word: ";
    getline(cin >> ws, search);
    return;
}

//Get an integer from the user
int get_int()
{
    int search;
    cout << "Enter a number: ";
    if (!(cin >> search))
        throw failed_int();
    return search;
}

//Terminantes program: displays message and exits
void user_terminate()
{
    cout << "\nError. Terminating Program \n\n.";
    exit(1);
}

//Exception functions: displays message detailing
//what error occurred. Notice different return type for
//failed integer (will require some action when caught)
char failed_int()
{
    cout << "\nInvalid Input: integer expected.\n";
    return '0';
}

int range_int()
{
    cout << "\nInvalid Input: out of range.\n";
    return 0;
}

int empty_string()
{
    cout << "\nInvalid Input: empty string.\n";
    return 0;
}

int failed_display()
{
    cout << "\nDisplay Error: game fields are invalid.\n";
    return 0;
}

int failed_bool()
{
    cout << "\nInvalid Input: 'yes' or 'no' expected.\n";
    return 0;
}

int dupe_game()
{
    cout << "\nInvalid Input: duplicate game entered.\n";
    return 0;
}
