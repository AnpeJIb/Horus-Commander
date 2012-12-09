#include "node_carrier.h"

Domain::Territory::NodeCarrier::NodeCarrier()
    : m_node(0)
{
}

Domain::Territory::Node *Domain::Territory::NodeCarrier::node()
{
    // TODO: NULL-CHECK
    return m_node;
}

void Domain::Territory::NodeCarrier::setNode(Domain::Territory::Node *value)
{
    // TODO: NULL-CHECK
    m_node = value;
}
