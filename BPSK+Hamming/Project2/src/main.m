function main
[snr,BPSK_ERR_Rate,Hamming_ERR_Rate] = textread('data.txt','%f%f%f','headerlines',1);
plot(snr, BPSK_ERR_Rate,'r-',snr, Hamming_ERR_Rate,'b-');
legend('BPSK������','Hamming������');
grid on;
xlabel('�����');
ylabel('������');
title('BPSK��Hamming���뷽ʽ�����ʱȽ�');
