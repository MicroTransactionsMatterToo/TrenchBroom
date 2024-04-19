//
// Created by ennis on 12/04/24.
//

#include "IOLink.h"

#include "EntityNodeBase.h"

#include <utility>

namespace TrenchBroom
{
namespace Model
{
IOLink::IOLink(
  Assets::OutputPropertyDefinition* definition,
  EntityNodeBase* emitter,
  std::string trigger,
  std::string targetName,
  std::string targetInput,
  const float refireCount,
  const float fireDelay,
  IOParameter paramValue)
  : m_trigger{std::move(trigger)}
  , m_targetName{std::move(targetName)}
  , m_targetInput{std::move(targetInput)}
  , m_refireCount{refireCount}
  , m_fireDelay{fireDelay}
  , m_parameterValue{std::move(paramValue)}
  , m_definition{definition}
  , m_emitter{emitter}
  , m_uuid{QUuid::createUuid()}
{
}

const std::string& IOLink::trigger()
{
  return m_trigger;
}

const std::string& IOLink::targetName()
{
  return m_targetName;
}
const std::string& IOLink::targetInput()
{
  return m_targetInput;
}
float IOLink::refireCount() const
{
  return m_refireCount;
}
float IOLink::fireDelay() const
{
  return m_fireDelay;
}
IOParameter IOLink::parameterValue()
{
  return m_parameterValue;
}
EntityNodeBase* IOLink::emitter() const
{
  return m_emitter;
}
std::vector<EntityNodeBase*>& IOLink::targets()
{
  return m_targets;
}
Assets::OutputPropertyDefinition* IOLink::definition() const
{
  return m_definition;
}
QUuid IOLink::uuid() const
{
  return m_uuid;
}

std::ostream& operator<<(std::ostream& lhs, const IOLink& rhs)
{
  lhs << rhs.definition()->key();
  return lhs;
}

bool operator==(const IOLink& lhs, const IOLink& rhs)
{
  return lhs.uuid() == rhs.uuid();
}
} // namespace Model
} // namespace TrenchBroom