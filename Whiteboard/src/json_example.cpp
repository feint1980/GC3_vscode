#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Define your character struct
struct CharacterStats {
    int strength;
    int vitality;
    int dexterity;
    int agility;
    int intelligence;
    int wisdom;
    double mana_bonus;
    double mana_scaling;
};

// Convert struct to JSON
void to_json(json& j, const CharacterStats& c) {
    j = json{
        {"strength", c.strength},
        {"vitality", c.vitality},
        {"dexterity", c.dexterity},
        {"agility", c.agility},
        {"intelligence", c.intelligence},
        {"wisdom", c.wisdom},
        {"mana_bonus", c.mana_bonus},
        {"mana_scaling", c.mana_scaling}
    };
}

// Convert JSON to struct
void from_json(const json& j, CharacterStats& c) {
    j.at("strength").get_to(c.strength);
    j.at("vitality").get_to(c.vitality);
    j.at("dexterity").get_to(c.dexterity);
    j.at("agility").get_to(c.agility);
    j.at("intelligence").get_to(c.intelligence);
    j.at("wisdom").get_to(c.wisdom);
    j.at("mana_bonus").get_to(c.mana_bonus);
    j.at("mana_scaling").get_to(c.mana_scaling);
}

int wmain() {
    // Create a character struct
    CharacterStats patchouli = {10, 12, 8, 7, 15, 14, 50.0, 1.5};

    // Convert to JSON
    json j = patchouli;
    std::cout << "JSON: " << j.dump(4) << std::endl;

    // Convert back to struct
    CharacterStats newCharacter = j.get<CharacterStats>();
    std::cout << "Strength: " << newCharacter.strength << std::endl;

    return 0;
}
