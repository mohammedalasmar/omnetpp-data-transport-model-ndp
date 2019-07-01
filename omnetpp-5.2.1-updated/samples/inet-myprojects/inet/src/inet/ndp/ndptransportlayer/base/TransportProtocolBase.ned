
package inet.ndp.ndptransportlayer.base;

import inet.common.LayeredProtocolBase;

 
simple TransportProtocolBase extends LayeredProtocolBase
{
    gates:
        input upperLayerIn[];
        output upperLayerOut[];
        input lowerLayerIn @labels(ITransportPacket/up);
        output lowerLayerOut @labels(ITransportPacket/down);
}
