#ifndef UTILS
#define UTILS

#include <memory>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>
#include <functional>
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

  Position operator+(const Position &other) const {
    return {x + other.x, y + other.y};
  }

  Position operator-(const Position &other) const {
    return {x - other.x, y - other.y};
  }

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

  std::string toString() const {
    return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
  }
};

struct Resources {
  double eau;
  double electricite;
  Resources(double e = 0.0, double el = 0.0) : eau(e), electricite(el) {}

  Resources operator+(const Resources &other) const {
    return {eau + other.eau, electricite + other.electricite};
  }

  Resources operator-(const Resources &other) const {
    return {eau - other.eau, electricite - other.electricite};
  }

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
  const int width{960};
  const int height{640};
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

// Générateur d'IDs
class BuildingIDGenerator {
private:
    static std::hash<std::string> string_hasher;
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_int_distribution<int> dist;

public:
    static int generateID(const std::string& name, TypeBatiment type, 
                         const Position& position, const Surface& surface) {
        std::string unique_string = 
            name + "_" +
            std::to_string(static_cast<int>(type)) + "_" +
            position.toString() + "_" +
            std::to_string(static_cast<int>(surface.largeur)) + "x" +
            std::to_string(static_cast<int>(surface.longeur)) + "_" +
            std::to_string(dist(gen));
        
        size_t hash = string_hasher(unique_string);
        return static_cast<int>(hash & 0x7FFFFFFF);
    }
};

// Initialisation des variables statiques du BuildingIDGenerator
std::hash<std::string> BuildingIDGenerator::string_hasher;
std::random_device BuildingIDGenerator::rd;
std::mt19937 BuildingIDGenerator::gen(BuildingIDGenerator::rd());
std::uniform_int_distribution<int> BuildingIDGenerator::dist(1000, 9999);

// Générateur de noms
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

//NameGenerator
std::map<TypeBatiment, std::vector<std::string>> NameGenerator::buildingNames;
std::random_device NameGenerator::rd;
std::mt19937 NameGenerator::gen(NameGenerator::rd());
bool NameGenerator::initialized = false;

#endif // !UTILS
