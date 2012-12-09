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

private:
    Belligerent* belligerent(){return m_belligerent;}
    Node* parent(){return m_parent;}
    Node* parentDefault(){return m_parentDefault;}
    Point2D pos(){return m_pos;}

    bool isNearEdge(){return m_nearEdge;}
    bool isExplored(){return m_explored;}
    bool isConstant(){return m_constant;}

    void setBelligerent(Belligerent* value){m_belligerent = value;}
    void setParent(Node* value){m_parent = value;}
    void setParentDefault(Node* value){m_parentDefault = value;}
    void setPos(const Point2D& value){m_pos = value;}

    void setNearEdge(bool value){m_nearEdge = value;}
    void setExplored(bool value){m_explored = value;}
    void setConstant(bool value){m_constant = value;}

private:
    Belligerent* m_belligerent;
    Node* m_parent;
    Node* m_parentDefault;
    Point2D m_pos;

    bool m_nearEdge;
    bool m_explored;
    bool m_constant;
};

}}

#endif // NODE_H
