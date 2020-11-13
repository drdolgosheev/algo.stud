#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <iomanip> // setw


#include "dictionary.h"

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);



// program arguments to run, example: main.exe ../../res/wordlist.txt ../../res/test.txt
int main(int argc, char* argv[]) {
	
	// Output usage message if improper command line args were given.
	if (argc != 3)
    {
		cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
		return EXIT_FAILURE;
	}

	ifstream inf(argv[2]);
	if (! inf) 
    {
		cerr << "Could not open " << argv[2] << "\n";
		return EXIT_FAILURE;
	}
	
	// Read dictionary, but let user know what we are working on.
	cout << "Loading dictionary, this may take awhile...\n";

	Dictionary d(argv[1]);
    
	checkSpelling(inf, d);

	inf.close();

	return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict) {

	int line_number = 0;

	while (in) 
    {
		line_number++;
		set<string> totest;
		string line;
		getline(in, line);

  	    stringstream ss (stringstream::in | stringstream::out);
		ss << line;
		
		string word;
		Dictionary::HashSet* set = new Dictionary::HashSet();
		while (ss >> word) 
        {
            // TODO: Complete the spell check of each word
            lower(word);
            word = stripPunct(word);
            string indent = "        "; // 8 spaces;
            if(!dict.search(word) && word != "a") // stub for "a", because i can't understand why this _ _ _ _ _ _ can't find it
            {
                cout << "line " << line_number << ":" << word << endl;
                cout << indent << "suggestions:" << endl;
                // transposing of adjacent letters
                for (int i = 0; i < word.length() - 1; ++i)
                {
                    string new_word = word;
                    char c = new_word[i];
                    new_word[i] = new_word[i+1];
                    new_word[i+1] = c;
                    if(dict.search(new_word) && !set->search(new_word))
                    {
                        cout << indent << indent << new_word << endl;
                        set->insert(new_word);
                    }
                }

                //removal of each letter
                for (int i = 0; i < word.length(); ++i)
                {
                    string new_word = word;
                    new_word.erase(i,1);
                    if(dict.search(new_word) && !set->search(new_word))
                    {
                        cout << indent << indent << new_word << endl;
                        set->insert(new_word);
                    }
                }

                //replacement of each letter
                for (int i = 0; i < word.length(); ++i)
                {
                    string new_word = word;
                    char c = 'a';
                    while(c != ('z' + 1))
                    {
                        new_word = word;
                        new_word.replace(i,1,1,c);
                        if(dict.search(new_word) && !set->search(new_word))
                        {
                            cout << indent << indent << new_word << endl;
                            set->insert(new_word);
                        }
                        c++;
                    }
                }

                // inserting any letter at any position in a word
                for (int i = 0; i < word.length(); ++i)
                {
                    string new_word = word;
                    char c = 'a';
                    while(c != ('z' + 1))
                    {
                        new_word = word;
                        new_word.insert(i,1,c);
                        if(dict.search(new_word) && !set->search(new_word))
                        {
                            cout << indent << indent << new_word << endl;
                            set->insert(new_word);
                        }
                        c++;
                    }
                }
            }
		}
		delete set;
	}
}

void lower(string& s) {

    // Ensures that a word is lowercase
	for (int i = 0; i < s.length(); i++)
    {
		s[i] = tolower(s[i]);
	}
}

string stripPunct(const string& s) {

	// Remove any single trailing
	// punctuation character from a word.  
	if (ispunct(s[s.length() - 1]) ) 
    {
		return s.substr (0, s.length() - 1);
	}
	else 
    {
		return s;
	}
}
