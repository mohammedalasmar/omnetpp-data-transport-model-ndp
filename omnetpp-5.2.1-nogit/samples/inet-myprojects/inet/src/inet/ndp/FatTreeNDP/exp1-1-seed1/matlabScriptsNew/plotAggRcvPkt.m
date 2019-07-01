%%% @author Mohammed Alasmar, 2019
%%% email: mohammedzsalasmar@gmail.com
%%
function plotAggRcvPkt
%%
conf = dlmread(fullfile('..','MatConfig.csv'));
k = conf(16);
totAge = k*k/2;

n=0;
for i=1:totAge
    for j=1:k
      c=dlmread(fullfile('..','MatAggRouterRcvdPkt.csv'));
      n=n+1;
      numRecPkt(i ,j) = c(n);
    end 
end


% n=0;
% for i=1:totAge
%     for j=1:k
%       c=dlmread(fullfile('..','MatAggRouterDropPkt.csv'));
%       n=n+1;
%       numDropPkt(i ,j) = c(n);
%     end 
% end


 
% figure
% subplot(311)
imTitle = ['Fat tree -  #aggRouters= ', num2str(totAge)];
b1=bar(numRecPkt);
% title(imTitle );
 
set(gca,'XTick',1:totAge)
xlabel('Aggregation Switches')
ylabel('#Received Packets')
grid on 
box on;
ax = gca;
ax.YAxis.Exponent = 0;
ax.XAxis.Exponent = 0;
  
set(gca,'fontsize',24);
set(gca,'FontName','Times');
% savefig('src.fig');
% h1 = openfig('src.fig');
% set(h1,'Units','Inches');
% pos = get(h1,'Position');
% set(h1,'PaperPositionMode','Auto','PaperUnits','Inches','PaperSize',[pos(3), pos(4)]);
% saveas(h1,'src.pdf');

 
% subplot(312)
% b2=bar(numDropPkt);
% set(gca,'fontsize',8)
% set(gca,'XTick',1:totAge)
% xlabel('Agg. Routers', 'FontSize',13)
% ylabel('#Dropped Packets' ,'FontSize',13)
% grid on
% ax = gca;
 
% subplot(313)
%  errorRate= (numDropPkt./numRecPkt);
% b3=bar(errorRate);
% set(gca,'fontsize',8)
% set(gca,'XTick',1:totAge)
% xlabel('Agg. Routers', 'FontSize',13)
% ylabel('Packets Drop Rate' ,'FontSize',13)
% grid on 
%  ax = gca;
 

end

