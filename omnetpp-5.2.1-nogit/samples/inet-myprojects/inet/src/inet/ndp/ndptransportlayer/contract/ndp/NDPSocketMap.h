
#ifndef __INET_NDPSocketMap_H
#define __INET_NDPSocketMap_H

#include <map>

#include "inet/common/INETDefs.h"
#include "NDPSocket.h"


namespace inet {

/**
 * Small utility class for managing a large number of NDPSocket objects.
 */
//TBD: need for lookup could be eliminated by adding a void *yourPtr into NDPConnection and NDPCommand
class INET_API NDPSocketMap
{
  protected:
    typedef std::map<int, NDPSocket *> SocketMap;
    SocketMap socketMap;

  public:
    /**
     * Constructor.
     */
    NDPSocketMap() {}

    /**
     * Destructor. Does NOT delete the NDPSocket objects.
     */
    ~NDPSocketMap() {}

    /**
     * Finds the socket (by connId) for the given message. The message
     * must have arrived from NDP, and must contain a NDPCommand
     * control info object. The method returns nullptr if the socket was
     * not found, and throws an error if the message doesn't contain
     * a NDPCommand.
     */
    NDPSocket *findSocketFor(cMessage *msg);

    /**
     * Registers the given socket. Should not be called multiple times
     * for one socket object.
     */
    void addSocket(NDPSocket *socket);

    /**
     * Removes the given socket from the data structure.
     */
    NDPSocket *removeSocket(NDPSocket *socket);

    /**
     * Returns the number of sockets stored.
     */
    unsigned int size() { return socketMap.size(); }

    /**
     * Deletes the socket objects.
     */
    void deleteSockets();
};

} // namespace inet

#endif // ifndef __INET_NDPSocketMap_H

