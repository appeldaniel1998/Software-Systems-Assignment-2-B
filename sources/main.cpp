#include "Notebook.hpp"

using namespace std;
using namespace ariel;

int mainProg()
{
    while (true)
    {
        Notebook note;
        int inp = 0;
        cout << "would you like to read (press 1), write (press 2), erase (press 3), show page (press 4) or exit the program (press 0)?" << endl;
        cin >> inp;
        if (inp == 0)
        {
            break;
        }
        if (inp == 1)
        {
            cout << "enter page, row, column, direction (1 for vertical and 2 for horizontal), and length, separated by enters (new lines):" << endl;
            int page = 0;
            int row = 0;
            int col = 0;
            int length = 0;
            int inDir = 0;
            Direction dir;
            cin >> page;
            cin >>  row;
            cin >>  col;
            cin >>  inDir;
            cin >>  length;
            if (inDir == 1)
            {
                dir = Direction::Vertical;
            }
            else if (inDir == 2)
            {
                dir = Direction::Horizontal;
            }
            else
            {
                continue;
            }
            cout << note.read(page, row, col, dir, length) << endl;
        }
        if (inp == 2)
        {
            cout << "enter page, row, column, direction (1 for vertical and 2 for horizontal), and string to write, separated by enters (new lines):" << endl;
            int page = 0;
            int row = 0;
            int col = 0;
            int length = 0;
            int inDir = 0;
            string inString;
            Direction dir;
            cin >> page;
            cin >>  row;
            cin >>  col;
            cin >>  inDir;
            cin >> inString;
            if (inDir == 1)
            {
                dir = Direction::Vertical;
            }
            else if (inDir == 2)
            {
                dir = Direction::Horizontal;
            }
            else
            {
                continue;
            }
            note.write(page, row, col, dir, inString);
            cout << "successful" << endl;
        }

        if (inp == 3)
        {
            cout << "enter page, row, column, direction (1 for vertical and 2 for horizontal), and length, separated by enters (new lines):" << endl;
            int page = 0;
            int row = 0;
            int col = 0;
            int length = 0;
            int inDir = 0;
            Direction dir;
            cin >> page;
            cin >>  row;
            cin >>  col;
            cin >>  inDir;
            cin >>  length;
            if (inDir == 1)
            {
                dir = Direction::Vertical;
            }
            else if (inDir == 2)
            {
                dir = Direction::Horizontal;
            }
            else
            {
                continue;
            }
            note.erase(page, row, col, dir, length);
            cout << "successful" << endl;
        }

        if (inp == 4)
        {
            cout << "enter page:" << endl;
            int page = 0;
            cin >> page;
            note.show(page);
        }
    }
    return 0;
}