
function plotNumTrimmedPkts
%%
conf=dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
numCores= (k/2)^2;
n=0;
for i=1:numCores
    for j=1:k
      c=dlmread(fullfile('..','MatNumTrimmedPktCore.csv'));
      n=n+1;
      trimmedCore(i ,j) = c(n);
    end 
end


totAge=k*k/2;
n=0;
for i=1:totAge
    for j=1:k
      c=dlmread(fullfile('..','MatNumTrimmedPktAgg.csv'));
      n=n+1;
      trimmedAgg(i ,j) = c(n);
    end 
end


totEdge=k*k/2;
n=0;
for i=1:totEdge
    for j=1:k
      c=dlmread(  fullfile('..','MatNumTrimmedPktEdge.csv'));
      n=n+1;
      trimmedEdge(i ,j) = c(n);
    end 
end




figure
movegui('southeast')


subplot(311)
% imTitle = ['Fat tree - #edgeRouters= ', num2str(totEdge)];
b1=bar(trimmedCore);
 
% title(imTitle );
set(gca,'fontsize',8)
set(gca,'XTick',1:numCores)
xlabel('Core Routers', 'FontSize',13)
ylabel('# Trimmed Packets' ,'FontSize',13)
grid
 ax = gca;
subplot(312)
b2=bar(trimmedAgg);
set(gca,'fontsize',8)
set(gca,'XTick',1:totAge)
xlabel('Aggregation Routers', 'FontSize',13)
ylabel('# Trimmed Packets' ,'FontSize',13)
grid
 ax = gca;
 
subplot(313)
b3=bar(trimmedEdge);
set(gca,'fontsize',8)
set(gca,'XTick',1:totEdge)
xlabel('Edge Routers', 'FontSize',13)
ylabel('Trimmed Packets' ,'FontSize',13)
grid
 ax = gca;
%  ax.YAxis.Exponent = 6;
%  ax.XAxis.Exponent = 0;

end

