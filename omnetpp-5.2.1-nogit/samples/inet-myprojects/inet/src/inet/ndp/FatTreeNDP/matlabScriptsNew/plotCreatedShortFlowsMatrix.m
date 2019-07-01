function plotCreatedShortFlowsMatrix

 
% numShortFlows = 100;

conf=dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
percentLongFlowNodes=conf(4) ; 
kBytes=conf(3)/1000;
numShortFlows=conf(2);
% percentLongFlowNodes=0.33;
% kBytes= 70 ;
numServers= (k^3)/4;
numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); 

%%
srcNodes=0; 
fid = fopen(fullfile('..','MatMatrixSrc.csv'));
textLine = fgets(fid); % Read first line.
lineCounter = 1;
while ischar(textLine)
   textLine= strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ; 
    for i=1:length(numbers)
    srcNodes(end+1)= numbers(i) ;
    end
	% Read the next line.
    textLine = fgets(fid);
	lineCounter = lineCounter + 1;
end
fclose(fid);

srcNodesRes=srcNodes(2:end);

%%
destNodes=0; 
fid = fopen(fullfile('..','MatMatrixDest.csv'));
textLine = fgets(fid); % Read first line.
lineCounter = 1;
while ischar(textLine)
   textLine= strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ; 
    for i=1:length(numbers)
    destNodes(end+1)= numbers(i) ;
    end
	% Read the next line.
    textLine = fgets(fid);
	lineCounter = lineCounter + 1;
end
fclose(fid);

destNodesRes=destNodes(2:end);

%%


srcDest=[srcNodesRes ;destNodesRes]';
figure 
hist3(srcDest,'FaceAlpha',.75, 'Nbins', [numServers,numServers]);
surfHandle = get(gca, 'child');
set(gcf,'renderer','opengl');
set(surfHandle,'FaceColor','interp', 'CdataMode', 'auto');
set(gca,'fontsize',12)
% set(gca,'XTick',1:1:numServers)
% set(gca,'YTick',1:1:numServers)


hold on

n= hist3(srcDest,'FaceAlpha',.65, 'Nbins', [numServers,numServers]);
n1 = n';
n1(size(n,1) + 1, size(n,2) + 1) = 0;

xb = linspace(min(srcDest(:,1)),max(srcDest(:,1)),size(n,1)+1);
yb = linspace(min(srcDest(:,2)),max(srcDest(:,2)),size(n,1)+1);
h = pcolor(xb,yb,n1);
  h.ZData = ones(size(n1)) * -max(max(n))*1.5;
% h.ZData = ones(size(n1)) * -12;

colorbar
%   colormap(hot) % heat map
grid on
view(3) 

imTitle = ['Traffic Matrix - Flows Bivariate histogram (#servers run shortFlows=', num2str(numServers-numlongflowsRunningServers), ', #shortFlows=', num2str(numShortFlows),')'];

title(imTitle);
xlabel('source nodes'); ylabel('destination nodes'); zlabel('#completed shortFlows');
% Get handle of surface plotted to change color settings
surfHandle = get(gca, 'child');
% Set the color to change with bar value
set(gcf,'renderer','opengl');
set(gca,'fontsize',12)
set(surfHandle,'FaceColor','interp', 'CdataMode', 'auto');
%    set(gca,'XTick',1:1:numServers)
%     set(gca,'YTick',1:1:numServers)

end
