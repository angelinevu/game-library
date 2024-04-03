#include "game.h"

//Angeline Vu, 03/05/2024, CS302-001, Program 3

//Game class methods
//Default constructor: sets value of all members to 0
game::game() : name(""), genre(""), skill(0), players(0), rating(0) {}

//Search function: searches all string fields for a match;
//Displays all with match
int game::search_string(const string & find) const
{
    if (name.find(find) != string::npos)	//Match
        return 1;

    if (genre.find(find) != string::npos)	//Match
        return 1;

    return 0;
}

//Search function: searches all integer fields for a match;
//Displays all with match
int game::search_int(const int find) const
{
    if (find == skill || find == players || find == rating)	//Do any fields match?
        return true;

    return false;
}

//Display all fields: name, genre, skill, players, rating
int game::display() const
{
    if (name == "" || genre == "" || skill < 1 || skill > 5 || players < 1 || rating < 1 || rating > 5)
        throw failed_display();

    cout << "\nName: " << name		//Display name
        << "\nGenre: " << genre		//Display genre
        << "\nSkill: " << skill		//Display skill
        << "\nPlayers: " << players	//Display players
        << "\nRating: " << rating;	//Display rating
    return 1;
}

//Set value of all fields: name, genre, skill, players, rating
int game::set()
{
    cout << "\nName: ";		//Sets name
    getline(cin >> ws, name);
    if (name == "") 		//Empty
        throw empty_string();

    cout << "Genre: ";		//Sets genre	
    getline(cin >> ws, genre);		
    if (genre == "")		//Empty
        throw empty_string();

    cout << "Skill (1-5): ";	//Sets skill
    if (!(cin >> skill))		//Noninteger
        throw failed_int();
    if (skill < 1 || skill > 5)	//Out of range
        throw range_int();

    cout << "Players (1+): ";	//Sets players
    if (!(cin >> players))		//Noninteger
        throw failed_int();
    if (players < 1)		//Out of range
        throw range_int();

    cout << "Rating (1-5): ";	//Sets rating
    if (!(cin >> rating))		//Noninteger
        throw failed_int();
    if (rating < 1 || rating > 5)	//Out of range
        throw range_int();

    return 1;
}

//Compares name of game, returns true if object is less
//than object
bool game::less_than(const game & source)
{
    if (name < source.name)
        return 1;

    return 0;
}

//Compares name to string, returns true if object is
//less than object
bool game::less_than(const string & compare)
{
    if (name < compare)
        return 1;

    return 0;
}

//Compares name to string, returns true if match
bool game::match(const string & find)
{
    if (name == find)
        return 1;
    return 0;
}

//Compares 2 games via name key, returns true if match
bool game::match(const game & source)
{
    if (name == source.name)
        return 1;
    return 0;
}

//Destructor: sets all values to 0 equivalent value
game::~game()
{
    name = genre = "";
    skill = players = rating = 0;
}

//Videogame class methods
//Default constructor: sets value of all members to 0
video::video() : platforms(""), xplatform(false), devices(0) {}

//Search for a string
int video::search_string(const string & find) const
{
    if (game::search_string(find))	//In parent field?
        return 1;

    if (platforms.find(find) != string::npos)	//Found
        return 1;

    return 0;
}

//Search for an int
int video::search_int(const int find) const
{
    if (game::search_int(find))	//Parent match?
        return 1;

    if (devices == find)		//Match?
        return 1;

    return 0;
}

//Search components for match
int video::search_parts(const string & find)
{
    if (find == "")				//Empty string
        throw empty_string();

    if (platforms.find(find) != string::npos)	//Found
        return 1;

    return 0;
}

//Supports crossplay?
bool video::xplay()
{
    return xplatform;
}

//Display all fields. 
int video::display() const
{
    game::display();

    if (platforms == "" || devices < 1)	//Bad data
        throw failed_display();

    cout << "\nPlatforms: " << platforms;
    if (xplatform)
        cout << "\nCrossplay Available";
    cout << "\nDevices: " << devices << endl;

    return 1;
}

