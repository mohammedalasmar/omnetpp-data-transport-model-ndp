%%% @author Mohammed Alasmar, 2019
%%% email: mohammedzsalasmar@gmail.com
%%
function plotNumRcvdHeaderForEachShortFlow

%%
conf = dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
percentLongFlowNodes = conf(4) ;
numShortFlows = conf(2) ;
numServers = (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes);

%%

numHeaders = 0;
fid = fopen(fullfile('..','MatNumRcvHeader.csv'));
textLine = fgets(fid);
lineCounter = 1;
while ischar(textLine)
    textLine = strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ;
    for i = 1:length(numbers)
        numHeaders(end+1) = numbers(i) ;
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
figure, stem(numHeadersSortShortFlows,  '-rx', 'MarkerSize', 6, 'LineWidth', 3 )

set(gca,'fontsize',32)
set(gca,'FontName','Times');
% set(gca,'XTick',1:numServers)

xlabel('Rank of short flow')
ylabel('#received headers')
grid on
ylim([0 max(numHeadersSortShortFlows)+5])
ax = gca;
ax.XAxis.Exponent = 0;

end
