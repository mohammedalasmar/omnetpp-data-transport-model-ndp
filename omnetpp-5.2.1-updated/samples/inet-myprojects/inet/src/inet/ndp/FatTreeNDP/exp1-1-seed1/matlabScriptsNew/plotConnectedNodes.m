%%% @author Mohammed Alasmar, 2019
%%% email: mohammedzsalasmar@gmail.com
%%
function plotConnectedNodes

conf = dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
percentLongFlowNodes = conf(4) ;
numShortFlows = conf(2);
 
TMtype = conf(6);
if TMtype==1
    TMTypeStr= ['permTM'];
elseif TMtype==0
    TMTypeStr= ['randTM'];
else
    TMTypeStr= ['undefined'];
end

numServers= (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes);

%%
longFlowNodes=0;
fid = fopen(fullfile('..','MatLongFlowsNodes.csv'));
textLine = fgets(fid);  
lineCounter = 1;
while ischar(textLine)
    textLine= strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ;
    for i=1:length(numbers)
        longFlowNodes(end+1)= numbers(i) ;
    end
    % Read the next line.
    textLine = fgets(fid);
    lineCounter = lineCounter + 1;
end
fclose(fid);

longFlowNodes=longFlowNodes(2:end);


SrcLong=longFlowNodes(1:2:end);
DestLong=longFlowNodes(2:2:end);


%%
if TMtype==1 %permTM
    shortFlowNodes=0;
    fid = fopen(fullfile('..','MatPermMapShortFlowsVector.csv'));
    textLine = fgets(fid); % Read first line.
    lineCounter = 1;
    while ischar(textLine)
        textLine= strrep( textLine,'"','');
        numbers = sscanf(textLine, '%f ')  ;
        for i=1:length(numbers)
            shortFlowNodes(end+1)= numbers(i) ;
        end
        % Read the next line.
        textLine = fgets(fid);
        lineCounter = lineCounter + 1;
    end
    fclose(fid);
    
    shortFlowNodes=shortFlowNodes(2:end);
    
    
    SrcShort=shortFlowNodes(1:2:end);
    DestShort=shortFlowNodes(2:2:end);
    
    srcDestRand=[SrcShort;DestShort]';
    
    srcDestRandUnique = unique(srcDestRand,'rows', 'stable');
    t = mat2cell(srcDestRandUnique,ones(1,size(srcDestRandUnique,1)),2);
    g = @(row)nnz(ismember(srcDestRand,row,'rows'));
    repetition = cellfun(g,t);
    
end

%%
if TMtype==0 %randTM
    shortFlowNodes=0;
    fid = fopen(fullfile('..','MatRandShortFlowsNodes.csv'));
    textLine = fgets(fid); % Read first line.
    lineCounter = 1;
    while ischar(textLine)
        textLine= strrep( textLine,'"','');
        numbers = sscanf(textLine, '%f ')  ;
        for i=1:length(numbers)
            shortFlowNodes(end+1)= numbers(i) ;
        end
        % Read the next line.
        textLine = fgets(fid);
        lineCounter = lineCounter + 1;
    end
    fclose(fid);
    
    shortFlowNodes=shortFlowNodes(2:end);
    
    
    SrcShort=shortFlowNodes(1:2:end);
    DestShort=shortFlowNodes(2:2:end);
    srcDestRand=[SrcShort;DestShort]';
    
    srcDestRandUnique = unique(srcDestRand,'rows', 'stable');
    t = mat2cell(srcDestRandUnique,ones(1,size(srcDestRandUnique,1)),2);
    g = @(row)nnz(ismember(srcDestRand,row,'rows'));
    repetition = cellfun(g,t);
    
end

%%
figure

% subplot(211)
imTitle1 = [TMTypeStr, ' #servers=', num2str(numServers) , ',  #servers run: *longFlows* =', num2str(numlongflowsRunningServers),' ,*shortFlows* =',num2str(numServers-numlongflowsRunningServers)  ];

s=scatter(SrcLong,DestLong, 'og');
s.LineWidth = 10;
s.MarkerEdgeColor = 'r';
 

strValues = strtrim(cellstr(num2str([SrcLong(:) DestLong(:)],'(%d,%d)')));
% text(SrcLong,DestLong,strValues,'VerticalAlignment','top');

% title(imTitle1);

% set(gca,'XTick',1:numServers)
xlabel('Source Server')
ylabel('Destination Server' )
xlim([-0.9 numServers+0.5])
ylim([-0.9 numServers+0.5])
set(gca,'XTick',1:1:numServers)
set(gca,'YTick',1:1:numServers)

ax = gca;
legend('LongFlows')
grid on
hold on
% subplot(212)
% imTitle2 = [' #servers=', num2str(numServers) , ',  #servers run shortFlows=', num2str(numServers-numlongflowsRunningServers) ];

%%
s2= scatter(SrcShort,DestShort,  'xb')
s2.LineWidth = 10;
 
% title(imTitle2 );

strValues = strtrim(cellstr(num2str([srcDestRandUnique(:,1) srcDestRandUnique(:,2)],'(%d,%d)')));
rep = strtrim(cellstr(num2str(repetition(:),' %d ')));

% text(srcDestRandUnique(:,1),srcDestRandUnique(:,2),strValues,'VerticalAlignment','top');
text(srcDestRandUnique(:,1),srcDestRandUnique(:,2),rep,'VerticalAlignment','bottom', 'FontSize', 14);

% set(gca,'XTick',1:numServers)
xlabel('Source Server')
ylabel('Destination Server')
xticks([0:5:numServers])
yticks([0:5:numServers])

%  ylim([1,60])
%  yticks([0:5:60])

grid on
ax = gca;

legendInfo{1} =  'LongFlows';
legendInfo{2} =  'ShortFlows';
legend( legendInfo ,'FontSize',22)

lgd = legend;
lgd.NumColumns = 2;
set(gca,'FontName','Times');
box on;

set(gca,'fontsize',28);
 
% savefig('src.fig');
% h1 =openfig('src.fig');
% set(h1,'Units','Inches');
% pos = get(h1,'Position');
% set(h1,'PaperPositionMode','Auto','PaperUnits','Inches','PaperSize',[pos(3), pos(4)]);
% saveas(h1,'src.pdf');


end