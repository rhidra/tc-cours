x = 2*pi*rand(1000000,1);
t0 = 3.6559;
w = 2*pi*1000;

y = exp(sin(w*t0 + x)+abs(x)./x);
histogram(y);

