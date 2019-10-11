# ndp-tcp-datacentre-omnetpp-model

This repository includes the codes for our OMNeT++ Summit 2019 paper (see this link https://github.com/mohammedalasmar/ndpTcpDatacentreOmnetppModel/blob/master/datacentre-omnetpp.pdf).

The paper includes implementations for some data centre protocols in OMNeT++/INET. These implementations are as follows: 
(1) FatTree topology
(2) Per-packet and per-flow ECMP
(3) A model of NDP protocol in INET
(4) Evaluating the performance of TCP and NDP in a FatTree topology
(5) A central traffic scheduler for scheduling flows in the simulated network and setting up simulation parameters for experimenting with the above-mentioned contributions 




An implementation of NDP[1] protocol (SIGCOMM 2017 Best Paper Award) in OMNeT++/INET. 

[1] NDP: Re-Architecting Datacenter Networks and Stacks for Low Latency https://gianniantichi.github.io/files/papers/ndp.pdf 

This model is based on OMNeT++v5.2.1 and INETv3.6.3.


Click on the video symbol below to watch the DEMO:


[![Watch the video](https://live.staticflickr.com/65535/48716277907_e413164ca4_m_d.jpg)](https://drive.google.com/file/d/1K5unvUnAxxSCegsLscOYE1raJuEGrF4v/view?usp=sharing
)




ndp-tcp-datacentre-omnetpp-model
/samples/inet-myprojects/inet/src/inet/ndp/

NDP Design

![alt text](https://live.staticflickr.com/65535/48706583473_cbcfd528a0_z_d.jpg)


NDP in OMNeT++/INET

![alt text](https://live.staticflickr.com/65535/48707103072_f57811f959_z_d.jpg)


![alt text](https://live.staticflickr.com/65535/48706601793_6ebd9eb6ee_z_d.jpg)



Per-packet vs per-flow ECMP

![alt text](https://live.staticflickr.com/65535/48706601763_51955a574a_z_d.jpg)
