#include "game.h"
#include "tree.h"

//Angeline Vu, 03/05/2024, CS302-001, Program 3
//This file has class method implementations
//for the node class and the tree class

//Node class functions
//Default constructor: sets members to zero equivalent
node::node() : data(nullptr), parent(nullptr), left(nullptr), right(nullptr), color(color_flag::red) {}

//Constructor with game_ptr argument.
//Transfers ownership to the node!
//node::node(game_ptr & source)
node::node(game_ptr & source)
{
    data = source;
}

//Getter: get color flag
color_flag node::get_color()
{
    return color;
}

//Getter: get game_ptr data
node::game_ptr & node::get_data()
{
    return data;
}

//Getter: get node's parent
node::node_ptr & node::get_parent()
{
    return parent;
}

//Getter: get node_ptr right
node::node_ptr & node::get_right()
{
    return right;
}

//Getter: get node_ptr left
node::node_ptr & node::get_left()
{
    return left;
}

int node::set_parent(node_ptr & new_parent)
{
    parent = new_parent;
    return 1;
}

//Set right: transfers ownership to the node
int node::set_right(node_ptr & new_right)
{
    right = new_right;
    return 1;
}

//Set left: transfers ownership to the node
int node::set_left(node_ptr & new_left)
{
    left = new_left;
    return 1;
}

//Set the node color based on argument
int node::set_color(color_flag flag)
{
    color = flag;
    return 1;
}

//Compares nodes: if the arg data is greater or equal
//to the node's, return true
bool node::less_than(const game_ptr & new_data)
{
    if (data->less_than(*new_data))
        return true;
    return false;
}

//Destructor: sets all member values to 0 equivalent
node::~node()
{
    color = color_flag::red;
    data.reset();
    left.reset();
    right.reset();
}

//Red-black tree class functions
//Default constructor: sets all member values to zero equivalent 
//Constructor
tree::tree() : root(nullptr) {}

//Display all entries in order
int tree::display() const
{
    if (!root)		//Empty 
        return 0;
    return display(root);
}

//Recursive function for display
int tree::display(node_ptr root) const
{
    if (!root)	
        return 1;
    display(root->get_left());
    root->get_data()->display();
    display(root->get_right());
    return 1;
}

//Insert entry to tree
int tree::insert(node::game_ptr & game)
{
    if (!root)		//Empty, add first item
    {
        root = make_shared<node>(game);
        root->set_color(color_flag::black);       //Black root
        return 1;
    }

    node_ptr parent = nullptr;     //Hold onto parent

    return insert(root, parent, game);     //Get location of newly inserted node
}

//Recursive function to insert in the tree
int tree::insert(node_ptr & root, node_ptr & parent, node::game_ptr & game)
{
    if (!root)
    {
        root = make_shared<node>(game); //New node
        root->set_parent(parent);       //Set parent
        return balance(root);           //Fix?
    }

    if (root->get_data()->match(*game))  //No duplicate games
        throw dupe_game();

    if (root->get_data()->less_than(*game))         //Data in node is less than new
    {
        insert(root->get_right(), root, game);    //Traverse to insert correctly
        if (root && root->get_right()->get_color() == color_flag::red)  //Unwind stack and check balance
            balance(root->get_right());                    
    }

    else
    {
        insert(root->get_left(), root, game);      //Data in node is more than new
        if (root && root->get_left()->get_color() == color_flag::red)   //Unwind stack and check balance
            balance(root->get_left());
    }

    return 1;
}

//Balance tree after insert
int tree::balance(node_ptr & root)
{
    if (root == this->root)     //Real root == no case
        return 1;

    if (root->get_parent()->get_color() == color_flag::black)   //Parent is black
        return 1;                                           //If not root, has a parent

    node_ptr mom = root->get_parent();           //Parent
    node_ptr grandma = mom->get_parent();        //Grandparent
    node_ptr auntie = nullptr;                   //Uncle

    if (mom == grandma->get_right())                //Mom is right child
    {
        auntie = grandma->get_left();               //Auntie is left child

        if (auntie && auntie->get_color() == color_flag::red)   //Case #1: Auntie is red
        {
            mom->set_color(color_flag::black);                  //Only color changes needed
            auntie->set_color(color_flag::black);               
            grandma->set_color(color_flag::red);               
        }

        else if (root == mom->get_left())           //Case #2: root == mom->left &&
        {                                           //mom == grandma->right
            root->set_color(color_flag::black);                 //Set colors
            mom->set_color(color_flag::red);
            grandma->set_color(color_flag::red);                
            right_rotate(mom);                      //Rotate right parent
            left_rotate(grandma);                   //Rotate left grandparent
        }

        else
        {
            mom->set_color(color_flag::black);                      //Case #3: root == mom->right &&
            grandma->set_color(color_flag::red);                    //mom == grandma->right
            left_rotate(grandma);
        }
    }

    else
    {
        auntie = grandma->get_right();                  //Auntie is the right child

        if (auntie && auntie->get_color() == color_flag::red)       //Case #1 mirror
        {
            mom->set_color(color_flag::black);
            auntie->set_color(color_flag::black);
            grandma->set_color(color_flag::red);
        }

        else if (root == mom->get_right())              //Case #3: root == mom->right &&
        {                                               //mom == grandma->left
            root->set_color(color_flag::black);               //Color change
            mom->set_color(color_flag::red);
            grandma->set_color(color_flag::red);
            left_rotate(mom);                           //Rotations
            right_rotate(grandma);
        }

        else                                            //Case #4 root == mom->left &&
        {                                               //mom == grandma->left
            mom->set_color(color_flag::black);                //Color change
            grandma->set_color(color_flag::red);
            right_rotate(grandma);                      //Rotation
        }
    }

    this->root->set_color(color_flag::black);                 //Real root = black
    return 1;
}

