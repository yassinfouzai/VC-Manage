#ifndef UTILS
#define UTILS

#include <vector>
#include <memory>
#include <string>       
#include <map>         
#include <random>      
class Batiment;

struct Surface {
    float longeur;
    float largeur;
    Surface(int longeur = 0, int largeur = 0) : longeur(longeur), largeur(largeur) {}
};

struct Position {
    int x;
    int y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}

    // Addition operators
    Position operator+(const Position& other) const {
        return { x + other.x, y + other.y };
    }

    // Subtraction operator
    Position operator-(const Position& other) const {
        return { x - other.x, y - other.y };
    }

    // compound assignment operators
    Position& operator+=(const Position& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Position& operator-=(const Position& other) {
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
    Resources operator+(const Resources& other) const {
        return { eau + other.eau, electricite + other.electricite };
    }

    // Subtraction operator
    Resources operator-(const Resources& other) const {
        return { eau - other.eau, electricite - other.electricite };
    }

    // compound assignment operators
    Resources& operator+=(const Resources& other) {
        eau += other.eau;
        electricite += other.electricite;
        return *this;
    }

    Resources& operator-=(const Resources& other) {
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
    PowerPlant,
    WaterTreatmentPlant,
    Custom
};

class NameGenerator {
private:
    std::mt19937 rng;
    std::map<TypeBatiment, std::vector<std::string>> prefixes;
    std::map<TypeBatiment, std::vector<std::string>> suffixes;
    std::map<TypeBatiment, std::vector<std::string>> fullNames;
    
    void initializeData() {
        // Houses
        prefixes[TypeBatiment::House] = {
            "Belle", "Grand", "Petite", "Jolie", "Ancienne", "Moderne", 
            "Bleue", "Verte", "Blanche", "Rouge", "Solaire", "Tranquille"
        };
        
        suffixes[TypeBatiment::House] = {
            "Villa", "Maison", "Demeure", "Résidence", "Cottage", "Manoir",
            "Domaine", "Pavillon", "Chaumière", "Propriété"
        };

        // Apartments
        prefixes[TypeBatiment::Apartment] = {
            "Résidence", "Complexe", "Immeuble", "Tour", "Bâtiment",
            "Les", "Le", "La", "Avenue", "Place", "Jardin"
        };
        
        suffixes[TypeBatiment::Apartment] = {
            "des Roses", "du Parc", "Moderne", "Central", "Lumière",
            "Harmonie", "Sérénité", "Horizon", "Ciel", "Mer", "Bois"
        };

        fullNames[TypeBatiment::Apartment] = {
            "Résidence du Parc", "Tour Lumineuse", "Immeuble Moderne",
            "Complexe Horizon", "Les Jardins Fleuris", "Avenue Royale",
            "Place Centrale", "Les Hauts de Ville", "Résidence Belle Vue",
            "Tour Céleste", "Les Appartements du Lac"
        };

        // Parks
        prefixes[TypeBatiment::Park] = {
            "Parc", "Jardin", "Square", "Esplanade", "Promenade"
        };
        
        suffixes[TypeBatiment::Park] = {
            "Public", "Municipal", "des Enfants", "Botanique", "Floreal",
            "du Centenaire", "de la Paix", "de l'Amitié", "Vert", "Naturel"
        };

        // Power Plants
        prefixes[TypeBatiment::PowerPlant] = {
            "Centrale", "Station", "Complexe", "Unité"
        };
        
        suffixes[TypeBatiment::PowerPlant] = {
            "Énergétique", "Électrique", "Solaire", "Éolienne", "Hydraulique",
            "Thermique", "Nucléaire", "de Production"
        };

        fullNames[TypeBatiment::PowerPlant] = {
            "Centrale Solaire Principale", "Station Énergétique Nord",
            "Complexe de Production Électrique", "Unité Éolienne Urbaine"
        };

        // Water Treatment Plants
        prefixes[TypeBatiment::WaterTreatmentPlant] = {
            "Usine", "Station", "Centre"
        };
        
        suffixes[TypeBatiment::WaterTreatmentPlant] = {
            "d'Épuration", "de Traitement", "Hydrique", "des Eaux"
        };

        // Cinemas
        prefixes[TypeBatiment::Cinema] = {
            "Cinéma", "Complexe", "Salle"
        };
        
        suffixes[TypeBatiment::Cinema] = {
            "Paradiso", "Central", "Modern", "Star", "City", "Lumière"
        };
    }
    
public:
    NameGenerator() : rng(std::random_device{}()) {
        initializeData();
    }
    
    explicit NameGenerator(unsigned int seed) : rng(seed) {
        initializeData();
    }
    
    std::string generateBuildingName(TypeBatiment type) {
        if (fullNames.find(type) != fullNames.end() && !fullNames[type].empty()) {
            std::uniform_int_distribution<int> dist(0, fullNames[type].size() - 1);
            return fullNames[type][dist(rng)];
        }
        
        if (prefixes.find(type) != prefixes.end() && suffixes.find(type) != suffixes.end()) {
            std::uniform_int_distribution<int> prefixDist(0, prefixes[type].size() - 1);
            std::uniform_int_distribution<int> suffixDist(0, suffixes[type].size() - 1);
            
            return prefixes[type][prefixDist(rng)] + " " + suffixes[type][suffixDist(rng)];
        }
        
        // Fallback
        return "Bâtiment " + std::to_string(std::uniform_int_distribution<int>(1000, 9999)(rng));
    }
    
    std::string generateBuildingName(TypeBatiment type, const std::string& district) {
        std::string baseName = generateBuildingName(type);
        
        std::uniform_real_distribution<double> probDist(0.0, 1.0);
        if (probDist(rng) < 0.3) { 
            return baseName + " - " + district;
        }
        
        return baseName;
    }
    
    static NameGenerator& getInstance() {
        static NameGenerator instance;
        return instance;
    }
};

using BatPtr = std::unique_ptr<Batiment>;
using BatimentList = std::vector<BatPtr>;

#endif // !UTILS