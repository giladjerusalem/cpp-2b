#include "Direction.hpp"
#include <string>
#include <map>
#include <vector>

const int wide =100;

using namespace std;
namespace ariel
    {
    class Notebook
    {
        private:
    map < int,vector < vector <char> > > book;
    public:
        Notebook();
        void write(int, int, int, Direction, string);
        string read(int, int, int, Direction, int);
        void erase(int, int, int, Direction, int);
        void show (int);
    };
}