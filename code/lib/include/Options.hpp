#ifndef DAUNTLESS_ASS_OPTIONS_HPP
#define DAUNTLESS_ASS_OPTIONS_HPP

#include "Dictionary.hpp"
#include "gear/ArmourSet.hpp"
#include "gear/Armoury.hpp"
#include "gear/Cell.hpp"
#include "util/files.hpp"
#include <QDir>
#include <QJsonObject>
#include <array>
#include <optional>
#include <string>
#include <unordered_map>

#define NUMBER_OF_SKILLSELECTORS 9

class OptionsIoException
{
  public:
    OptionsIoException(std::string what) : what(std::move(what)) {}
    std::string what;
};

const QString CONFIG_FILE_NAME =
    util::files::pathAppend(util::files::DOCUMENTS_LOCATION, "setting.json");
const QString LAST_SEARCH =
    util::files::pathAppend(util::files::DOCUMENTS_LOCATION, "lastSearch.ass");
const QString STANDARD_CELL_SAVE_LOCATION =
    util::files::pathAppend(util::files::DOCUMENTS_LOCATION, "cells");
const QString MY_CELLS = util::files::pathAppend(STANDARD_CELL_SAVE_LOCATION, "myCells.cells");
const QString STANDARD_SEARCH_SAVE_LOCATION =
    util::files::pathAppend(util::files::DOCUMENTS_LOCATION, "searches");
const QString MY_LOADOUTS =
    util::files::pathAppend(util::files::DOCUMENTS_LOCATION, "myLoadouts.loadout");

class Options
{

  public:
    Options();
    struct SkillSearch
    {
        Gear::SkillType filter = Gear::SkillType::None;
        std::string skillName = "";
        int skillLevel = 0;
    };
    struct Loadout
    {
      public:
        std::string name;
        Gear::ArmourSet set;
        Loadout(const std::string& name, const Gear::ArmourSet& set) : name(name), set(set) {}
    };
    void loadConfiguration(const Gear::Armoury& armoury,
                           const QString& fileName = CONFIG_FILE_NAME);
    void saveConfiguration(const QString& fileName = CONFIG_FILE_NAME);
    void loadSearch(const Gear::Armoury& armoury, const Dictionary& dict,
                    const QString& fileName = LAST_SEARCH);
    void saveSearch(const Gear::Armoury& armoury, const QString& fileName = LAST_SEARCH);
    void save(const Gear::Armoury& armoury);
    void saveCells(const Gear::Armoury& armoury, const QString& fileName = MY_CELLS);
    void loadCells(const Gear::Armoury& armoury, const Dictionary& dict,
                   const QString& fileName = MY_CELLS);
    void saveMyLoadouts(const Gear::Armoury& armoury, const QString& fileName = MY_LOADOUTS);
    void loadMyLoadouts(const Gear::Armoury& armoury, const Dictionary& dict,
                        const QString& fileName = MY_LOADOUTS);

    int numberOfResults = 100;
    std::string language = "English";
    std::unordered_map<std::string, bool> checkedGear;
    std::unordered_map<Gear::Cell, int> cells;
    std::array<SkillSearch, NUMBER_OF_SKILLSELECTORS> skillSearches;
    std::vector<Gear::ArmourSet> armourSets;
    Gear::WeaponType weaponType = Gear::WeaponType::Sword;
    Gear::Element weaponElement = Gear::Element::All;
    QString lastSearchSaveLocation = STANDARD_SEARCH_SAVE_LOCATION;
    QString lastCellSaveLocation = STANDARD_CELL_SAVE_LOCATION;
    QString lastExportTextSaveLocation = util::files::DOCUMENTS_LOCATION;
    int cellUsage = 0;
    bool useLowerTierArmour = true;
    int tier = 3;
    std::vector<Loadout> myLoadouts;

  private:
    QJsonArray cellListToJson(const Gear::CellList& cells, const Gear::Armoury& armoury);
    Gear::CellList jsonToCellList(const QJsonArray& json, const Gear::Armoury& armoury);
    QJsonObject cellToJson(const Gear::Cell& cell, const Gear::Armoury& armoury);
    Gear::Cell jsonToCell(const QJsonObject& json, const Gear::Armoury& armoury);
    QJsonObject gearToJson(const Gear::Gear& armour);
    std::tuple<std::string, int> jsonToGear(const QJsonObject& json);
    Gear::Armour jsonToArmour(const QJsonObject& json, const Gear::Armoury& armoury);
    Gear::Weapon jsonToWeapon(const QJsonObject& json, const Gear::Armoury& armoury);
    std::optional<Gear::ArmourSet> jsonToArmourSet(const QJsonObject& json,
                                                   const Gear::Armoury& armoury);
    QJsonObject armourSetToJson(const Gear::ArmourSet& set, const Gear::Armoury& armoury);
};

#endif // !DAUNTLESS_ASS_OPTIONS_HPP