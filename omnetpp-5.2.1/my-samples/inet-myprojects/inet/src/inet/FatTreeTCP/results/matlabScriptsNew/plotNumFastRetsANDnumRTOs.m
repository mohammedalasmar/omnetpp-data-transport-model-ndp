% clc,clear,close all
% path(path,genpath('/Volumes/LocalDataHD/m/ma/ma777/Desktop/distinguishable_colors'));
% lineStyles = {'-', '--', ':', '-.'};
% myColors = distinguishable_colors(nLines);

function plotNumFastRetsANDnumRTOs(K,numShortFlows)


%%
k=K;


conf=dlmread(fullfile('..','MatConfig.csv'));
percentLongFlowNodes=conf(4); 
kBytes=conf(3)/1000; 

% numShortFlows = 100;
% percentLongFlowNodes=0.33;
% kBytes= 70 ;

%%
numServers= (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 


 nLines = length(kBytes);


 %%  RTOs
numRTOs=0; 
fid = fopen(fullfile('..','MatNumRTOs.csv'));
textLine = fgets(fid); % Read first line.
lineCounter = 1;
while ischar(textLine)
   textLine= strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ; 
    for i=1:length(numbers)
    numRTOs(end+1)= numbers(i) ;
    end
	% Read the next line.
    textLine = fgets(fid);
	lineCounter = lineCounter + 1;
end
fclose(fid);

numRTOsRes=numRTOs(2:end);

% numRTOsRes=numRTOsRes(1:2*numShortFlows); %%%%% to check add Nov 2018

%% Fast Retransmissions 
 numFastRets=0;
 fid = fopen(fullfile('..','MatNumFastRets.csv'));
textLine = fgets(fid); % Read first line.
lineCounter = 1;
while ischar(textLine)
   textLine= strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ; 
    for i=1:length(numbers)
    numFastRets(end+1)= numbers(i) ;
    end
	% Read the next line.
    textLine = fgets(fid);
	lineCounter = lineCounter + 1;
end
fclose(fid);

numFastRetsRes=numFastRets(2:end);
numRTOsRes = numRTOsRes(1:length(numFastRetsRes))

TROsVsFASTRets=[numRTOsRes;numFastRetsRes];
TROsVsFASTRets( :, all(~TROsVsFASTRets,1) ) = [] ;


%%

% val1 = sum(numRTOs111 == 1);
% val2 = sum(numRTOs111 == 2);
% sort(numRTOs111)
sortRTOs= sort(TROsVsFASTRets(1,:));
sortFastRets= sort(TROsVsFASTRets(2,:));


sortRTOs=sortRTOs(1,1:(end-numlongflowsRunningServers));
sortFastRets=sortFastRets(1,1:(end-numlongflowsRunningServers));


sortRTOsOUT = [zeros(1, numShortFlows-length(sortRTOs)) , sortRTOs ];
sortFastRetsOUT = [zeros(1, numShortFlows-length(sortRTOs)) , sortFastRets ];

figure
movegui('south');

subplot(212)
plot(sortRTOsOUT, '+') 
set(gca,'fontsize',13)
xlabel('flow rank', 'FontSize',13)
ylabel('Timeouts(#)' ,'FontSize',13)
ylim([0 max(sortRTOsOUT)+1])
xlim([0 numShortFlows+0.01*numShortFlows])
 ax = gca;
  ax.XAxis.Exponent = 0;
grid
 
subplot(211)
plot(sortFastRetsOUT, '+') 
set(gca,'fontsize',13)
xlabel('flow rank', 'FontSize',13)
ylabel('Fast Retransmissions(#)' ,'FontSize',13)
ylim([0 max(sortFastRetsOUT)+2])
xlim([0 numShortFlows+0.01*numShortFlows])
 ax = gca;
  ax.XAxis.Exponent = 0;
grid
title(' dupthresh of 3');

end
