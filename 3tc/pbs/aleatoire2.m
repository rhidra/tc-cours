close all;
clear;
n=[ 100 200 500 1000 2000 5000 10000 100000];

for i=1:length(n)
    subplot(4,2, i);
    x=5+sqrt(2)*randn(n(i),1);
    histogram(x)
    title(strcat('Histogram N=', num2str(n(i))))
end