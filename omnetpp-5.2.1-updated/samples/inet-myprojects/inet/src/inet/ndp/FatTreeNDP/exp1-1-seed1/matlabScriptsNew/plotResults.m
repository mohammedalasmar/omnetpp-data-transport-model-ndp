%%% @author Mohammed Alasmar, 2019
%%% email: mohammedzsalasmar@gmail.com
%%
function plotResults

close all,
simulationSummary, movegui('north');
% saveas(gcf,'simulation_summary.png')

plotGoodput, movegui('south');
% saveas(gcf,'plotGoodput.png')

plotFCT, movegui('east');
% saveas(gcf,'plotFCT.png')

figure, subplot(311), plotCoreRcvPkt,
% saveas(gcf,'plotCoreRcvPkt.png')

subplot(312), plotAggRcvPkt,
% saveas(gcf,'plotAggRcvPkt.png')

subplot(313),plotEdgeRcvPkt
% saveas(gcf,'plotEdgeRcvPkt.png')
movegui('west');

plotFinalNumApplications, movegui('northeast');
% saveas(gcf,'plotFinalNumApplications1.png')

plotCreatedShortFlowsMatrix, movegui('northwest');
% saveas(gcf,'plotCreatedShortFlowsMatrix.png')

plotConnectedNodes, movegui('southeast');
% saveas(gcf,'plotConnectedNodes.png')

% plotNumTrimmedPkts
% saveas(gcf,'plotNumTrimmedPkts.png')

plotNumRcvdHeaderForEachShortFlow, movegui('southwest');
% saveas(gcf,'plotNumRcvdHeaderForEachShortFlow.png')

%  disp( 'press any key to quit Matlab ..')
%  pause
%  quit
end
