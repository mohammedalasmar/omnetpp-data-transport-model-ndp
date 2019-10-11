# ndp-tcp-datacentre-omnetpp-model

This repository includes the codes for our OMNeT++ Summit 2019 paper (see this link https://github.com/mohammedalasmar/ndpTcpDatacentreOmnetppModel/blob/master/datacentre-omnetpp.pdf).

The paper includes implementations for some data centre protocols in OMNeT++/INET. These implementations are as follows: \
(1) FatTree topology\
(2) Per-packet and per-flow ECMP\
(3) A model of NDP protocol in INET\
(4) Evaluating the performance of TCP and NDP in a FatTree topology\
(5) A central traffic scheduler for scheduling flows in the simulated network and setting up simulation parameters for experimenting with the above-mentioned contributions.   


=============================================

STEP1: compile omnetpp project:\
(1) Open a new terminal and go to the  omnetpp-5.2.1 directory\ 
(2) omnetpp-5.2.1$ ./configure\
(3) omnetpp-5.2.1$ . setenv\
(4) omnetpp-5.2.1$ make cleanall\
(5) omnetpp-5.2.1$ make -j4

[![Watch the video](https://live.staticflickr.com/65535/48716277907_e413164ca4_m_d.jpg)](https://drive.google.com/file/d/12lFCZBZKDBOSbrI7KJYmBaCnjm3GLPCa/view?usp=sharing
)



STEP2: compile inet and ndp projects:\
(1) Go to this directory: omnetpp-5.2.1/my-samples/inet-myprojects/inet\
(2) inet$ make makefiles\
(3)  Go to this directory: omnetpp-5.2.1/my-samples/inet-myprojects/inet/src\
(4)  .. inet/src$ make -j4

[![Watch the video](https://live.staticflickr.com/65535/48716277907_e413164ca4_m_d.jpg)](https://drive.google.com/file/d/1Qrb2r71MZxAeSat6jRhH1mEShvqBrGcM/view?usp=sharing
)



STEP3: run an NDP example in the terminal:\
(1) There is an ini file that shows an example for NDP model in this directory\
omnetpp-5.2.1/my-samples/inet-myprojects/inet/src/inet/ndp/FatTreeNDP/exp1-1-seed1.ini\

(2) There is a shell script that can be used to run this example and it generates several csv files, see\
omnetpp-5.2.1/my-samples/inet-myprojects/inet/src/inet/ndp/FatTreeNDP/exp1-1-seed1/runNewShell.sh\

(3) To run the shell script, type this command in the terminal\
$ sh -e runNewShell.sh  8  100

Note that: the shell script takes two input parameters which are: K (FatTree size) (e.g. K = 8) and numShortFlows to\ simulate (e.g. numShortFlows = 100)

(4) There are several Matalb scripts to plot the results from this experiment. You can run all of them by calling the\ 'plotResults.m' Matlab script. 





=============================================
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
