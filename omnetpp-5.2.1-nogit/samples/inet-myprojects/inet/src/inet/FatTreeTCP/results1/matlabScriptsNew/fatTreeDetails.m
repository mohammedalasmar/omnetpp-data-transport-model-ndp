function fatTreeDetails(k)
 
t0=annotation('textbox', [0.2 0.2 0.8 0.8], 'String', 'Simulation Configurations' ,'FitBoxToText','on');
sz = t0.FontSize;
t0.FontSize = 16;
c = t0.Color;
t0.Color = 'red';
c = t0.LineWidth;
t0.LineWidth =4;


 %%

conf=dlmread(fullfile('..','MatConfig.csv'));
numShortFlows=conf(2); 
simTime=conf(1); 
simTimeStrSec=[' Simulation Time  = ' , num2str(simTime) , ' seconds' ];
simTimeStrMi=['                     = ' , num2str(simTime/60) , ' minutes' ];




wallClockTime=conf(7); % real  time
wallClockTimeHr=['wallClockTime = ' , num2str(wallClockTime/60) , ' hours' ];
wallClockTimeMin=['             = ' , num2str(wallClockTime) , ' minutes' ];
wallClockTimeSec=['            = ' , num2str(wallClockTime*60) , ' seconds' ];


completingFlowRate= numShortFlows/(simTime);
completingFlowRateStr=['completingFlowRate= ', num2str(completingFlowRate), ' flows/sec'];

simTimeStr={wallClockTimeHr;wallClockTimeMin;wallClockTimeSec;' '; simTimeStrSec;simTimeStrMi;completingFlowRateStr };



numShortFlowsStr=['numShortFlows = ' , num2str(numShortFlows)];
flowSize=conf(3); 
flowSizeStr=['shortFlowSize(B) = ' , num2str(flowSize)];

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
 
inputConf={numShortFlowsStr;flowSizeStr; percentLongFlowNodesStr ; arrivalRateStr ; TMTypeStr  };


t1=annotation('textbox', [0.2 0.2 0.7 0.7], 'String', inputConf ,'FitBoxToText','on');
sz = t1.FontSize;
t1.FontSize = 16;

%%
numPods=k;

numServers= (k^3)/4;
numCores= (k/2)^2;
numAggPerPod= k/2;
totAgg=k*numAggPerPod;
numEdgePerPod= k/2;
totEdge=k*numEdgePerPod;
numServersPerPod=(k^2)/4;

numPodsStr=['numPods= ' , num2str(numPods)];
numServersStr=['numServers= ' , num2str(numServers)];
portRoutersStr=['#-ports= ' , num2str(k)];
numCoresStr=['numCores= ' , num2str(numCores)];
numAggPerPodStr=['numAggPerPod= ' , num2str(numAggPerPod)];
totAggStr=['totAgg= ' , num2str(totAgg)];
numEdgePerPodStr=['numEdgePerPod= ' , num2str(numEdgePerPod)];
totEdgeStr=['totEdge= ' , num2str(totEdge)];
numServersPerPodStr=['numServersPerPod= ' , num2str(numServersPerPod)];
 
configurations={numPodsStr; numServersStr ; portRoutersStr ; numServersPerPodStr ;numCoresStr;numAggPerPodStr;totAggStr;numEdgePerPodStr;totEdgeStr };

movegui('northwest')

t2=annotation('textbox', [0.2 0.2 0.4 0.4], 'String', configurations ,'FitBoxToText','on');
sz = t2.FontSize;
t2.FontSize = 16;



t3=annotation('textbox', [0.55 0.55 0.01 0.01], 'String', simTimeStr ,'FitBoxToText','on');
sz = t3.FontSize;
t3.FontSize = 12;


 end
