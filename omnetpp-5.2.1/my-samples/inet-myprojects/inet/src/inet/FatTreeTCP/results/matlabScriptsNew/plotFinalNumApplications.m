
function plotFinalNumApplications(K)

%%
k=K;
% numShortFlows = 100;

conf=dlmread(fullfile('..','MatConfig.csv'));
percentLongFlowNodes=conf(4) ; 
kBytes=conf(3)/1000;

% percentLongFlowNodes=0.33;
% kBytes= 70 ;
numServers= (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 

%%


nodes=0; 
fid = fopen(fullfile('..','MatNodes.csv'));
textLine = fgets(fid); % Read first line.
lineCounter = 1;
while ischar(textLine)
   textLine= strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ; 
    for i=1:length(numbers)
    nodes(end+1)= numbers(i) ;
    end
	% Read the next line.
    textLine = fgets(fid);
	lineCounter = lineCounter + 1;
end
fclose(fid);

nodesRes=nodes(2:end);

%%
numSink=0; 
fid = fopen(fullfile('..','MatNumTcpSinkApps.csv'));
textLine = fgets(fid); % Read first line.
lineCounter = 1;
while ischar(textLine)
   textLine= strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ; 
    for i=1:length(numbers)
    numSink(end+1)= numbers(i) ;
    end
	% Read the next line.
    textLine = fgets(fid);
	lineCounter = lineCounter + 1;
end
fclose(fid);
numSinkRes=numSink(2:end);

%%
numSession=0; 
fid = fopen(fullfile('..','MatNumTcpSessionApps.csv'));
textLine = fgets(fid); % Read first line.
lineCounter = 1;
while ischar(textLine)
   textLine= strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ; 
    for i=1:length(numbers)
    numSession(end+1)= numbers(i) ;
    end
	% Read the next line.
    textLine = fgets(fid);
	lineCounter = lineCounter + 1;
end
fclose(fid);

numSessionRes=numSession(2:end);


%%
figure
movegui('southwest');
subplot(211)
imTitle = ['#created applications at each server (#servers run longFlows=', num2str(numlongflowsRunningServers) , ',  #servers run shortFlows=', num2str(numServers-numlongflowsRunningServers) ];
 
stem(nodesRes(numlongflowsRunningServers+1:end),numSinkRes(numlongflowsRunningServers+1:end)) 
if numlongflowsRunningServers~=0
hold on
stem(nodesRes(1:numlongflowsRunningServers),numSinkRes(1:numlongflowsRunningServers), 'r') 
end
 legend('ShortFlows  Nodes',' LongFlows Nodes')

set(gca,'fontsize',10)
% set(gca,'XTick',1:numServers)
title(imTitle);

xlabel('servers', 'FontSize',13)
ylabel('# of TCPSinkApp' ,'FontSize',13)
% ylim([0 max(sortRTOsOUT)+1])
  xlim([-0.3 numServers+0.01*numServers])
 ax = gca;
  ax.XAxis.Exponent = 0;
grid
 
subplot(212)
stem(nodesRes(numlongflowsRunningServers+1:end),numSessionRes(numlongflowsRunningServers+1:end)) 

if numlongflowsRunningServers~=0
hold on
stem(nodesRes(1:numlongflowsRunningServers),numSessionRes(1:numlongflowsRunningServers), 'r') 
end
 legend('ShortFlows  Nodes',' LongFlows Nodes')

set(gca,'fontsize',10)
% set(gca,'XTick',1:numServers)

xlabel('servers', 'FontSize',13)
ylabel('# of TCPSessionApp' ,'FontSize',13)
% ylim([0 max(sortFastRetsOUT)+2])
  xlim([-0.3 numServers+0.01*numServers])
 ax = gca;
  ax.XAxis.Exponent = 0;
grid
end
