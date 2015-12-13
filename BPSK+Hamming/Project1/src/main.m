function main
[x,y] = textread('data.txt','%f%f','headerlines',1);
plot(x,y/1000000000);
grid on;
xlabel('Es/No(dB)');
ylabel('Bit-error probability');
title('AWGN Channel Coding');
