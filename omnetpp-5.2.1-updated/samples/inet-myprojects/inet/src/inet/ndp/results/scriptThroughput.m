function scriptThroughput 
c=dlmread('throughput.csv');

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
 figure
plot(NumSenders,throughput,'--*')
ax = gca;
  ax.YAxis.Exponent = 9;
grid on, xlabel('Senders','FontSize',13), ylabel('bps','FontSize',13), title('Goodput', 'FontSize',13)
saveas(gcf , 'throughput.png');
 
end