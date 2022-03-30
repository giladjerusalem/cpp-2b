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
        void write(unsigned int, unsigned int, unsigned int, Direction, string);
        string read(unsigned int, unsigned int, unsigned int, Direction, unsigned int);
        void erase(unsigned int, unsigned int, unsigned int, Direction, unsigned int);
        void show (unsigned int);
    };
}