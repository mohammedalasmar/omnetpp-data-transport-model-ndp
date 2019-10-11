function plotResults(K,numShortFlows , multicastOrMultisource)
 fatTreeDetails(K)
 saveas(gcf,'fatTreeDetails.png')

 plotFCT(K,numShortFlows)
 saveas(gcf,'plotFCT.png')

 plotThroughput(K,numShortFlows) 
 saveas(gcf,'plotThroughput.png')
  
  if (multicastOrMultisource == "multicast") 
      plotThroughputMulticast(K) 
  end
  
  if (multicastOrMultisource == "multisource") 
      plotThroughputMultisource(K) 
  end



%  plotNumFastRetsANDnumRTOs(K,numShortFlows)
%  saveas(gcf,'plotNumFastRetsANDnumRTOs.png')
% 
%   
%  plotCoreRcvAndDropPkt(K)
%  saveas(gcf,'plotCoreRcvAndDropPkt.png')
%   
%  plotAggRcvAndDropPkt(K)
%  saveas(gcf,'plotAggRcvAndDropPkt.png')
% 
%  plotEdgeRcvAndDropPkt(K)
%  saveas(gcf,'plotEdgeRcvAndDropPkt.png')
% 
%  plotServersRcvAndDropPkt(K)
%  saveas(gcf,'plotServersRcvAndDropPkt.png')
% 
%  plotFinalNumApplications(K)
%  saveas(gcf,'plotFinalNumApplications.png')
% 
%  plotCreatedShortFlowsMatrix(K)
%  saveas(gcf,'plotCreatedShortFlowsMatrix.png')
% 
%  plotConnectedNodes(K)
%  saveas(gcf,'plotConnectedNodes.png')

 
%  disp( 'press any key to quit Matlab ..')
%  pause
%  quit
end