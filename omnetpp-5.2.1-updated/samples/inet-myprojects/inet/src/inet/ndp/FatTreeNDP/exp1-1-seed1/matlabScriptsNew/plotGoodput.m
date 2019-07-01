%%% @author Mohammed Alasmar, 2019 
%%% email: mohammedzsalasmar@gmail.com
%%
function plotGoodput
 
conf = dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
% numShortFlows=conf(2); 
percentLongFlowNodes = conf(4);
numServers = (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 

kBytes = conf(3)*1500/1000;


%%
flowSizeVal = num2str(kBytes);

shortFlowsGoodput = dlmread(fullfile('..','MatInstThroughput.csv'));
shortFlowsGoodput = sort(shortFlowsGoodput);
shortFlows = shortFlowsGoodput(1:end-numlongflowsRunningServers);
%  movegui('center');  

scale = 10^9; % 1Gbps
figure, plot(shortFlows/scale, '-r', 'LineWidth',5) 
grid on
legendInfo{1} =  [flowSizeVal, 'KB'];
legend(legendInfo)
legend( legendInfo ,'FontSize',30)

imTitle = ['Fat tree - #servers= ', num2str(numServers)];
% title(imTitle );

xlabel('Rank of trasnport flow')
ylabel('Goodput (Gbps)')
 box on;
ax = gca;
ax.YAxis.Exponent = 0;
ax.XAxis.Exponent = 0;
ylim([0 1])
xlim([1 length(shortFlows)])

set(gca,'fontsize',30);
set(gca,'FontName','Times');
% savefig('src.fig');
% h1 = openfig('src.fig');
% set(h1,'Units','Inches');
% pos = get(h1,'Position');
% set(h1,'PaperPositionMode','Auto','PaperUnits','Inches','PaperSize',[pos(3), pos(4)]);
% saveas(h1,'src.pdf');
 
end

