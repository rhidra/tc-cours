close all;
clear;
n=[ 100 200 500 1000 2000 5000 10000 100000];

for i=1:length(n)
    subplot(4,2, i);
    x= 2*pi*rand(n(i),1);
    histogram(x, 'Normalization', 'cumcount')
    title(strcat('Histogram N=', num2str(n(i))))
end