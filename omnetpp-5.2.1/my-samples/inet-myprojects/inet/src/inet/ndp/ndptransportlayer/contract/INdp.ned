

package inet.ndp.ndptransportlayer.contract;
 
moduleinterface INdp
{
    @display("i=block/wheelbarrow");
    gates:
        input appIn[] @labels(NDPCommand/down);
        input ipIn @labels(NDPSegment,IPv4ControlInfo/up,IPv6ControlInfo/up);
        output appOut[] @labels(NDPCommand/up);
        output ipOut @labels(NDPSegment,IPv4ControlInfo/down,IPv6ControlInfo/down);
}
