%%% @author Mohammed Alasmar, 2019
%%% email: mohammedzsalasmar@gmail.com
%%
function plotFCT

conf = dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
kBytes = conf(3)*1500/1000;
% numShortFlows=conf(2);
numServers = (k^3)/4;

flowSizeVal = num2str(kBytes);

shortFlowsFCT = dlmread(fullfile('..','MatFct.csv'));
shortFlowsFCT(find(shortFlowsFCT<0))=0;

figure, h= cdfplot(shortFlowsFCT*1000); grid on
set(h,'linewidth',5);
legendInfo{1} =  [flowSizeVal, 'KB'];
legend(legendInfo)


imTitle = ['Fat tree- Permutation Matrix, #servers= ', num2str(numServers)];
title('');
ylim([0 1.1])

ylabel('CDF')
xlabel('FCT (msec)')
box on; 
ax = gca;
ax.YAxis.Exponent = 0;
ax.XAxis.Exponent = 0;

set(gca,'fontsize',30);
set(gca,'FontName','Times');
% savefig('src.fig');
% h1 = openfig('src.fig');
% set(h1,'Units','Inches');
% pos = get(h1,'Position');
% set(h1,'PaperPositionMode','Auto','PaperUnits','Inches','PaperSize',[pos(3), pos(4)]);
% saveas(h1,'src.pdf');
end


