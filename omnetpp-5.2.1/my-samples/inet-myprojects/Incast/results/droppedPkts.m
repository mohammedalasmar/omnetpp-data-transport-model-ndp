function droppedPkts

c=dlmread('dropPkts.csv');

senders=c(:,1);
drops=c(:,2);
 
for k1 = 1:length(senders)
    [sv(k1),ix] = min(senders)  ; 
%     pause
    senders(ix) = inf;
    res(k1)=drops(ix);
end


NumSenders=sort(c(:,1));
drops=res';
figure
    movegui('east');
 plot(NumSenders,drops,'--*')
ax = gca;
% ax.YAxis.Exponent = 1;
grid on, xlabel('#senders','FontSize',13), ylabel('dropped Packets','FontSize',13), title('dropped Packets ','FontSize',13)



end