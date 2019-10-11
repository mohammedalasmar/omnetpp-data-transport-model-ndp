
function plotThroughputMultisource(K)

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
kBytes=conf(3)  ;
replicas = conf(8);
sessions = conf(10);
numSinks = replicas*sessions;

%%
numServers= (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 

nLines = length(kBytes);


a= num2str(kBytes/1000);
b=num2str(numServers);

throughput=dlmread(fullfile('..','MatInstThroughput.csv'));

multicastgroup=dlmread(fullfile('..','MatMultisourcegroups.csv'));

tempp = [multicastgroup,throughput];
[val idx]=sort(tempp(:,1));
grpVsThr = [val tempp(idx,2)];
grpVsThr= grpVsThr(1:numSinks,:);
throughputCol = grpVsThr(:,2);
n =  replicas; % replicas
 
avgThroughput= arrayfun(@(i) mean(throughputCol(i:i+n-1)),1:n:length(throughputCol)-n+1)';
 
avgThroughputSorted = sort(avgThroughput);
% shortFlows= r(1:end-numlongflowsRunningServers);
 
figure
movegui('center');
plot(avgThroughputSorted/10^9, 'r','LineWidt',2)
legendInfo =  [ a, ' KB'];
 


imTitle = ['Fat tree - #servers= ', num2str(numServers)];
legend(legendInfo)
set(gca,'fontsize',15)
% title(imTitle );
xlabel('Flow rank', 'FontSize',15)
ylabel('Goodput (Gbps)' ,'FontSize',15)
grid
%  ax = gca;
%  ax.YAxis.Exponent = 1;
%  ax.XAxis.Exponent = 0;
ylim([0 1])
xlim([1 length(avgThroughputSorted)])


% set(gca,'fontsize',25)
% set(gca,'FontName','Times')
%  savefig('src.fig')
%   h1 =openfig('src.fig')
% set(h1,'Units','Inches');
% pos = get(h1,'Position');
% set(h1,'PaperPositionMode','Auto','PaperUnits','Inches','PaperSize',[pos(3), pos(4)])
% saveas(h1,'goodput.pdf')

end

