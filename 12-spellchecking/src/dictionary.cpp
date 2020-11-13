#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"


Dictionary::Dictionary(string filename)
{
    std::string line;

    ifstream in(filename);

    if(in.is_open())
    {
        while(getline(in, line))
        {
            if(line[line.length()-1] == '\r')
                line.erase(line.length()-1);
            insert(line);
        }
    }

    in.close();
}
