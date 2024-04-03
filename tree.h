#include <memory>
#include <array>
using namespace std;

//Angeline Vu, 03/05/2024, CS302-001, Program 3
//This file has class interfaces for the tree structure

//Color flag for red black tree
enum class color_flag {black, red};   	//Colors

//Node class, has a unique game pointer for data;
//has vector of children (3)
class node
{
    public:
        typedef shared_ptr<node> node_ptr;	//Nicknames!
        typedef shared_ptr<game> game_ptr;	

        node();					//Constructor
        node(game_ptr &);		//Constructor with argument	

        color_flag get_color();	    //Get color
        game_ptr & get_data();		//Get data
        node_ptr & get_parent();    //Get parent
        node_ptr & get_right();		//Get right ptr
        node_ptr & get_left();		//Get left ptr

        int set_parent(node_ptr & new_parent);  //Sets parent ptr
        int set_right(node_ptr &);	            //Set right ptr
        int set_left(node_ptr &);               //Set left ptr
        int set_color(color_flag color);        //Set node to black: default red

        bool less_than(const node::game_ptr & new_data);//Compare nodes
        ~node();				                        //Destructor

    private:
        color_flag color;		//The color of the node
        game_ptr data;			//Data in node (game ptr)
        node_ptr parent;        //Left pointer
        node_ptr left;          //Left pointer
        node_ptr right;         //Right pointer
};

//2-3 Tree
class tree
{
    public:
        typedef shared_ptr<node> node_ptr;	//Nickname

        tree();			          		//Constructor
        int display() const;			//Display all

        int insert(node::game_ptr &);	//Insert
        int balance(node_ptr &);        //Balance tree after insert
        int right_rotate(node_ptr &);   //Rotates tree
        int left_rotate(node_ptr &);

        int search_string(const string &) const;    //Search via string key
        int search_int(const int) const;	        //Search via int key
        int search_parts(const string &) const;	    //Search parts via string key

        int retrieve(const string &, node::game_ptr &) const; //Retrieve based on name

        int remove_all();	//Remove all
        ~tree();		    //Destructor

    private:
        node_ptr root;		//Tree root

        //Recursive functions
        int display(node_ptr root) const;
        int insert(node_ptr & root, node_ptr & parent, node::game_ptr &);			
        int search_string(node_ptr root, const string &) const;
        int search_int(node_ptr root, const int) const;
        int search_parts(node_ptr root, const string &) const;
        int retrieve(node_ptr root, const string &, node::game_ptr &) const;
        int remove_all(node_ptr & root);
};
