
function plotServersRcvAndDropPkt
%%
conf=dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
% numShortFlows=conf(2); 

numServers= (k^3)/4;
conf=dlmread(fullfile('..','MatConfig.csv'));
percentLongFlowNodes=conf(4); 
kBytes=conf(3)/1000; 


numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 

%% 
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 
 
c=dlmread(fullfile('..','MatServersRcvdPkt.csv'));
% r=sort(c);
r=c;
% shortFlowsRcvdPkt= r(1:end-numlongflowsRunningServers);
shortFlowsRcvdPkt= r;

c2=dlmread( fullfile('..','MatServersDropPkt.csv'));
% r2=sort(c2);
r2=c2;
% shortFlowsDropPkt= r2(1:end-numlongflowsRunningServers);
shortFlowsDropPkt=r2;

serversRcvdBytes=dlmread( fullfile('..','MatServersRcvdPktBytes.csv'));
serversDropBytes=dlmread( fullfile('..','MatServersDropPktBytes.csv'));



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


figure
movegui('west')

subplot(411)
imTitle = [' #servers=', num2str(numServers) , ',  #servers run shortFlows=', num2str(numServers-numlongflowsRunningServers) , '#servers run longFLows=', num2str(numlongflowsRunningServers)];
% stem(shortFlowsRcvdPkt, '*') 
stem(nodesRes(numlongflowsRunningServers+1:end),shortFlowsRcvdPkt(nodesRes(numlongflowsRunningServers+1:end)+1)) 
if numlongflowsRunningServers~=0
hold on
stem(nodesRes(1:numlongflowsRunningServers),shortFlowsRcvdPkt(nodesRes(1:numlongflowsRunningServers)+1), 'r') 
end

legend('ShortFlows Nodes','LongFlows Nodes')
title(imTitle );
set(gca,'fontsize',9)
% set(gca,'XTick',1:numServers)
xlabel('servers', 'FontSize',13)
ylabel('#Received Packets' ,'FontSize',13)
grid on
ax = gca;
set(gca,'XTick',1:3:numServers)

 
subplot(412)
stem(nodesRes(numlongflowsRunningServers+1:end),serversRcvdBytes(nodesRes(numlongflowsRunningServers+1:end)+1)) 
if numlongflowsRunningServers~=0
 hold on
 stem(nodesRes(1:numlongflowsRunningServers),serversRcvdBytes(nodesRes(1:numlongflowsRunningServers)+1), 'r') 
end

set(gca,'fontsize',9)
% set(gca,'XTick',1:numServers)
xlabel('servers ', 'FontSize',13)
ylabel('Received Bytes' ,'FontSize',13)
grid on
ax = gca;
set(gca,'XTick',1:3:numServers)
legend('ShortFlows Nodes','LongFlows Nodes')

subplot(413)
% stem(shortFlowsDropPkt, '*') 
stem(nodesRes(numlongflowsRunningServers+1:end),shortFlowsDropPkt(nodesRes(numlongflowsRunningServers+1:end)+1),'x') 
if numlongflowsRunningServers~=0
hold on
stem(nodesRes(1:numlongflowsRunningServers),shortFlowsDropPkt(nodesRes(1:numlongflowsRunningServers)+1), 'xr') 
end

set(gca,'fontsize',9)
% set(gca,'XTick',1:numServers)
xlabel('servers ', 'FontSize',13)
ylabel('#Dropped Packets' ,'FontSize',13)
grid on
ax = gca;
set(gca,'XTick',1:3:numServers)
legend('ShortFlows Nodes','LongFlows Nodes')



 subplot(414)
% stem(shortFlowsDropPkt, '*') 
stem(nodesRes(numlongflowsRunningServers+1:end),serversDropBytes(nodesRes(numlongflowsRunningServers+1:end)+1),'x') 
if numlongflowsRunningServers~=0
hold on
stem(nodesRes(1:numlongflowsRunningServers),serversDropBytes(nodesRes(1:numlongflowsRunningServers)+1), 'xr') 
end

set(gca,'fontsize',9)
% set(gca,'XTick',1:numServers)
xlabel('servers ', 'FontSize',13)
ylabel('Dropped Bytes' ,'FontSize',13)
grid on
ax = gca;
set(gca,'XTick',1:3:numServers)
legend('ShortFlows Nodes','LongFlows Nodes')
 

 
 
 
% subplot(313)
%  errorRate= (shortFlowsDropPkt./shortFlowsRcvdPkt);
% stem(errorRate, 'r*') 
%  
% set(gca,'fontsize',13)  
% % set(gca,'XTick',1:numServers)
% xlabel('servers ', 'FontSize',13)
% ylabel('Bytes Drop Rate' ,'FontSize',13)
% grid
%  ax = gca;
% %  ax.YAxis.Exponent = 6;
% %  ax.XAxis.Exponent = 0;

end

