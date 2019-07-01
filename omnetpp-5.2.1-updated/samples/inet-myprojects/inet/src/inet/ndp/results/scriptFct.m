function  scriptFct
c=dlmread('fct.csv');

senders=c(:,1);
fct=c(:,2);
 
 
%  v=[4 2 7 4 12 9];
for k1 = 1:length(senders)
    [sv(k1),ix] = min(senders)  ; 
%     pause
    senders(ix) = inf;
    res(k1)=fct(ix);
end


NumSenders=sort(c(:,1));
fct=res';
mm=mean(fct);
figure
    movegui('south');
 plot(NumSenders,fct,'--*'), hold on, plot(NumSenders,mm*ones(1,length(NumSenders)),'--r')
ax = gca;
% ax.YAxis.Exponent = 1;
grid on, xlabel('Senders','FontSize',13), ylabel('seconds','FontSize',13), title('FCT ','FontSize',13)

saveas(gcf , 'fct.png');
 
end