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




%%

numRTOs=0; 
fid = fopen('requestsRTOs.csv');
textLine = fgets(fid); % Read first line.
lineCounter = 1;
while ischar(textLine)
   textLine= strrep( textLine,'"','');
    numbers = sscanf(textLine, '%f ')  ; 
    for i=1:length(numbers)
    numRTOs(end+1)= numbers(i) ;
    end
	% Read the next line.
    textLine = fgets(fid);
	lineCounter = lineCounter + 1;
end
fclose(fid);

numRTOsRes=numRTOs(3:end);
figure
 movegui('northwest');
 plot(numRTOsRes,'*')
ax = gca;
% ax.YAxis.Exponent = 1;
grid on, xlabel('#senders','FontSize',13), ylabel('Requests #TIMEOUTs','FontSize',13), title('Requests TIMEOUTs ','FontSize',13)



end