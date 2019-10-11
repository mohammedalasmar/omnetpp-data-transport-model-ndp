% clc,clear,close all
% path(path,genpath('/Volumes/LocalDataHD/m/ma/ma777/Desktop/distinguishable_colors'));
% lineStyles = {'-', '--', ':', '-.'};
% myColors = distinguishable_colors(nLines);

function fastRetsRTOs 




 %%  RTOs
numRTOs=0; 
fid = fopen('RTOs.csv');
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


%% Fast Retransmissions 
 numFastRets=0;
 fid = fopen('fastRet.csv');
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

TROsVsFASTRets=[numRTOsRes;numFastRetsRes];
TROsVsFASTRets( :, all(~TROsVsFASTRets,1) ) = [] ;


%%

% val1 = sum(numRTOs111 == 1);
% val2 = sum(numRTOs111 == 2);
% sort(numRTOs111)
sortRTOs= sort(TROsVsFASTRets(1,:));
sortFastRets= sort(TROsVsFASTRets(2,:));

 
figure
movegui('south');

subplot(212)
plot(sortRTOs, '+') 
set(gca,'fontsize',13)
xlabel('client rank', 'FontSize',13)
ylabel('Timeouts(#)' ,'FontSize',13)
ylim([0 max(sortRTOs)+1])
% xlim([0 numShortFlows+0.01*numShortFlows])
 ax = gca;
  ax.XAxis.Exponent = 0;
grid
 
subplot(211)
plot(sortFastRets, '+') 
set(gca,'fontsize',13)
xlabel('client rank', 'FontSize',13)
ylabel('Fast Retransmissions(#)' ,'FontSize',13)
ylim([0 max(sortFastRets)+2])
% xlim([0 numShortFlows+0.01*numShortFlows])
 ax = gca;
  ax.XAxis.Exponent = 0;
grid
title(' dupthresh of 3');

end
