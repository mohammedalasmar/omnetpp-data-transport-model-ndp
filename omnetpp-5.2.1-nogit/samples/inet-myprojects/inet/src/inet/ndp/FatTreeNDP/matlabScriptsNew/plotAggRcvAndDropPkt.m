
function plotAggRcvAndDropPkt
%%
conf=dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
totAge=k*k/2;

n=0;
for i=1:totAge
    for j=1:k
      c=dlmread(fullfile('..','MatAggRouterRcvdPkt.csv'));
      n=n+1;
      numRecPkt(i ,j) = c(n);
    end 
end


n=0;
for i=1:totAge
    for j=1:k
      c=dlmread(fullfile('..','MatAggRouterDropPkt.csv'));
      n=n+1;
      numDropPkt(i ,j) = c(n);
    end 
end

figure
movegui('east')

subplot(311)
imTitle = ['Fat tree -  #aggRouters= ', num2str(totAge)];
b1=bar(numRecPkt);
 
title(imTitle );
set(gca,'fontsize',8)
set(gca,'XTick',1:totAge)
xlabel('Agg. Routers', 'FontSize',13)
ylabel('#Received Packets' ,'FontSize',13)
grid
 ax = gca;
subplot(312)
b2=bar(numDropPkt);
set(gca,'fontsize',8)
set(gca,'XTick',1:totAge)
xlabel('Agg. Routers', 'FontSize',13)
ylabel('#Dropped Packets' ,'FontSize',13)
grid
ax = gca;
 
subplot(313)
 errorRate= (numDropPkt./numRecPkt);
b3=bar(errorRate);
set(gca,'fontsize',8)
set(gca,'XTick',1:totAge)
xlabel('Agg. Routers', 'FontSize',13)
ylabel('Packets Drop Rate' ,'FontSize',13)
grid
 ax = gca;
%  ax.YAxis.Exponent = 6;
%  ax.XAxis.Exponent = 0;

end

