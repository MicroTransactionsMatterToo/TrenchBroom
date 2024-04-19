//
// Created by ennis on 12/04/24.
//

#pragma once
#include <QUuid>

#include "Assets/PropertyDefinition.h"


namespace TrenchBroom::Model
{
class EntityNodeBase;
}
namespace TrenchBroom
{
namespace Model
{
using IOParameter = std::variant<int, float, std::string, std::nullptr_t>;

class IOLink
{
private:
  QUuid m_uuid;
  std::string m_trigger;
  std::string m_targetName;
  std::string m_targetInput;
  float m_refireCount;
  float m_fireDelay;
  IOParameter m_parameterValue;

  Assets::OutputPropertyDefinition* m_definition;
  EntityNodeBase* m_emitter;
  std::vector<EntityNodeBase*> m_targets;

public:
  IOLink(
    Assets::OutputPropertyDefinition* definition,
    EntityNodeBase* emitter,
    std::string trigger,
    std::string targetName,
    std::string targetInput,
    float refireCount = -1,
    float fireDelay = 0,
    IOParameter paramValue = {nullptr});

  QUuid uuid() const;
  const std::string& trigger();
  const std::string& targetName();
  const std::string& targetInput();
  float refireCount() const;
  float fireDelay() const;
  IOParameter parameterValue();

  Assets::OutputPropertyDefinition* definition() const;
  EntityNodeBase* emitter() const;
  std::vector<EntityNodeBase*>& targets();


};

std::ostream& operator<< (std::ostream& lhs, const IOLink& rhs);
bool operator==(const IOLink& lhs, const IOLink& rhs);
} // namespace Model

} // namespace TrenchBroom
