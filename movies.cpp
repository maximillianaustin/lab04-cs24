#include "movies.h"

bool Movie::operator>(const Movie &left) const {
    return name > left.name;
}
bool Movie::operator<(const Movie &other) const {
    return name < other.name; // Compare names alphabetically
}
bool Movie::operator==(const Movie &left) const {
    return name == left.name && rating == left.rating;
}
Movie::Movie(std::string name, double rating, int originalIndex) : name(name), rating(rating), originalIndex(originalIndex) {}
std::string Movie::getName() const {
    return name;
}
double Movie::getRating() const {
    return rating;
}
int Movie::getOriginalIndex() const {
    return originalIndex;
}