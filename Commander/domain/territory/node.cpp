#include "node.h"

using namespace Domain;
using namespace Domain::Territory;

Node::Node()
{
}

Node::~Node()
{
}

Belligerent *Node::belligerent()
{
    return m_belligerent;
}

Node *Node::parent()
{
    return m_parent;
}

Node *Node::parentDefault()
{
    return m_parentDefault;
}

void Node::setBelligerent(Belligerent *value)
{
    m_belligerent = value;
}

void Node::parent(Node *value)
{
    m_parent = value;
}

void Node::parentDefault(Node *value)
{
    m_parentDefault = value;
}
