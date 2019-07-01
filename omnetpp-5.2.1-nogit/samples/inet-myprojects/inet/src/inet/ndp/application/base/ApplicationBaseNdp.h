

#ifndef __INET_APPLICATIONBASE_H
#define __INET_APPLICATIONBASE_H

#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/lifecycle/NodeOperations.h"

namespace inet {

class INET_API ApplicationBaseNdp : public OperationalBase
{
  public:
    ApplicationBaseNdp();

  protected:
    virtual bool isInitializeStage(int stage) override { return stage == INITSTAGE_APPLICATION_LAYER; }
    virtual bool isNodeStartStage(int stage) override { return stage == NodeStartOperation::STAGE_APPLICATION_LAYER; }
    virtual bool isNodeShutdownStage(int stage) override { return stage == NodeShutdownOperation::STAGE_APPLICATION_LAYER; }
};

} // namespace inet

#endif // ifndef __INET_APPLICATIONBASE_H

