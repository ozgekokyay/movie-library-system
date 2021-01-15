#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "LibrarySystem.h"
#include "MethodTester.h"
#include "vector"

using namespace std;
extern ofstream outputFile;
//Constructor

MethodTester::MethodTester(const string file) {
    ifstream commandFile;
    commandFile.open(file);
    string line;
    if (commandFile.is_open())
    {
        // First line of the output file
        outputFile<<"==Movie Library System===\n";

        // create library named my favourite flower
        LibrarySystem krizantemLibrary;

        // print out method test before methods
        string lastMethod = "none";

        //execute commands
        while (getline(commandFile,line))
        {
            // Vector of string to save tokens
            vector <string> tokens;

            // stringstream class check1
            stringstream check1(line);
            string intermediate;

            while(getline(check1, intermediate, '\t'))
            {
                tokens.push_back(intermediate);
            }
            if (tokens[0] == "addUser"){
                if ( lastMethod != "addUser" ){
                    lastMethod = "addUser";
                    outputFile<<"\n===addUser() method test===\n";
                }
                int id = stoi(tokens[1]) ;
                string name = tokens[2];
                krizantemLibrary.addUser(id, name);

            }
            else if (tokens[0] == "addMovie"){
                if ( lastMethod != "addMovie" ){
                    lastMethod = "addMovie";
                    outputFile<<"\n===addMovie() method test===\n";
                }
                int id = stoi(tokens[1]) ;
                string name = tokens[2];
                int year = stoi(tokens[3]);
                krizantemLibrary.addMovie(id, name, year);

            }
            else if (tokens[0] == "showAllMovie"){
                if ( lastMethod != "showAllMovie" ){
                    lastMethod = "showAllMovie";
                    outputFile<<"\n===showAllMovie() method test===\n";
                }
                krizantemLibrary.showAllMovies();

            }
            else if (tokens[0] == "checkoutMovie"){
                if ( lastMethod != "checkoutMovie" ){
                    lastMethod = "checkoutMovie";
                    outputFile<<"\n===checkoutMovie() method test===\n";
                }
                int movieId = stoi(tokens[1]) ;
                int userId = stoi(tokens[2]) ;
                krizantemLibrary.checkoutMovie(movieId,userId);
            }
            else if (tokens[0] == "showUser"){
                if ( lastMethod != "showUser" ){
                    lastMethod = "showUser";
                    outputFile<<"\n===showUser() method test===\n";
                }
                int userId = stoi(tokens[1]) ;
                krizantemLibrary.showUser(userId);
            }
            else if (tokens[0] == "showMovie"){
                if ( lastMethod != "showMovie" ){
                    lastMethod = "showMovie";
                    outputFile<<"\n===showMovie() method test===\n";
                }
                int movieId = stoi(tokens[1]) ;
                krizantemLibrary.showMovie(movieId);

            }
            else if (tokens[0] == "returnMovie"){
                if ( lastMethod != "returnMovie" ){
                    lastMethod = "returnMovie";
                    outputFile<<"\n===returnMovie() method test===\n";
                }
                int movieId = stoi(tokens[1]) ;
                krizantemLibrary.returnMovie(movieId);
            }
            else if (tokens[0] == "deleteMovie"){
                if ( lastMethod != "deleteMovie" ){
                    lastMethod = "deleteMovie";
                    outputFile<<"\n===deleteMovie() method test===\n";
                }
                int movieId = stoi(tokens[1]) ;
                krizantemLibrary.deleteMovie(movieId);
            }
            else if (tokens[0] == "deleteUser"){
                if ( lastMethod != "deleteUser" ){
                    lastMethod = "deleteUser";
                    outputFile<<"\n===deleteUser() method test===\n";
                }
                int id = stoi(tokens[1]) ;
                krizantemLibrary.deleteUser(id);
            }
        }
    }

    commandFile.close();
}


