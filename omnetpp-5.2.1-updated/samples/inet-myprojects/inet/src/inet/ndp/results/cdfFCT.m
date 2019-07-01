function cdfFCT

c=dlmread('fct.csv');

senders=c(:,1);
fct=c(:,2) ;

fct(find(fct<0))=0;

% plot(sort(c(1:end)), '+')
figure
movegui('west');

h= cdfplot(fct); grid
set(h,'linewidth',3);

set(gca,'fontsize',13)
% xlim([0 numShortFlows+0.01*numShortFlows])
ylim([0 1.2])
% xlabel('flow rank', 'FontSize',18)
% ylabel('FCT (sec)' ,'FontSize',18)
ylabel('CDF', 'FontSize',13)
xlabel('FCT (sec)' ,'FontSize',13)
title('FCT CDF')
grid
ax = gca;
ax.YAxis.Exponent = 0;
ax.XAxis.Exponent = 0;
% pause
% quit
end


