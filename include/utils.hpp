#ifndef UTILS
#define UTILS

#include <memory>
#include <string>
#include <vector>

class Batiment;

struct Surface {
  float longeur;
  float largeur;
  Surface(int longeur = 0, int largeur = 0)
      : longeur(longeur), largeur(largeur) {}
};

struct Position {
  int x;
  int y;
  Position(int x = 0, int y = 0) : x(x), y(y) {}

  // Addition operators
  Position operator+(const Position &other) const {
    return {x + other.x, y + other.y};
  }

  // Subtraction operator
  Position operator-(const Position &other) const {
    return {x - other.x, y - other.y};
  }

  // compound assignment operators
  Position &operator+=(const Position &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Position &operator-=(const Position &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
};

struct Resources {
  double eau;
  double electricite;
  Resources(double e = 0.0, double el = 0.0) : eau(e), electricite(el) {}

  // Addition operators
  Resources operator+(const Resources &other) const {
    return {eau + other.eau, electricite + other.electricite};
  }

  // Subtraction operator
  Resources operator-(const Resources &other) const {
    return {eau - other.eau, electricite - other.electricite};
  }

  // compound assignment operators
  Resources &operator+=(const Resources &other) {
    eau += other.eau;
    electricite += other.electricite;
    return *this;
  }

  Resources &operator-=(const Resources &other) {
    eau -= other.eau;
    electricite -= other.electricite;
    return *this;
  }
};

struct WindowSettings {
  std::string title;
  const int width{1280};
  const int height{720};
};

enum class TypeBatiment {
  Blank, //0
  House, //1
  Apartment, //2
  Cinema, //3
  Mall, //4
  Bank, //5
  PowerPlant, //6
  WaterTreatmentPlant, //7
  UtilityPlant, //8
  Park, //9
  Custom //10
};

enum class SimState { Running, Evaluating, GameOver };

enum class Difficulty { Easy, Medium, Hard };

using BatPtr = std::unique_ptr<Batiment>;
using BatimentList = std::vector<BatPtr>;

#endif // !UTILS
