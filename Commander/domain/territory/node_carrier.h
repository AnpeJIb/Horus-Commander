#ifndef NODE_CARRIER_H
#define NODE_CARRIER_H

#include "node.h"

namespace Domain { namespace Territory {

class NodeCarrier
{
public:
    NodeCarrier();

    Node* node(){return m_node;}
    void setNode(Node* value){m_node = value;}

protected:
    Node* m_node;
};

}}

#endif // NODE_CARRIER_H
