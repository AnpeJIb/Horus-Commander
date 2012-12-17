#ifndef BATTLEGROUND_H
#define BATTLEGROUND_H

#include <QtCore>
#include <QString>

#include "generic_domain.h"
#include "title_carrier.h"
#include "node_carrier.h"

namespace Domain { namespace Territory {

class Battleground: public GenericDomain, public TitleCarrier, public NodeCarrier
{
public:
    Battleground();
    ~Battleground();

    Node* node();
    void setNode(Node* value);

    uint length;
    uint width;
    uint maxHeight;
    qint8 timeZoneUTC;
    float imgScaleKmPer100Px;

    QString summerVariantDirTitle;
    QString autumnVariantDirTitle;
    QString winterVariantDirTitle;
    QString springVariantDirTitle;

    QString mapImgPath;
    QString mapAlphaImgPath;
};

}}

#endif // BATTLEGROUND_H
