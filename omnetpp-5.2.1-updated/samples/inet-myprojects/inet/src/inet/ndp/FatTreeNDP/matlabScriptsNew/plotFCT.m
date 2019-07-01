 
function plotFCT

% path(path,genpath('/Volumes/LocalDataHD/m/ma/ma777/Desktop/distinguishable_colors'));
% lineStyles = {'-', '--', ':', '-.'};
% myColors = distinguishable_colors(nLines);
% nLines = length(kBytes);

%%

conf=dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
kBytes=conf(3)*1500/1000; 
numShortFlows=conf(2); 

% kBytes= 70 ;

% numShortFlows =100;

numServers= (k^3)/4;
 


%%
for i=1:length(kBytes)
    a= num2str(kBytes(i));
    b=num2str(numServers);
    c=dlmread(fullfile('..','MatFct.csv'));

%     plot(sort(c(1:end)),'linestyle', lineStyles{rem(i-1,numel(lineStyles))+1},...
%         'color', myColors(i,:),...
%         'linewidth',3);
     c(find(c<0))=0;
 
    % plot(sort(c(1:end)), '+') 
    figure
    movegui('north');

     h= cdfplot(c); grid
    set(h,'linewidth',3);

     legendInfo{i} =  [ a, 'kB'];
    hold on
end

imTitle = ['Fat tree- Permutation Matrix, #servers= ', num2str(numServers)];
legend(legendInfo)
set(gca,'fontsize',13)
title(imTitle );
% xlim([0 numShortFlows+0.01*numShortFlows])
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
end


