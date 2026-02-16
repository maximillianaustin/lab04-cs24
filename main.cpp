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
    /*
    Parameters affecting complexity:
    n = number of movies in the file;
    m = number of prefixes in the file;
    
    Space complexity: O(n) for storing all the movies in a vector and O(m) for storing the prefixes in a vector, resulting in an overall space complexity of O(n + m).

    Time complexity: O(n)
    */
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
    vector<Movie> allMovies; //O(n) size and space complexity where n is the number of movies in the file.

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    int count = 0;
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            Movie n(movieName, movieRating, count);
            count ++;
            allMovies.push_back(n);
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
    }

    movieFile.close();
    sort(allMovies.begin(), allMovies.end());
    if (argc == 2){
         // replace with your data structure
              // O(n log n) time complexity for sorting the movies based on their names.
        for (const Movie &m : allMovies) {  // O(n) time complexity to print all the movies in ascending alphabetical order of movie names.
            cout << m.getName() << ", " << m.getRating() << endl;

        }
            //print all the movies in ascending alphabetical order of movie names
            return 0; 
            //Overall O(n log n) time complexity.
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
    prefixFile.close(); // O(m) time complexity to read all the prefixes from the file and store them in a vector.

    vector<Movie> bestMovies(prefixes.size(), Movie("", -1.0, -1));
   vector<vector<Movie>> moviesWithPrefix(prefixes.size()); // O(m) space complexity to store the movies with each prefix in a vector of vectors.
    

    

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
     for (size_t i = 0; i < prefixes.size(); ++i) { // O(m * n) time complexity to find all movies that have the given prefix for each prefix in the vector.
        const string &prefix = prefixes[i];
        Movie target(prefix, 0.0, -1);
        auto it = lower_bound(allMovies.begin(), allMovies.end(), target); // O(log n) time complexity to find the lower bound of the prefix in the sorted vector of movies.
        while (it != allMovies.end()){
            const Movie &m = *it;
            if (m.getName().rfind(prefix,0) == 0) {
                moviesWithPrefix[i].push_back(m); // O(1) time complexity to add a movie to the vector of movies with the given prefix.
                if (m.getRating() > bestMovies[i].getRating()) {
                    bestMovies[i] = m;
                }
            } else {
                break;
            }
            ++it;
        }
        if (bestMovies[i].getRating() < 0) {
            cout << "No movies found with prefix " << prefix << endl;
        } else {
            sort(moviesWithPrefix[i].begin(), moviesWithPrefix[i].end(), 
             [](const Movie& a, const Movie& b) {
                 return a.getOriginalIndex() < b.getOriginalIndex();
             });
            for (const auto& m : moviesWithPrefix[i]) {
                cout << m.getName() << ", " << std::fixed << std::setprecision(1) << m.getRating() << endl;
            }
            cout << "\n";
        }
    }


    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for (size_t i = 0; i < bestMovies.size(); ++i) { //O(m) time complexity to print the highest rated movie for each prefix in the vector.
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