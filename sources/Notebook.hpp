#include <iostream>
#include <string>
#include "Direction.hpp"
#include <map>

using namespace std;

namespace ariel
{
    static bool verifyNumericInput(int page, int row, int col, int length=0);
    static bool inputVerification(string inString);
    class Notebook
    {
        map</*page number= */ int , map</*row number on page*/ int , map</*col number on row*/ int, /*char value*/char>>> pages;
        public: //all functions are implemented in Notebook.cpp
            Notebook();
            ~Notebook();
            void write(int page, int row, int col, Direction dir, string inString);
            string read(int page, int row, int col, Direction dir, int length);
            void erase(int page, int row, int col, Direction dir, int length);
            void show(int pageNum);
        private:
            bool verifyNotebookAvailabilityHorizontalWrite(int page, int row, int col, string inString);
            bool verifyNotebookAvailabilityVerticalWrite(int page, int row, int col, string inString);
    };
};