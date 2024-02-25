#include "ghost.h"
#include "given.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

class Ghost_Tester
{

public:

    Ghost_Tester()
        : pacman {}, ghost_list {}
    {
        ghost_list.push_back(new Blinky{pacman});
        ghost_list.push_back(new Pinky{pacman});
        ghost_list.push_back(new Clyde{pacman});
    }

    void run()
    {
        while(true)
        {
            draw_map();
            cout << "> ";

            string line {};
            getline(cin, line);
            istringstream iss {line};
        
            string command {};
            iss >> command;

            for (Ghost* e : ghost_list) 
            {
                if (command == e -> get_color())
                {
                    Point new_pos {};
                    iss >> new_pos.x >> new_pos.y;
                    e -> set_position(new_pos);
                }
            }
            if (command == "pos")
            {
                Point new_pos {};
                iss >> new_pos.x >> new_pos.y;
                pacman.set_position(new_pos);
            }
            else if (command == "dir")
            {
                Point new_dir {};
                iss >> new_dir.x >> new_dir.y;
                pacman.set_direction(new_dir);
            }
            else if (command == "scatter")
            {
                for (Ghost* e : ghost_list) 
                {
                    e -> set_position(e -> get_scatter_point());
                }
            }
            else if (command == "quit")
            {
                for (Ghost* e : ghost_list) 
                {
                    delete e;
                }                
                break;
            }

        }
    }
    
private:

    string to_draw(Point const& curr_pos)
    {
        string to_draw{"  "};

        if (pacman.get_position() == curr_pos)
        {
            to_draw[1] = '@';
        }
        for (Ghost* e : ghost_list) 
        {
            char c {e -> get_color().at(0)};

            if(e -> get_chase_point() == curr_pos)
            {
                to_draw[1] = c;
            }
            if(e -> get_position() == curr_pos)
            {
                to_draw[1] = toupper(c);
            }
        }

        return to_draw;
    }

    void draw_map()
    {
        cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+\n";

        for (int y {HEIGHT - 1}; y >= 0; --y) 
        {
            cout << "|";
            for (int x {}; x < WIDTH; x++) 
            {
                cout << to_draw( Point{x,y} );
            }
            cout << "|\n";
        }
    
        cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+" << endl;
    }

    Pacman pacman;
    vector<Ghost*> ghost_list;
};

int main()
{
    Ghost_Tester gt {};
    gt.run();
    return 0;
}
