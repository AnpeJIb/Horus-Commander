#ifndef NODE_H
#define NODE_H

#include "generic_domain.h"
#include "type_carrier.h"
#include "belligerent.h"
#include "point2d.h"

namespace Domain { namespace Territory {

class Node;

class Node: public GenericDomain, public TypeCarrier
{
public:
    enum NodeType
    {
        NODE_HEADQUARTERS   = 0,
        NODE_MAP            = 1,
        NODE_TOWN           = 2,
        NODE_AIRFIELD       = 3,
        NODE_AREA           = 4,
        NODE_PATH           = 5
    };

    Node();

    Belligerent* belligerent();
    Node* parent();
    Node* parentDefault();

    void setBelligerent(Belligerent* value);
    void parent(Node* value);
    void parentDefault(Node* value);

    PointF2D pos;

    bool nearEdge;
    bool explored;
    bool constant;

private:
    Belligerent* m_belligerent;
    Node* m_parent;
    Node* m_parentDefault;
};

}}

#endif // NODE_H
