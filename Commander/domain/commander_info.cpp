#include "commander_info.h"

using namespace Domain;

CommanderInfo::CommanderInfo()
{
}

CommanderInfo::~CommanderInfo()
{
}

Scheme *CommanderInfo::scheme()
{
    return m_scheme;
}

void CommanderInfo::setScheme(Scheme *value)
{
    m_scheme = value;
}
