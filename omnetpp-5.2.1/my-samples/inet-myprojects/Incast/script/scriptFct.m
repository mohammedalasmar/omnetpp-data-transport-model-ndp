clc,clear,close all
c=dlmread('nnn.csv');

senders=c(:,1);
throughput=c(:,2);
 
 
%  v=[4 2 7 4 12 9];
for k1 = 1:length(senders)
    [sv(k1),ix] = min(senders)  ; 
%     pause
    senders(ix) = inf;
    res(k1)=throughput(ix);
end


NumSenders=sort(c(:,1));
throughput=res';
 plot(NumSenders,throughput,'--*')
ax = gca;
% ax.YAxis.Exponent = 1;
grid on, xlabel('Senders'), ylabel('s')
saveas(gcf , 'test.png');
 
pause
quit