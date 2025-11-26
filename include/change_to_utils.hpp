#ifndef UTILS
#define UTILS

#include <memory>
#include <vector>
#include <string>
#include <random>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>
#include <functional> // for std::hash
#include <sstream>

using json = nlohmann::json;

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

  // For hashing
  std::string toString() const {
    return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
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

enum class TypeBatiment {
  House,
  Apartment,
  Park,
  Cinema,
  Mall,
  Bank,
  PowerPlant,
  WaterTreatmentPlant,
  UtilityPlant,
  Custom
};

enum class SimState {
    Running,
    Evaluating,
    GameOver
};

enum class Difficulty { Easy, Medium, Hard };

using BatPtr = std::unique_ptr<Batiment>;
using BatimentList = std::vector<BatPtr>;

class BuildingIDGenerator {
private:
    static std::hash<std::string> string_hasher;
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_int_distribution<int> dist;

public:
    static int generateID(const std::string& name, TypeBatiment type, 
                         const Position& position, const Surface& surface) {
        // Create a unique string combining all properties
        std::string unique_string = 
            name + "_" +
            std::to_string(static_cast<int>(type)) + "_" +
            position.toString() + "_" +
            std::to_string(static_cast<int>(surface.largeur)) + "x" +
            std::to_string(static_cast<int>(surface.longeur)) + "_" +
            std::to_string(dist(gen)); // spicy randomness
        
        // h4sh ;)
        size_t hash = string_hasher(unique_string);
        int id = static_cast<int>(hash & 0x7FFFFFFF); // Ensure positive
        
        return id;
    }
};

std::hash<std::string> BuildingIDGenerator::string_hasher;
std::random_device BuildingIDGenerator::rd;
std::mt19937 BuildingIDGenerator::gen(BuildingIDGenerator::rd());
std::uniform_int_distribution<int> BuildingIDGenerator::dist(1000, 9999);

class NameGenerator {
private:
    static std::map<TypeBatiment, std::vector<std::string>> buildingNames;
    static std::random_device rd;
    static std::mt19937 gen;
    static bool initialized;

    static void initializeNames() {
        if (initialized) return;
        
        std::ifstream file("building_names.json");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open building_names.json file");
        }

        json j;
        file >> j;

       
        buildingNames[TypeBatiment::House] = j["House"].get<std::vector<std::string>>();
        buildingNames[TypeBatiment::Apartment] = j["Apartment"].get<std::vector<std::string>>();
        buildingNames[TypeBatiment::Park] = j["Park"].get<std::vector<std::string>>();
        buildingNames[TypeBatiment::Cinema] = j["Cinema"].get<std::vector<std::string>>();
        buildingNames[TypeBatiment::Mall] = j["Mall"].get<std::vector<std::string>>();
        buildingNames[TypeBatiment::Bank] = j["Bank"].get<std::vector<std::string>>();
        buildingNames[TypeBatiment::PowerPlant] = j["PowerPlant"].get<std::vector<std::string>>();
        buildingNames[TypeBatiment::WaterTreatmentPlant] = j["WaterTreatmentPlant"].get<std::vector<std::string>>();
        buildingNames[TypeBatiment::UtilityPlant] = j["UtilityPlant"].get<std::vector<std::string>>();
        
        initialized = true;
    }

public:
    static std::string getRandomName(TypeBatiment type) {
        initializeNames();
        
        auto it = buildingNames.find(type);
        if (it == buildingNames.end() || it->second.empty()) {
            return "Unnamed Building";
        }

        std::uniform_int_distribution<> dis(0, it->second.size() - 1);
        return it->second[dis(gen)];
    }
};

std::map<TypeBatiment, std::vector<std::string>> NameGenerator::buildingNames;
std::random_device NameGenerator::rd;
std::mt19937 NameGenerator::gen(NameGenerator::rd());
bool NameGenerator::initialized = false;

#endif // !UTILS