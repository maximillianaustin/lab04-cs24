#include <string>
class Movie {
    public:
    bool operator>(const Movie &left) const;
    bool operator==(const Movie &left) const;   
    std::string getName() const;
    double getRating() const;
    Movie(std::string name, double rating) : name(name), rating(rating) {}
    private:
        std::string name;
        double rating;
};
