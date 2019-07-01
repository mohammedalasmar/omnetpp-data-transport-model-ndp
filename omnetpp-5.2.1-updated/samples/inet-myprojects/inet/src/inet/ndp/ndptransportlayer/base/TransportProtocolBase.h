#ifndef __INET_TRANSPORTPROTOCOLBASE_H
#define __INET_TRANSPORTPROTOCOLBASE_H

#include "inet/common/LayeredProtocolBase.h"
#include "inet/common/lifecycle/NodeOperations.h"

namespace inet {

class INET_API TransportProtocolBase: public LayeredProtocolBase {
public:
    TransportProtocolBase() {
    }
    ;

protected:
    virtual bool isInitializeStage(int stage) override {
        return stage == INITSTAGE_TRANSPORT_LAYER;
    }
    virtual bool isNodeStartStage(int stage) override {
        return stage == NodeStartOperation::STAGE_TRANSPORT_LAYER;
    }
    virtual bool isNodeShutdownStage(int stage) override {
        return stage == NodeShutdownOperation::STAGE_TRANSPORT_LAYER;
    }
};

} // namespace inet

#endif // ifndef __INET_TRANSPORTPROTOCOLBASE_H

