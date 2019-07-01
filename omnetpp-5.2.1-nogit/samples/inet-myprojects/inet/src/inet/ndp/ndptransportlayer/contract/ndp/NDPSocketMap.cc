
#include "inet/common/INETDefs.h"
#include "NDPSocketMap.h"


namespace inet {

NDPSocket *NDPSocketMap::findSocketFor(cMessage *msg)
{
    NDPCommand *ind = dynamic_cast<NDPCommand *>(msg->getControlInfo());
    if (!ind)
        throw cRuntimeError("NDPSocketMap: findSocketFor(): no NDPCommand control info in message (not from NDP?)");

    int connId = ind->getConnId();
    auto i = socketMap.find(connId);
    ASSERT(i == socketMap.end() || i->first == i->second->getConnectionId());
    return (i == socketMap.end()) ? nullptr : i->second;
}

void NDPSocketMap::addSocket(NDPSocket *socket)
{
    ASSERT(socketMap.find(socket->getConnectionId()) == socketMap.end());
    socketMap[socket->getConnectionId()] = socket;
}

NDPSocket *NDPSocketMap::removeSocket(NDPSocket *socket)
{
    auto i = socketMap.find(socket->getConnectionId());
    if (i != socketMap.end())
        socketMap.erase(i);
    return socket;
}

void NDPSocketMap::deleteSockets()
{
    for (auto & elem : socketMap)
        delete elem.second;
    socketMap.clear();
}

} // namespace inet

