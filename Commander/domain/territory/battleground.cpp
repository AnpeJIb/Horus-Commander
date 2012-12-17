#include "battleground.h"

using namespace Domain::Territory;

Battleground::Battleground()
{
}

Battleground::~Battleground()
{
}

Node *Battleground::node()
{
    return m_node;
}

void Battleground::setNode(Node *value)
{
    m_node = value;
}
