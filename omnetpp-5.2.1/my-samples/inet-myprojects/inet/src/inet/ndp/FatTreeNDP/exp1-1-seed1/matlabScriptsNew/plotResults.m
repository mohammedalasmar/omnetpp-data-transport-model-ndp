function plotResults 

 

 fatTreeDetails
 saveas(gcf,'fatTreeDetails.png')

 plotFCT
 saveas(gcf,'plotFCT.png')

 plotThroughput
 saveas(gcf,'plotThroughput.png')

  
 plotCoreRcvAndDropPkt
 saveas(gcf,'plotCoreRcvAndDropPkt.png')
  
 plotAggRcvAndDropPkt
 saveas(gcf,'plotAggRcvAndDropPkt.png')

 plotEdgeRcvAndDropPkt
 saveas(gcf,'plotEdgeRcvAndDropPkt.png')

%  plotServersRcvAndDropPkt
%  saveas(gcf,'plotServersRcvAndDropPkt.png')

plotFinalNumApplications
saveas(gcf,'plotFinalNumApplications.png')

plotCreatedShortFlowsMatrix
saveas(gcf,'plotCreatedShortFlowsMatrix.png')

plotConnectedNodes
saveas(gcf,'plotConnectedNodes.png')

plotNumTrimmedPkts
saveas(gcf,'plotNumTrimmedPkts.png')

plotNumRcvdHeaderForEachShortFlow
 saveas(gcf,'plotNumRcvdHeaderForEachShortFlow.png')

%  disp( 'press any key to quit Matlab ..')
%  pause
%  quit
end
