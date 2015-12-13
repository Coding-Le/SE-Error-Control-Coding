function main
[snr,BPSK_ERR_Rate,Hamming_ERR_Rate] = textread('data.txt','%f%f%f','headerlines',1);
plot(snr, BPSK_ERR_Rate,'r-',snr, Hamming_ERR_Rate,'b-');
legend('BPSK误码率','Hamming误码率');
grid on;
xlabel('信噪比');
ylabel('误码率');
title('BPSK和Hamming编码方式误码率比较');
