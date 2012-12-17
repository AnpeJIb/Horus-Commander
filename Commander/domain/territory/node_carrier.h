#ifndef NODE_CARRIER_H
#define NODE_CARRIER_H

#include "node.h"

namespace Domain { namespace Territory {

class NodeCarrier
{
public:
    virtual Node* node() = 0;
    virtual void setNode(Node* value) = 0;

protected:
    Node* m_node;
};

}}

#endif // NODE_CARRIER_H
