#include "movies.h"

bool Movie::operator>(const Movie &left) const {
    return name > left.name;
}
bool Movie::operator==(const Movie &left) const {
    return name == left.name && rating == left.rating;
}