//Rotates tree right
int tree::right_rotate(node_ptr & root)
{
    node_ptr mom = root->get_parent();      //Current parent
    node_ptr hold = root->get_right();      //New child node

    root->set_right(hold->get_left());

    if (!hold->get_left())                  //No left child
        hold->get_left()->set_parent(hold);

    if (!mom)                               //Real root
        this->root = hold;

    else if (root == mom->get_left())       //Mom's left
        mom->set_left(hold);

    else                                    //Mom's right
        mom->set_right(hold);

    hold->set_parent(mom);                  //Set kid's mom
    hold->set_left(root);                   //Set left kid
    root->set_parent(hold);                 //Set mom

    return 1;
}

//Rotates tree left
int tree::left_rotate(node_ptr &)
{
    node_ptr mom = root->get_parent();      //Mom
    node_ptr hold = root->get_right();      //New child node

    root->set_right(hold->get_left());    

    if (!hold->get_left())                  //No child left
        hold->get_left()->set_parent(root);

    if (!mom)                               //Real root
        this->root = hold;

    else if (root == mom->get_left())       //Mom's left
        mom->set_left(hold);

    else                                    //Mom's right
        mom->set_right(hold);

    hold->set_parent(mom);                  //Set kid's mom
    hold->set_left(root);                   //Set left kid
    root->set_parent(hold);                 //Set mom 
    return 1;
}

//Search via string key: returns number of matches
int tree::search_string(const string & find) const
{
    if (!root)		//Empty
        return 0;
    return search_string(root, find);
}

//Recursive function to search for a string
int tree::search_string(node_ptr root, const string & find) const
{
    if (!root)		//Empty
        return 0;

    int count = search_string(root->get_left(), find);
    if (root->get_data()->search_string(find))
    {
        root->get_data()->display();
        ++count;
    }
    return search_string(root->get_right(), find) + count;
}

//Search via int key
int tree::search_int(const int find) const
{
    if (!root)		//Empty
        return 0;
    return search_int(root, find);
}

//Recursive function to search int
int tree::search_int(node_ptr root, const int find) const
{
    if (!root)		//Empty
        return 0;

    int count = search_int(root->get_left(), find);
    if (root->get_data()->search_int(find))
    {
        root->get_data()->display();
        ++count;
    }
    return search_int(root->get_right(), find) + count;
}

//Search parts via string key
int tree::search_parts(const string & find) const
{
    if (!root)		//Empty
        return 0;
    return search_parts(root, find);
}

//Recursive function to search components of game
int tree::search_parts(node_ptr root, const string & find) const
{
    if (!root)		//Empty
        return 0;

    int count = search_parts(root->get_left(), find);
    if (root->get_data()->search_parts(find))
    {
        root->get_data()->display();
        ++count;
    }
    return search_parts(root->get_right(), find) + count;
}

//Retrieve based on name match
int tree::retrieve(const string & find, node::game_ptr & found) const
{
    if (!root)
        return 0;

    if (find == "")
        throw empty_string();

    return retrieve(root, find, found);
}

//Recursive function to retrieve game_ptr match
int tree::retrieve(node_ptr root, const string & find, node::game_ptr & found) const
{
    if (!root)
        return 0;

    if (root->get_data()->match(find))
    {
        found = root->get_data();
        return 1;
    }

    if (root->get_data()->less_than(find))
        return retrieve(root->get_right(), find, found);
    return retrieve(root->get_left(), find, found);
}

//Remove all: delete all entries
int tree::remove_all()
{
/*
    if (!root)		//Empty
        return 1;
    root = nullptr;
*/
    remove_all(root);
    return 1;
}

//Recursive remove all function
int tree::remove_all(node_ptr & root)
{
    if (!root)
        return 1;
    remove_all(root->get_left()) + remove_all(root->get_right());
    root = nullptr;
    return 1;
}

//Destructor: deletes redblack tree
tree::~tree()
{
    remove_all();	
}
