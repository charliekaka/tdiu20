#include "ghost.h"
#include "given.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

/*
  Ledning och Tips:

  - Modifiera stukturen till en header-fil och en implementationsfil
  - Ut�ka 'run()' och 'draw_map()' med �vrig funktionalitet.
  - L�gg alla sp�ken i en l�mplig beh�llare som en datamedlem.
  - Bryt ut stora kodblock till egna funktioner.
  - Anv�nd hj�lpfunktioner f�r att undvika duplicering av kod.
  - T�nk p� att varje funktion inte borde vara l�ngre �n 25 rader.
 */

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

	    // L�GG TILL RED, SCATTER MM

            for (Ghost* e : ghost_list) {
                if (command == e->get_color())
                {
                    Point new_pos {};
                    iss >> new_pos.x >> new_pos.y;
                    e->set_position(new_pos);
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
                
            }
            else if (command == "quit")
            {
                break;
            }
        }
    }
    
private:

    /*
      En hj�lpfunktion som avg�r vilka tv� tecken som ska ritas ut f�r en given position p�
      spelplanen.
     */

    // L�GG TILL FLER TECKEN?
    string to_draw(Point const& curr_pos)
    {
        string to_draw{"  "};

        if (pacman.get_position() == curr_pos)
        {
            to_draw[1] = '@';
        }

        return to_draw;
    }
    
    /*
      En hj�lpfunktion f�r att rita ut spelplanen f�r testprogrammet.
      
      Itererar �ver varje rad och column i kartan. Index f�r raderna �r flippade f�r att placera
      y = 0 l�ngst ned.
      
      Varje punkt i kartan ritas som tv� tecken eftersom ett tecken i terminalen �r ca dubbelt s�
      h�gt som det �r brett.
    */
    void draw_map()
    {
        cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+\n";

        for (int y {HEIGHT - 1}; y >= 0; --y) 
        {
            cout << "|";
            for (int x {}; x < WIDTH; ++x) 
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
