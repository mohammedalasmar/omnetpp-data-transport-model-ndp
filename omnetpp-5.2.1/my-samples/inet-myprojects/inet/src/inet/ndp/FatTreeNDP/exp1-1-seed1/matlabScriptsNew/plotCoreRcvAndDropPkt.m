
function plotCoreRcvAndDropPkt
%%

conf=dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
numCores= (k/2)^2;
n=0;
for i=1:numCores
    for j=1:k
      c=dlmread(fullfile('..','MatCoreRouterRcvdPkt.csv'));
      n=n+1;
      numRecPkt(i ,j) = c(n);
    end 
end


n=0;
for i=1:numCores
    for j=1:k
      c=dlmread(fullfile('..','MatCoreRouterDropPkt.csv'));
      n=n+1;
      numDropPkt(i ,j) = c(n);
    end 
end

figure
movegui('northeast')

subplot(311)
imTitle = ['Fat tree - #coreRouters= ', num2str(numCores)];
b1=bar(numRecPkt);
title(imTitle );
set(gca,'fontsize',13)
set(gca,'XTick',1:numCores)
xlabel('Core Routers', 'FontSize',13)
ylabel(' #Received Packets' ,'FontSize',13)
grid
 ax = gca;
subplot(312)
b2=bar(numDropPkt);
set(gca,'fontsize',13)
set(gca,'XTick',1:numCores)
xlabel('Core Routers', 'FontSize',13)
ylabel('#Dropped Packets' ,'FontSize',13)
grid
 ax = gca;
 
subplot(313)
 errorRate= (numDropPkt./numRecPkt);
b3=bar(errorRate);
set(gca,'fontsize',13)
set(gca,'XTick',1:numCores)
xlabel('Core Routers', 'FontSize',13)
ylabel('Packets Drop Rate' ,'FontSize',13)
grid
 ax = gca;
%  ax.YAxis.Exponent = 6;
%  ax.XAxis.Exponent = 0;

end

