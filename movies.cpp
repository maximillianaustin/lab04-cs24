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
std::string Movie::getName() const {
    return name;
}
double Movie::getRating() const {
    return rating;
}