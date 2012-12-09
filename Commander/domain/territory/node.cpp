#include "node.h"

Domain::Belligerent *Domain::Territory::Node::belligerent()
{
    // TODO: NULL-CHECK
    return m_belligerent;
}

Domain::Territory::Node *Domain::Territory::Node::parent()
{
    // TODO: NULL-CHECK
    return m_parent;
}

Domain::Territory::Node *Domain::Territory::Node::parentDefault()
{
    // TODO: NULL-CHECK
    return m_parentDefault;
}

void Domain::Territory::Node::setBelligerent(Domain::Belligerent *value)
{
    // TODO: NULL-CHECK
    m_belligerent = value;
}

void Domain::Territory::Node::parent(Domain::Territory::Node *value)
{
    // TODO: NULL-CHECK
    m_parent = value;
}

void Domain::Territory::Node::parentDefault(Domain::Territory::Node *value)
{
    // TODO: NULL-CHECK
    m_parentDefault = value;
}
