#include "game.h"
#include "tree.h"

//Angeline Vu, 03/05/2024, CS302-001, Program 3
//This file implements the main program.

//Main function
int main()
{
    set_terminate(user_terminate);	//Set new terminating functions

    tree collection;		    //Collection of videogames
    string search;		     	//String to hold user input
    char selection = ' ';		//Menu user input holder
    node::game_ptr temp;		//Game pointer to add to collection
    node::game_ptr cast;        //Game pointer to attempt casting

    do
    {
        selection = menu();	  //Main menu
        try {
            switch (selection)
            {
                case '1': { selection = game_menu();	//Insert a game
                              switch (selection)	    	//Choose game type
                              {
                                  case '1': { video new_video;	//New videogame
                                                new_video.set();
                                                temp = make_unique<video>(new_video);
                                                collection.insert(temp);	
                                                temp = nullptr;
                                                break;
                                            }

                                  case '2': { card new_card;  	//New card game
                                                new_card.set();
                                                temp = make_unique<card>(new_card);
                                                collection.insert(temp);	
                                                temp = nullptr;
                                                break;
                                            }

                                  case '3': { board new_board;	//New board game
                                                new_board.set();
                                                temp = make_unique<board>(new_board);
                                                collection.insert(temp);	
                                                temp = nullptr;
                                                break;
                                            }
                              }

                              break;
                          }

                case '2': { cout << "\nDisplay\n";
                              if (!collection.display())	      //Display tree
                                  cout << "\nEmpty Collection\n";
                              break;
                          }

                case '3': { cout << "\nSearch Word\n";
                              get_string(search);
                              if (!collection.search_string(search))	  //Find word
                                  cout << "\nNo match\n";
                              break;
                          }

                case '4': { cout << "\nSearch Number\n";
                              if (!collection.search_int(get_int()))	//Find number
                                  cout << "\nNo match\n";
                              break;
                          }

                case '5': { cout << "\nSearch Parts\n";
                              get_string(search);
                              if (!collection.search_parts(search))		//Find parts
                                  cout << "\nNo match\n";
                              break;
                          }

                case '6': { cout << "\nSearch Crossplay\n";    //For video game, is xplay?
                              get_string(search);
                              if (!collection.retrieve(search, cast))
                                  cout << "\nNo match\n";
                              else
                              {
                                  shared_ptr<video> type = dynamic_pointer_cast<video>(cast);
                                  if (type)
                                  {
                                      if (type->xplay())                            //Supports?
                                          cout << "\nCrossplay Supported\n";        //Yes
                                      else
                                          cout << "\nCrossplay Not Supported\n";    //No
                                  }
                                  else                                              //Not a game
                                      cout << "\nGame Not Applicable\n";
                              }
                              break;
                          }

                case '7': { cout << "\nProgram Ended\n";	      //Quit
                              break;
                          }

            }
        }

        catch (char)        //Exception when an integer read was failed
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "\nPlease Try Again.\n"; 
        }

        catch (...)         //All other exceptions
        {
            cout << "\nPlease Try Again.\n"; 
        }

    } while (selection != '7');     //Quit

    return 0;
}
