#ifndef BATTLEGROUND_H
#define BATTLEGROUND_H

#include <QtCore>
#include <QString>

#include "generic_domain.h"
#include "titled_domain.h"
#include "node_carrier.h"

namespace Domain { namespace Territory {

class Battleground: public GenericDomain, public TitledDomain, public NodeCarrier
{
public:
    Battleground();

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
