

cplusplus {{
#include "inet/common/INETDefs.h"
}}

namespace inet;

 
packet GenericAppMsgNdp
{
  
    int numPaketToSend;  //  if this is a reader(receiver)
    bool isSender;  // receiver 
    bool isReceiver;  // receiver 
   	bool isLongFlow;
    bool serverClose;        // if true, server should close the
 }