//Get values
int video::set()
{
    game::set();
    cout << "Platforms: ";		//Platforms
    getline(cin >> ws, platforms);
    if (platforms == "")		//Empty string
        throw empty_string();

    string input;
    cout << "Crossplatform (yes/no): ";	//Xplatform
    getline(cin >> ws, input);

    if (input != "yes" && input != "no")	//Not yes or no
        throw failed_bool();

    if (input == "yes")			//Set xplatform
        xplatform = true;
    else 
        xplatform = false;

    cout << "Number of Devices (1+): ";	//Devices
    if (!(cin >> devices))			//!int
        throw failed_int();
    if (devices < 1)			//!range
        throw range_int();

    return 1;
}

//Destructor
video::~video()
{
    platforms = "";
    xplatform = false;
    devices = 0;
}

//Card class
//Default constructor: sets data to zero equivalent
card::card() : type(""), decks(0) {}

//Search for a string
int card::search_string(const string & find) const
{
    if (game::search_string(find))	//In parent field?
        return 1;

    if (type.find(find) != string::npos)	//Found
        return 1;

    return 0;
}

//Search for an int
int card::search_int(const int find) const
{
    if (game::search_int(find))	//Parent match?
        return 1;

    if (find == decks)
        return 1;

    return 0;
}

//Search components for match
int card::search_parts(const string & find)
{
    if (find == "")
        throw empty_string();

    if (type.find(find) != string::npos)	//Found
        return 1;

    return 0;
}

//Display: displays card type and number of decks
int card::display() const
{
    game::display();			//Call parent's display
    if (type == "" || decks < 1)		//Invalid input
        throw failed_display();

    cout << "\nCard Type: " << type
        << "\nNumber of Decks: " << decks << endl;
    return 1;
}

//Get values card type and number of decks from the user
int card::set()
{
    game::set();

    cout << "Card Type (e.g. Standard 52): ";	//Type
    getline(cin >> ws, type);
    if (type == "")			//Empty string
        throw empty_string();

    cout << "Number of Decks (1+): ";	//Decks
    if (!(cin >> decks))			//!int
        throw failed_int();
    if (decks < 1)				//!range
        throw range_int();

    return 1;	
}

//Destructor: sets all values to zero equivalent
card::~card()
{
    type = "";
    decks = 0;
}

//Board class
//Default Constructor
board::board() {}

//Search for a string in pieces vector
int board::search_string(const string & find) const
{
    if (game::search_string(find))	//In parent field?
        return 1;

    bool found;
    for (auto i = pieces.begin(); i < pieces.end(); ++i)
    {
        if (*i == find)
            found = true;
    }
    return found;
}

//Search for an int in piece_count vector
int board::search_int(const int find) const
{
    if (game::search_int(find))	//Parent match?
        return 1;

    bool found;
    for (auto i = piece_count.begin(); i < piece_count.end(); ++i)
    {
        if (*i == find)
            found = true;
    }
    return found;
}

//Search components for match
int board::search_parts(const string & find)
{
    bool found;
    for (auto i = pieces.begin(); i < pieces.end(); ++i)
    {
        if (*i == find)
            found = true;
    }
    return found;
}

//Display: formatted display
//Potential Output:
//1 board
//3 dice
int board::display() const
{
    game::display();
    cout << "\nParts:\n";
    if (pieces.size() != piece_count.size())
        throw failed_display();
    for (int i = 0; i < pieces.size(); ++i)
        cout << " - "  << piece_count[i] << ' ' << pieces[i] << endl;
    return 1;
}

//Get values: pieces indicate the type of pieces that are needed
//in the board game (e.g. dice). Piece count indicates the number
//of each type is needed. It is ordered by same index: pieces[0]
//will need piece_count[0] number.
int board::set()
{
    game::set();		//Call parent class << operator

    int count = 0;
    string str_temp = "";	//Temporary hold to 
    int int_temp = 0;

    cout << "Enter number of types of pieces (1+): ";	//How many entries?
    if (!(cin >> count))
        throw failed_int();
    if (count < 1)
        throw range_int();

    for (int i = 0; i < count; ++i)
    {
        cout << "\nEnter piece type: ";
        getline(cin >> ws, str_temp);
        if (str_temp == "")			//Empty string error
            throw empty_string();
        pieces.push_back(str_temp);

        cout << "Enter number of pieces: ";
        if (!(cin >> int_temp))			//Invalid type error
            throw failed_int();
        piece_count.push_back(int_temp);
    }	
    return 1;
}

//Destructor: sets all data values to 0 equivalent
board::~board()
{
    pieces.clear();
    piece_count.clear();
}
