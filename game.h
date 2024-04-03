#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <exception>
using namespace std;

//Angeline Vu, 03/05/2024, CS302-001, Program 3
//This program keeps a collection of different kinds of games.
//Namely, videogames, card games, and board games. 

//This file has class interfaces, prototypes

//Abstract base class for game. With protected members name
//genre, skill, number of players, and rating

//Terminantes program: displays message and exits
void user_terminate();

//Exception handling functions
char failed_int();
int range_int();
int empty_string();
int failed_display();
int failed_bool();
int dupe_game();

//Interface functions
char menu();
char game_menu();
void get_string(string & search);
int get_int();

//Abstract Base Class. Has fields name, genre, skill, number of players,
//and rating of the game. Has overlaoded functions for << and >>. Several 
//Search functions and a special display function.
class game
{
    public:	
        game();							//Default Constructor
        virtual int display() const;	//Display function
        virtual int set();		        //Set function

        virtual int search_string(const string & find) const;	//Search for a string
        virtual int search_int(const int find) const;   		//Search for an int
        virtual int search_parts(const string & find) = 0;  	//Search components for match

        bool less_than(const game &);		//Compare names
        bool less_than(const string &);		
        bool match(const game &); 
        bool match(const string &); 

        virtual ~game();					//Destructor

    protected:
        string name;			//Name of the game
        string genre;			//Genre of the game
        int skill;				//Degree of of difficulty
        int players;			//Number of players
        int rating;				//Rating of game
};

//Derived class videogame with private members platforms
//and devices. Has unique function to check if it's crossplay;
//private members: platforms the game supports, is crossplay or
//not, and number of devices playing at a time
class video : public game
{
    public:
        video();					//Constructor
        int display() const;		//Display
        int set();					//Get values
        int search_string(const string & find) const;   //Search for a string
        int search_int(const int find) const;		    //Search for an int
        int search_parts(const string & find);	    	//Search components for match
        bool xplay();   			//Supports crossplay?
        ~video();					//Destructor

    private:
        string platforms;		//e.g. Xbox, PC
        bool xplatform;			//Supports crossplay
        int devices;			//How many devices available
};

//Card game derived from game with private members
//type of card, how many people can play per deck, how
//many decks are available
class card : public game
{
    public:
        card();						//Constructor
        int display() const;		//Display
        int set();					//Get values
        int search_string(const string & find) const;	//Search for a string
        int search_int(const int find) const;   		//Search for an int
        int search_parts(const string & find);  		//Search components for match
        ~card();					//Destructor

    private:
        string type;		//Type of (e.g. standard, UNO)
        int decks;			//Number of decks needed
};

//Class board derived from game with private members
//types of pieces, pieces per person, and available pieces
class board : public game
{
    public:
        board();					//Constructor
        int display() const;		//Display
        int set();					//Get values
        int search_string(const string & find) const;//Search for a string
        int search_int(const int find) const;		//Search for an int
        int search_parts(const string & find);		//Search components for match
        ~board();					//Destructor

    private:
        vector<string> pieces;		//Type of (e.g. dice)
        vector<int> piece_count;	//Number of pieces
};
