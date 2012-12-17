#ifndef NODE_H
#define NODE_H

#include "generic_domain.h"
#include "kind_carrier.h"
#include "belligerent_carrier.h"
#include "pointF2D.h"

namespace Domain { namespace Territory {

class Node;

class Node: public GenericDomain, public KindCarrier, public BelligerentCarrier
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
    ~Node();

    Belligerent* belligerent();
    Node* parent();
    Node* parentDefault();

    void setBelligerent(Belligerent* value);
    void parent(Node* value);
    void parentDefault(Node* value);

    PointF2D pos;

    bool isExplored;
    bool isConstant;

private:
    Node* m_parent;
    Node* m_parentDefault;
};

}}

#endif // NODE_H
