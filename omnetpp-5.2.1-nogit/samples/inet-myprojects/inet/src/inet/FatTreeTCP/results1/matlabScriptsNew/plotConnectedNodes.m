function plotConnectedNodes(k)


conf=dlmread(fullfile('..','MatConfig.csv'));
percentLongFlowNodes=conf(4) ; 
kBytes=conf(3)/1000;
numShortFlows=conf(2);

TMtype=conf(6);
if TMtype==0
    TMTypeStr= ['permTM'];
elseif TMtype==1
    TMTypeStr= ['randTM'];
else 
    TMTypeStr= ['undefined'];
end
% kBytes= 70 ;
numServers= (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 

%%
longFlowNodes=0; 
fid = fopen(fullfile('..','MatLongFlowsNodes.csv'));
textLine = fgets(fid); % Read first line.
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
if TMtype==0  %permTM
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
if TMtype==1 %randTM
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

s=scatter(SrcLong,DestLong, 'or' );
s.LineWidth = 0.9;
s.MarkerEdgeColor = 'r';


strValues = strtrim(cellstr(num2str([SrcLong(:) DestLong(:)],'(%d,%d)')));
% text(SrcLong,DestLong,strValues,'VerticalAlignment','top');

title(imTitle1);
set(gca,'fontsize',12)
% set(gca,'XTick',1:numServers)
xlabel('Source Server', 'FontSize',13)
ylabel('Destination Server' ,'FontSize',13)
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


scatter(SrcShort,DestShort,  '*b')
% title(imTitle2 );

strValues = strtrim(cellstr(num2str([srcDestRandUnique(:,1) srcDestRandUnique(:,2)],'(%d,%d)')));
rep = strtrim(cellstr(num2str(repetition(:),' %d ')));

% text(srcDestRandUnique(:,1),srcDestRandUnique(:,2),strValues,'VerticalAlignment','top');
text(srcDestRandUnique(:,1),srcDestRandUnique(:,2),rep,'VerticalAlignment','bottom');

set(gca,'fontsize',10)
% set(gca,'XTick',1:numServers)
xlabel('Source Server', 'FontSize',13)
ylabel('Destination Server' ,'FontSize',13)
grid on
ax = gca;
legend('LongFlows','ShortFlows')



end