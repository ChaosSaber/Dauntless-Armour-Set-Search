#include "gear/Gear.hpp"
#include <sstream>

Gear::Gear::Gear(const std::string& name, const std::string& description, int level,
                 const Skill& skill, const std::vector<std::string>& uniqueSkills,
                 const std::vector<Cell>& cells)
    : name_(name), description_(description), level_(level), skill_(skill),
      uniqueSkills_(uniqueSkills), cells_(cells)
{
}

Gear::Gear::Gear(std::string&& name, std::string&& description, int level, Skill&& skill,
                 std::vector<std::string>&& uniqueSkills, std::vector<Cell>&& cells)
    : name_(std::move(name)), description_(std::move(description)), level_(level),
      skill_(std::move(skill)), uniqueSkills_(std::move(uniqueSkills)), cells_(std::move(cells))
{
}

Gear::Gear::Gear(const Gear& other)
    : Gear(other.name_, other.description_, other.level_, other.skill_, other.uniqueSkills_,
           other.cells_)
{
}

Gear::Gear::Gear(Gear&& other)
    : Gear(std::move(other.name_), std::move(other.description_), other.level_,
           std::move(other.skill_), std::move(other.uniqueSkills_), std::move(other.cells_))
{
}

const std::string& Gear::Gear::getName() const { return name_; }

int Gear::Gear::getLevel() const { return level_; }

const std::string& Gear::Gear::getDescription() const { return description_; }

bool Gear::Gear::hasUniqueSkill() const { return uniqueSkills_.size() != 0; }

const std::vector<std::string>& Gear::Gear::getUniqueSkills() const { return uniqueSkills_; }

Gear::SkillList Gear::Gear::getSkills() const
{
    if (skill_.getSkillPoints() == 0)
        return SkillList();
    return skill_;
}

bool Gear::Gear::hasSkill(const std::string& skill) const
{
    if (skill_.getName().empty())
        return false;
    return skill_.getName() == skill;
}

int Gear::Gear::getSkillPointsFor(const std::string& skill) const
{
    if (!skill_.getName().empty() && skill_.getName() == skill)
        return skill_.getSkillPoints();
    return 0;
}

std::string Gear::Gear::getGearInfo(const Dictionary& dict) const
{
    return dict.getTranslationFor(name_) + " +" + std::to_string(level_);
}

std::string Gear::Gear::getToolTip(const Dictionary& dict) const
{
    std::stringstream ss;
    ss << description_ << std::endl;
    if (skill_.getSkillPoints() > 0)
        ss << skill_.toString(dict) << std::endl;
    for (const auto& skill : uniqueSkills_)
        ss << skill << std::endl;
    for (auto& cell : cells_)
        ss << dict.getTranslationFor(cellSlotToStringKey(cell.getCellType()));
    return ss.str();
}

bool Gear::Gear::hasFreeCellSlotFor(SkillType type) const
{
    for (auto& cell : cells_)
        if (cell.isEmpty() && cell.getCellType() == type)
            return true;
    return false;
}

Gear::CellList Gear::Gear::getCellList() const { return cells_; }

bool Gear::Gear::addCell(const Cell& cell)
{
    for (auto& cell_ : cells_)
    {
        if (cell_.isEmpty() && cell_.getCellType() == cell.getCellType())
        {
            cell_ = cell;
            return true;
        }
    }
    return false;
}