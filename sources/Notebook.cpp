#include "Direction.hpp"
#include "Notebook.hpp"
#include <string>
#include <iostream>
#include <map>
#include <vector>

const int WIDE = 100;
const int MINIMUM = 32;
const int MAXIMUM = 126;


using namespace std;
namespace ariel{
    Notebook::Notebook(){}  //cunstructor
void Notebook:: write( int page, int row, int col, Direction dir, string insert){
    
    if (page<0||row<0||col<0)   //if insert negative number
    {
        throw ("not valid number: must be positive");
    }
    if (col>=WIDE){
        throw ("out of boundries");
    }

    for (size_t i = 0; i < insert.length(); i++)    //check if asscii is ok
    {
        if (insert[i]<MINIMUM || insert[i]>MAXIMUM || insert[i] == '~')
        {
            throw ("out of boundries");
        } 
    }
    
    if (dir == Direction::Horizontal && (size_t)col + insert.length() >= WIDE)
    {
        throw ("you trying to write out of boundries");       //if the size of the string is over the end of line
    }

    if (!book.contains(page))   //if the page not exist - create a new page from with row+1 rows (cause we start from 0) 
    {
        vector<vector<char>>page_created((size_t)row+1 , vector<char>(WIDE,'_'));  
        book[page]=page_created;
    }
    else
    {
        while (book[page].size()<=row)
        {
            book[page].push_back(vector<char>(WIDE,'_'));   //add lines
        }        
    }

    if (dir == Direction::Vertical)    //if the row doesnt exsit - create the row
    {
        for (size_t i = 0; i < insert.size(); i++)
        {
            if(i+(size_t)row>=book[page].size())
            {   //if missing lines
                while (book[page].size()<=(size_t)row+insert.size())
                {
                    book[page].push_back(vector<char>(WIDE,'_'));   //add lines
                }
                break;
            }
            if (book[page][(size_t)row+i][(size_t)col]!='_')
            {
                throw ("override chars");
            }            
        }
        for (size_t i = 0; i < insert.size(); i++)  //copy the char from insert
        {
            book[page][(size_t)row+i][(size_t)col]=insert[i];
        }
    }
    else if (dir == Direction::Horizontal)    //if the row doesnt exsit - create the row
    {
        for (size_t i = 0; i < insert.size(); i++)
        {
            if (book[page][(size_t)row][(size_t)col+i]!='_')    //someone write/delete there
            {
                throw ("override chars");
            }
        }
        for (size_t i = 0; i < insert.size(); i++)  //copy the char from "insert"
        {
            book[page][(size_t)row][(size_t)col+i]=insert[i];
        }

    }
}


//////////////////////////////////////////////////////

string Notebook::read( int page, int row, int col, Direction dir, int num){
    if (col>=WIDE||page<0||row<0||col<0||num<0)   //if insert negative number
    {
        throw ("not valid number: must be positive");
    }

    if (dir==Direction::Horizontal && col+num > WIDE)  //if the location + the string length is out of line
    {
        throw ("the string you trying to read is too long for this line");
    }
    if(num ==0)
    {
        return "";
    }

    if (!book.contains(page))   //if the page not exist - create a new page from with row+1 rows (cause we start from 0) 
    {
        vector<vector<char>>page_created((size_t)row+1 , vector<char>(WIDE,'_'));  
        book[page]=page_created;
    }
    else
    {
        while (book[page].size()<=row)
        {
            book[page].push_back(vector<char>(WIDE,'_'));   //add lines
        }        
    }


    string str(1, book[page][(size_t)row][(size_t)col]);
        
    if (dir==Direction::Horizontal)
    {   
        bool first_time = true;
        for (size_t i = 0; i < num; i++)    //horizonial- add to str char by char
        {
            if(!first_time)
            {
                str+=book[page][(size_t)row][(size_t)col+i];
            }
            else
            {
                first_time=false;
            }
        }
    }
    else if (dir==Direction::Vertical)
    {
        while (book[page].size()<=row + num)
        {
            book[page].push_back(vector<char>(WIDE,'_'));   //add lines
        }  
        bool first_time = true;
        for (size_t i = 0; i < num; i++)    //vertical- add to str char by char
        {
            if(!first_time)
            {
                str+=book[page][(size_t)row+i][(size_t)col];
            }
            else
            {
                first_time=false;
            }
            
        } 
    }
    
    return str;
}

////////////////////////////////////////////////////////

void Notebook::erase( int page, int row, int col, Direction dir, int num){
    if (page<0||row<0||col<0||num<0)   //if insert negative number
    {
        throw ("not valid number: must be positive");
    }

    if (col>=WIDE){
        throw ("out of boundries");
    }

    if (dir == Direction::Horizontal && col + num > WIDE)
    {
        throw ("you trying to write out of boundries");       //if the size of the string is over the end of line
    }
    if(num ==0)
    {
        return;
    }
    if (!book.contains(page))   //if the page not exist - open a new page from with row+1 rows (cause we start from 0) 
    {
        cout << "creating a new page";
        vector<vector<char>>page_created((size_t)row+1 , vector<char>(WIDE,'_'));  
        book[page]=page_created;
        cout << "new page created";
    }
    else
    {
        while (book[page].size()<=row)
        {
            book[page].push_back(vector<char>(WIDE,'_'));   //add lines
        }        
    }

    if (dir == Direction::Vertical)    //if the row doesnt exsit - create the row
    {
        while (book[page].size() <= row + num)
        {
            book[page].push_back(vector<char>(WIDE,'_'));   //add lines
        }
        for (size_t i = 0; i < num; i++)  //copy the char from insert
        {
            book[page][(size_t)row+i][(size_t)col]='~';     //erase
        }
    }
    else if (dir == Direction::Horizontal)    //if the row doesnt exsit - create the row
    {
        for (size_t i = 0; i < num; i++)  //copy the char from insert
        {
            book[page][(size_t)row][(size_t)col+i]='~';     //erase
        }
    }
}

//////////////////////////////////////////////////////////////////////

void Notebook:: show (int page){
    if (page<0)   //if insert negative number
    {
        throw ("not valid number: must be positive");
    }

    //if the page doesnt exist return "";
    if (!book.contains(page))   //if the page not exist - open a new page from with row+1 rows (cause we start from 0) 
    {
        return;
    }

    string s = "page number:" + to_string(page);

    for (size_t i = 0; i < book[page].size(); i++)
    {
        for (size_t j = 0; j < WIDE; j++)
        {
             s+=book[page][(size_t )i][(size_t )j];
        }
        cout<<s;        //print on screen the 'i' line
        cout<<"\n";     //
    }
    
} 

}
        