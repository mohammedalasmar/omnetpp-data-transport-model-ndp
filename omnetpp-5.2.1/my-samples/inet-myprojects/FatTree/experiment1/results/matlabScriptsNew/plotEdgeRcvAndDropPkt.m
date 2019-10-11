
function plotEdgeRcvAndDropPkt(k)
%%
 
totEdge=k*k/2;

n=0;
for i=1:totEdge
    for j=1:k
      c=dlmread(  fullfile('..','MatEdgeRouterRcvdPkt.csv'));
      n=n+1;
      numRecPkt(i ,j) = c(n);
    end 
end


n=0;
for i=1:totEdge
    for j=1:k
      c=dlmread(fullfile('..','MatEdgeRouterDropPkt.csv'));
      n=n+1;
      numDropPkt(i ,j) = c(n);
    end 
end

figure
movegui('southeast')


subplot(311)
imTitle = ['Fat tree - #edgeRouters= ', num2str(totEdge)];
b1=bar(numRecPkt);
 
title(imTitle );
set(gca,'fontsize',8)
set(gca,'XTick',1:totEdge)
xlabel('Edge Routers', 'FontSize',13)
ylabel('# Received Packets' ,'FontSize',13)
grid
 ax = gca;
subplot(312)
b2=bar(numDropPkt);
set(gca,'fontsize',8)
set(gca,'XTick',1:totEdge)
xlabel('Edge Routers', 'FontSize',13)
ylabel('# Dropped Packets' ,'FontSize',13)
grid
 ax = gca;
 
subplot(313)
 errorRate= (numDropPkt./numRecPkt);
b3=bar(errorRate);
set(gca,'fontsize',8)
set(gca,'XTick',1:totEdge)
xlabel('Edge Routers', 'FontSize',13)
ylabel('Pakcets Drop Rate' ,'FontSize',13)
grid
 ax = gca;
%  ax.YAxis.Exponent = 6;
%  ax.XAxis.Exponent = 0;

end

