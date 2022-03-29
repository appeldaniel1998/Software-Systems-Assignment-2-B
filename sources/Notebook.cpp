#include "Notebook.hpp"

using namespace std;
using namespace ariel;

namespace ariel
{
    const int maxRowLength = 100;
    Notebook::Notebook()
    {
        map</*page number= */ int , map</*row number on page*/ int , map</*col number on row*/ int, /*char value*/char>>> pages;
    }
    Notebook::~Notebook()
    {

    }
    void Notebook::write(int page, int row, int col, Direction dir, string inString)
    {
        if(!inputVerification(inString))
        {
            throw invalid_argument("String received contained illeagal characters");
        }
        if(!verifyNumericInput(page, row, col))
        {
            throw invalid_argument("String received contained illeagal  values");
        }

        if (dir == Direction::Horizontal)
        {
            if (col + int(inString.length()) >= maxRowLength)
            {
                throw invalid_argument("Horizontal string received will overflow the maximum line length");
            }
            if (!verifyNotebookAvailabilityHorizontalWrite(page, row, col, inString))
            {
                throw invalid_argument("Horizontal string: The space was occupied by another character/s");
            }
            for(uint i = 0; i < inString.length(); i++)
            {
                this->pages[size_t(page)][size_t(row)][size_t(col)+i] = inString[i];
            }
        }
        else //dir == Direction::Vertical
        {
            if (col >= maxRowLength)
            {
                throw invalid_argument("Vertical string received will overflow the maximum line length");
            }
            if (col >= maxRowLength || !verifyNotebookAvailabilityVerticalWrite(page, row, col, inString))
            {
                throw invalid_argument("Vertical string: the space was occupied");
            }

            for(uint i = 0; i < inString.length(); i++)
            {
                map</*col number on row*/ int, /*char value*/char> tempRow;
                this->pages[size_t(page)][size_t(row) + i] = tempRow;
                this->pages[size_t(page)][size_t(row) + i][size_t(col)] = inString[i];
            }
        }
    }
    string Notebook::read(int page, int row, int col, Direction dir, int length)
    {
        string str;
        if (!verifyNumericInput(page, row, col, length))
        {
            throw invalid_argument("Negative numbers received (or length <= 0)");
        }
        if(dir == Direction::Horizontal)
        {
            if (size_t(col) + size_t(length) > maxRowLength)
            {
                throw invalid_argument("Overflowing row length!");
            }

            for (size_t i = 0; i < length; i++)
            {
                try
                {
                    char ch = this->pages.at(size_t(page)).at(size_t(row)).at(size_t(col)+i);
                    str += ch;
                }
                catch(const exception& e)
                {
                    str += "_";
                }
            }
            return str;
        }
        // else dir == Direction::Vertical
        
        if (size_t(col) >= maxRowLength)
        {
            throw invalid_argument("Overflowing row length!");
        }

        for (size_t i = 0; i < length; i++)
        {
            try
            {
                str += this->pages.at(size_t(page)).at(size_t(row)+i).at(size_t(col));
            }
            catch(const exception& e)
            {
                str += "_";
            }
        }
        return str;
        

        
        
    }
    void Notebook::erase(int page, int row, int col, Direction dir, int length)
    {
        if (!verifyNumericInput(page, row, col, length))
        {
            throw invalid_argument("Negative numbers received (or length <= 0)");
        }
        if(dir == Direction::Horizontal)
        {
            if (size_t(col) + size_t(length) > maxRowLength)
            {
                throw invalid_argument("Overflowing row length!");
            }

            if (this->pages.find(page) == this->pages.end()) // Page not found
            {
                map</*row number on page*/ int , map</*col number on row*/ int, /*char value*/char>> tempPage;
                this->pages[size_t(page)] = tempPage;
            }
            if (this->pages[size_t(page)].find(row) == this->pages[size_t(page)].end()) // Row not found
            { 
                map</*col number on row*/ int, /*char value*/char> tempRow;
                this->pages[size_t(page)][size_t(row)] = tempRow;
            }
            for (uint i = 0; i < length; i++)
            {
                this->pages[size_t(page)][size_t(row)][size_t(col) + i] = '~';
            }
        }



        else //dir == Direction::Vertical
        {
            if (size_t(col) >= maxRowLength)
            {
                throw invalid_argument("Overflowing row length!");
            }

            if (this->pages.find(page) == this->pages.end()) // Page not found
            {
                map</*row number on page*/ int , map</*col number on row*/ int, /*char value*/char>> tempPage;
                this->pages[page] = tempPage;
            }
            for (int i = 0; i < length; i++)
            {
                if (this->pages[page].find(row + i) == this->pages[page].end()) // Row not found
                { 
                    map</*col number on row*/ int, /*char value*/char> tempRow;
                    this->pages[page][row + i] = tempRow;
                }
                this->pages[page][row + i][col] = '~';
            }

        }
    }
    void Notebook::show(int pageNum)
    {
        if (pageNum < 0)
        {
            throw invalid_argument("Negative number received");
        }
        
        cout << "Printing the existing rows on page " << pageNum << ": "<< endl;
        for (map<int, map<int, map<int, char>>>::iterator it = this->pages.begin(); it != this->pages.end(); it++)
        {
            for (map<int, map<int, char>>::iterator it2 = this->pages[it->first].begin(); it2 != this->pages[it->first].end(); it2++)
            {
                for(int i = 0; i < maxRowLength; i++)
                {
                    try
                    {
                        cout << this->pages.at(it->first).at(it2->first).at(i);
                    }
                    catch(const std::exception& e)
                    {
                        cout << "_";
                    }
                }
                cout << endl;
            }
        }

    }
    bool Notebook::verifyNotebookAvailabilityHorizontalWrite(int page, int row, int col, string inString)
    {
        for(uint i = size_t(col); i < size_t(col) + inString.length(); i++) 
        //Verifying that there are no characters on the line to be added to in the place where the string shall be added to
        {
            if (this->pages.find(page) == this->pages.end()) // Page not found
            {
                map</*row number on page*/ int , map</*col number on row*/ int, /*char value*/char>> tempPage;
                this->pages[page] = tempPage;
                break;
            }
            //page found
            
            if (this->pages[page].find(row) == this->pages[page].end()) // Row not found
            { 
                map</*col number on row*/ int, /*char value*/char> tempRow;
                this->pages[page][row] = tempRow;
                break;
            }
            //row found
            if (this->pages[page][row].find(size_t(i)) == this->pages[page][row].end()) // Column not found
            {
                continue;
            }
            if (this->pages[page][row][size_t(i)] == '_' || this->pages[page][row][size_t(i)] == inString[i]) //page, row, column found. Check that backspace is the character written there
            {
                continue;
            }
            //otherwise, return false
            return false;
            
        }
        return true;
    }
    bool Notebook::verifyNotebookAvailabilityVerticalWrite(int page, int row, int col, string inString)
    {
        for(uint i = size_t(row); i < size_t(row) + inString.length(); i++)
        {
            if (this->pages.find(page) == this->pages.end()) // Page not found
            {
                map</*row number on page*/ int , map</*col number on row*/ int, /*char value*/char>> tempPage;
                this->pages[page] = tempPage;
                break;
            }
            //page found
        
            if (this->pages[page].find(size_t(i)) == this->pages[page].end()) // Row not found
            {
                continue;
            }
            //row found
            
            if (this->pages[page][size_t(i)].find(size_t(col)) == this->pages[page][row].end()) // Column not found
            {
                continue;
            }
            try
            {
                if (this->pages.at(page).at(size_t(i)).at(size_t(col)) == '_' || this->pages.at(page).at(size_t(i)).at(size_t(col)) == inString[i]) //page, row, column found. Check that backspace is the character written there
                {
                    continue;
                }
                return false;
            }
            catch(const std::exception& e)
            {
                continue;
            }
        
        }
        return true;
    }
    static bool inputVerification(string inString)
    {
        const int minPrintableChar = 32; //minimum printable character
        const int maxPrintableChar = 126; //maximum printable character
        for(uint i = 0; i < inString.length(); i++)
        {
            if(inString[i] == '~' || inString[i] < minPrintableChar || inString[i] > maxPrintableChar)
            {
                return false;
            }
        }
        return true;
    }
    static bool verifyNumericInput(int page, int row, int col, int length)
    {
        return !(page < 0 || row < 0 || col < 0 || length < 0);
    }
}
