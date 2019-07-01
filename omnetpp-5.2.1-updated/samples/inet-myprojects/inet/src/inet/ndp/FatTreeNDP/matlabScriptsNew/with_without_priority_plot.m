clc,clear ,close all
conf=dlmread(fullfile('..','MatConfig.csv'));
k = conf(16); 
numShortFlows=conf(2); 
percentLongFlowNodes=conf(4); 
kBytes=conf(3)*1500/1000;

%%
numServers= (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 
 

nLines = length(kBytes);

for i=1:length(kBytes)
    a= num2str(kBytes(i));
    b=num2str(numServers);
    c=dlmread(fullfile('..','MatInstThroughput.csv'));
    r=sort(c);
    shortFlows= r(1:end-numlongflowsRunningServers);
     figure,
     plot(shortFlows, 'r') 
     hold on
end


for i=1:length(kBytes)
    a= num2str(kBytes(i));
    b=num2str(numServers);
    c=dlmread(fullfile('..','MatInstThroughput.csv'));
    r=sort(c);
    shortFlows= r(1:end-numlongflowsRunningServers);
    hold on,
    plot(shortFlows, 'b') 
     hold on
end

imTitle = ['Fat tree - #servers= ', num2str(numServers)];
set(gca,'fontsize',13)
title(imTitle );
xlabel('flow rank', 'FontSize',13)
ylabel('Goodput' ,'FontSize',13)
grid
 ax = gca;
 ax.YAxis.Exponent = 9;
 ax.XAxis.Exponent = 0;
ylim([0 1*10^9])

 





figure,
%% FCT  with
fct=dlmread(fullfile('..','aaMatFct.csv'));
fct(find(fct<0)) = 0;
BYT=dlmread(fullfile('..','aaMatFlowSizes.csv'));
    

BytVsFct = [BYT , fct];
BytVsFct(find(BytVsFct(:,1)==0),:) = [];
BytVsFctSorted = sortrows(BytVsFct);
BytVsFctSorted(find(BytVsFctSorted(:,2)==0),:) = []

q0_10k = BytVsFctSorted((BytVsFctSorted(:,1) > 0) & (BytVsFctSorted(:,1) <= 10000),2) ;
q10k_100k = BytVsFctSorted((BytVsFctSorted(:,1) > 10000) & (BytVsFctSorted(:,1) <= 100000),2) ;
q100k_1M = BytVsFctSorted((BytVsFctSorted(:,1) > 100000) & (BytVsFctSorted(:,1) <= 10^6),2) ;
q1M_10M = BytVsFctSorted((BytVsFctSorted(:,1) > 10^6) & (BytVsFctSorted(:,1) <= 10*10^6),2) ;
all_fct = [q0_10k;q10k_100k;q100k_1M;q1M_10M];
q0_100k =[q0_10k;q10k_100k];


h = cdfplot(all_fct); 
grid  , set(h,'linewidth',2); set(h,'Color','r');
hold on
BytVsFctSortedW = BytVsFctSorted
%% FCT  withouttttttttttttt
fct=dlmread(fullfile('..','aaMatFct.csv'));
fct(find(fct<0)) = 0;
BYT=dlmread(fullfile('..','aaMatFlowSizes.csv'));
    
BytVsFct = [BYT , fct];
BytVsFct(find(BytVsFct(:,1)==0),:) = [];
BytVsFctSorted = sortrows(BytVsFct);

BytVsFctSorted(find(BytVsFctSorted(:,2)==0),:) = []
q0_10k = BytVsFctSorted((BytVsFctSorted(:,1) > 0) & (BytVsFctSorted(:,1) <= 10000),2) ;
q10k_100k = BytVsFctSorted((BytVsFctSorted(:,1) > 10000) & (BytVsFctSorted(:,1) <= 100000),2) ;
q100k_1M = BytVsFctSorted((BytVsFctSorted(:,1) > 100000) & (BytVsFctSorted(:,1) <= 10^6),2) ;
q1M_10M = BytVsFctSorted((BytVsFctSorted(:,1) > 10^6) & (BytVsFctSorted(:,1) <= 10*10^6),2) ;
all_fct = [q0_10k;q10k_100k;q100k_1M;q1M_10M];

q0_100k =[q0_10k;q10k_100k]
h = cdfplot(all_fct); 
grid  , set(h,'linewidth',2); set(h,'Color','b');

 

 



imTitle = ['Fat tree- Permutation Matrix, #servers= ', num2str(numServers)];
% legend(legendInfo)
set(gca,'fontsize',13)
title(imTitle);
%  xlim([0 0.0004])
ylim([0 1.2])
% xlabel('flow rank', 'FontSize',18)
% ylabel('FCT (sec)' ,'FontSize',18)
ylabel('CDF', 'FontSize',13)
xlabel('FCT (sec)' ,'FontSize',13)
grid
 ax = gca;
 ax.YAxis.Exponent = 0;
 ax.XAxis.Exponent = 0;
% pause
% quit
 




