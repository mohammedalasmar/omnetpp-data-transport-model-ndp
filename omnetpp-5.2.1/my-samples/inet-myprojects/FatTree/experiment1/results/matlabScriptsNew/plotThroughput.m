
function plotThroughput(K, numShortFlows)

% path(path,genpath('/Volumes/LocalDataHD/m/ma/ma777/Desktop/distinguishable_colors'));
% lineStyles = {'-', '--', ':', '-.'};
% myColors = distinguishable_colors(nLines);
%%
k=K;
% numShortFlows =100;
% percentLongFlowNodes=0.33;
% kBytes= 70 ;
conf=dlmread(fullfile('..','MatConfig.csv'));
percentLongFlowNodes=conf(4); 
kBytes=conf(3)/1000;

%%
numServers= (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 

nLines = length(kBytes);

for i=1:length(kBytes)
    a= num2str(kBytes(i));
    b=num2str(numServers);
    c=dlmread(fullfile('..','MatInstThroughput.csv'));
    r=sort(c);
    shortFlows= r(1:end-numlongflowsRunningServers);
%     plot(shortFlows,'linestyle', lineStyles{rem(i-1,numel(lineStyles))+1},...
%         'coalor', myColors(i,:),...
%         'linewidth',3);
    figure
     movegui('center');
     plot(shortFlows, '--+') 
     legendInfo{i} =  [ a, 'kB'];
    hold on
end

imTitle = ['Fat tree - #servers= ', num2str(numServers)];
legend(legendInfo)
set(gca,'fontsize',13)
title(imTitle );
xlabel('flow rank', 'FontSize',13)
ylabel('Goodput' ,'FontSize',13)
grid
 ax = gca;
 ax.YAxis.Exponent = 9;
 ax.XAxis.Exponent = 0;

end

