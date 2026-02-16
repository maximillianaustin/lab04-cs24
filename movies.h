#include <string>
class Movie {
    public:
    bool operator>(const Movie &left) const;
    bool operator<(const Movie &other) const;
    bool operator==(const Movie &left) const;   
    int getOriginalIndex() const;
    std::string getName() const;
    double getRating() const;
    Movie(std::string name, double rating, int oi);
    private:
        std::string name;
        double rating;
        int originalIndex;
};
