
function plotNumRcvdHeaderForEachShortFlow

%%
conf=dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);

percentLongFlowNodes=conf(4) ; 
kBytes=conf(3)/1000;
numShortFlows = conf(2) ; 
% percentLongFlowNodes=0.33;
% kBytes= 70 ;
numServers= (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 

%%


numHeaders=0; 
fid = fopen(fullfile('..','MatNumRcvHeader.csv'));
textLine = fgets(fid); % Read first line.
lineCounter = 1;
while ischar(textLine)
   textLine= strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ; 
    for i=1:length(numbers)
    numHeaders(end+1)= numbers(i) ;
    end
	% Read the next line.
    textLine = fgets(fid);
	lineCounter = lineCounter + 1;
end
fclose(fid);
numHeaders=numHeaders(2:end);

numHeadersSort = sort(numHeaders);
numHeadersSortShortFlows=numHeadersSort(1:numShortFlows);
 
%%
figure
movegui('southwest');

stem(numHeadersSortShortFlows, 'r') 

set(gca,'fontsize',10)
% set(gca,'XTick',1:numServers)

xlabel('Rank of short flow', 'FontSize',13)
ylabel('# rcvd header' ,'FontSize',13)
grid on
 
 ax = gca;
  ax.XAxis.Exponent = 0;

end
