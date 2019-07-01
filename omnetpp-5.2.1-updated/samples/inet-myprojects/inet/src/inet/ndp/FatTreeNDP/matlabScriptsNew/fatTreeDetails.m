function fatTreeDetails
 


t0=annotation('textbox', [0.2 0.2 0.8 0.8], 'String', 'Simulation Configurations' ,'FitBoxToText','on');
sz = t0.FontSize;
t0.FontSize = 16;
c = t0.Color;
t0.Color = 'red';
c = t0.LineWidth;
t0.LineWidth =4;


 %%

conf=dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
numShortFlows=conf(2); 
simTime=conf(1); 
simTimeStrSec=[' Simulation Time  = ' , num2str(simTime) , ' seconds' ];
simTimeStrMi=['                     = ' , num2str(simTime/60) , ' minutes' ];

k = conf(16);


wallClockTime=conf(7); % real  time
wallClockTimeHr=['wallClockTime = ' , num2str(wallClockTime/60) , ' hours' ];
wallClockTimeMin=['             = ' , num2str(wallClockTime) , ' minutes' ];
wallClockTimeSec=['            = ' , num2str(wallClockTime*60) , ' seconds' ];


completingFlowRate= numShortFlows/(simTime);
completingFlowRateStr=['completingFlowRate= ', num2str(completingFlowRate), ' flows/sec'];

simTimeStr={wallClockTimeHr;wallClockTimeMin;wallClockTimeSec;' '; simTimeStrSec;simTimeStrMi;completingFlowRateStr };



numShortFlowsStr=['numShortFlows = ' , num2str(numShortFlows)];
flowSize=conf(3); 
flowSizeBytes = flowSize*1500; 
if flowSizeBytes < 10^6
    flowSizeBytes = flowSizeBytes/10^3;
    flowSizeBytesUnit = ' KBytes';
else
    flowSizeBytes = flowSizeBytes/10^6;
    flowSizeBytesUnit = ' MBytes';
end

flowSizeStr=['shortFlowSize = ' , num2str(flowSize) ,' Symbols = ' num2str(flowSizeBytes) , flowSizeBytesUnit];

percentLongFlowNodes=conf(4)*100;  
percentLongFlowNodesStr=['percentLongFlowNodes = ' , num2str(percentLongFlowNodes) ,'%'];

arrivalRate=conf(5); 
arrivalRateStr=['arrivalRate = ' , num2str(arrivalRate)];

TMtype=conf(6);
if TMtype==0
    TMTypeStr= ['TM type= permTM'];
elseif TMtype==1
    TMTypeStr= ['TM type= randTM'];
else 
    TMTypeStr= ['undefined'];
end
 

IW=conf(8);
IWStr = ['IW = ', num2str(conf(8))];

ndpSwitchQueueLength=conf(9);
ndpSwitchQueueLengthStr = ['switchQueueLength = ', num2str(ndpSwitchQueueLength)];

perFlowEcmp = conf(10);
perPacketEcmp = conf(11);



if perFlowEcmp==1
    ecmpType= ['ecmpType = perFlowEcmp'];
elseif perPacketEcmp==1
    ecmpType= ['ecmpType = perPacketEcmp'];
else 
    ecmpType= ['undefined'];
end

oneToOne =  conf(12);
manyToOne = conf(13);
oneToMany = conf(14);

if oneToOne==1
    patternType= ['patternType = oneToOne'];
elseif manyToOne==1
    patternType= ['patternType = manyToOne'];
elseif oneToMany==1
    patternType= ['patternType = oneToMany'];
else
    patternType= ['undefined'];
end

seedValue = conf(15);
seedValueStr = ['seedValue = ', num2str(seedValue)];

numPods=k;
numCores= (k/2)^2;
numServers= (k^3)/4;
numServersStr=['numServers= ' , num2str(numServers)];
numCoresStr=['numCores= ' , num2str(numCores)];
inputConf={numServersStr ; numCoresStr; numShortFlowsStr;flowSizeStr; percentLongFlowNodesStr ; arrivalRateStr ; TMTypeStr ; IWStr ; ndpSwitchQueueLengthStr ; ecmpType ; patternType ;seedValueStr  };


t1=annotation('textbox', [0.2 0.2 0.72 0.72], 'String', inputConf ,'FitBoxToText','on');
sz = t1.FontSize;
t1.FontSize = 16;

%%

% 
% numAggPerPod= k/2;
% totAgg=k*numAggPerPod;
% numEdgePerPod= k/2;
% totEdge=k*numEdgePerPod;
% numServersPerPod=(k^2)/4;
% 
% numPodsStr=['numPods= ' , num2str(numPods)];
% 
% portRoutersStr=['#-ports= ' , num2str(k)];
% 
% numAggPerPodStr=['numAggPerPod= ' , num2str(numAggPerPod)];
% totAggStr=['totAgg= ' , num2str(totAgg)];
% numEdgePerPodStr=['numEdgePerPod= ' , num2str(numEdgePerPod)];
% totEdgeStr=['totEdge= ' , num2str(totEdge)];
% numServersPerPodStr=['numServersPerPod= ' , num2str(numServersPerPod)];
%  
% configurations={numPodsStr; numServersStr ; portRoutersStr ; numServersPerPodStr ;numCoresStr;numAggPerPodStr;totAggStr;numEdgePerPodStr;totEdgeStr };
% 
% movegui('northwest')
% 
% t2=annotation('textbox', [0.2 0.2 0.4 0.4], 'String', configurations ,'FitBoxToText','on');
% sz = t2.FontSize;
% t2.FontSize = 16;



t3=annotation('textbox', [0.20 0.20 0.128 0.128], 'String', simTimeStr ,'FitBoxToText','on');
sz = t3.FontSize;
t3.FontSize = 14;


 end
