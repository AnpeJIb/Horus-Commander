#ifndef NODE_CARRIER_H
#define NODE_CARRIER_H

#include "node.h"

namespace Domain { namespace Territory {

class NodeCarrier
{
public:
    NodeCarrier();

    Node* node();
    void setNode(Node* value);

protected:
    Node* m_node;
};

}}

#endif // NODE_CARRIER_H
