// Winter'25
// Instructor: Maximillian Austin
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    vector<Movie> allMovies;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
        while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
                Movie n(movieName, movieRating);
                allMovies.push_back(n);
                // Use std::string movieName and double movieRating
                // to construct your Movie objects
               // cout << movieName << " has rating " << movieRating << endl;
                // insert elements into your data structure
        }

    movieFile.close();

    if (argc == 2){
         // replace with your data structure
            sort(allMovies.begin(), allMovies.end());
        for (const Movie &m : allMovies) {
            cout << m.getName() << ", " << m.getRating() << endl;

        }
            //print all the movies in ascending alphabetical order of movie names
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    prefixFile.close();

    vector<vector<Movie>> moviesByPrefix(prefixes.size());
    vector<Movie> bestMovies(prefixes.size(), Movie("", -1.0));
   
    

    

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
     for (size_t i = 0; i < prefixes.size(); ++i) {
        const string &prefix = prefixes[i];
        for (const Movie &movie : allMovies) {
            if (movie.getName().rfind(prefix, 0) == 0) {
                cout << movie.getName() << ", " << movie.getRating() << endl;
                moviesByPrefix[i].push_back(movie);
                if (movie.getRating() > bestMovies[i].getRating()) {
                    bestMovies[i] = movie;
                }
            }
        } if (moviesByPrefix[i].empty()) {
            cout << "No movies found with prefix " << prefix << endl;
        } else {
            cout << "\n";
        }
    }


    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for (size_t i = 0; i < bestMovies.size(); ++i) {
        const Movie &m = bestMovies[i];
        if (m.getRating() >= 0) {
            cout << "Best movie with prefix " << prefixes[i] << " is: " << bestMovies[i].getName() << " with rating " << std::fixed << std::setprecision(1) << bestMovies[i].getRating() << endl;
        }
    }
    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}