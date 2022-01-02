dt = 0.01;
T = 5;
time = 0:dt:T;

y = load("f9.txt");
N = length(y);
figure
plot(time, y), grid;

% Finding Fourier transforms
fourier_func = zeros(1, N);
for m = 1:N
  for j = 1:N
    fourier_func(m) = fourier_func(m) + 1 / N * y(j) * exp(1) ^ (-1i * 2 * pi * m * j / N);
  end
end
fourier_func = abs(fourier_func);
figure
plot(fourier_func), grid;

% Finding frequency and extremum
df = 1 / T;
f = 0:df:round(N / 2) * df;
counter = 0;
extr = zeros(2, 1);
for k = 3:round(N / 2) - 1
  if (fourier_func(k) > fourier_func(k + 1) && ...
          fourier_func(k) > fourier_func(k - 1) && ...
          abs(fourier_func(k) - fourier_func(k + 1)) > 1)
    counter = counter + 1;
    extr(counter) = k * df;
  end
end

% Finding approximate parameters
sn = sin(2 * pi * extr(1) * time);
A = [sum(time .^ 6), sum(time .^ 5), sum(time .^ 4), sum(sn .* time .^ 3), sum(time .^ 3);
     sum(time .^ 5), sum(time .^ 4), sum(time .^ 3), sum(sn .* time .^ 2), sum(time .^ 2);
     sum(time .^ 4), sum(time .^ 3), sum(time .^ 2), sum(sn .* time), sum(time);
     sum(sn .* time .^ 3), sum(sn .* time .^ 2), sum(sn .* time), sum(sn .* sn), sum(N * sn);
     sum(time .^ 3), sum(time .^ 2), sum(time), sum(N * sn), N];
b = [sum(y .* time.^ 3), sum(y .* time .^ 2), sum(y .* time), sum(y .* sn),  sum(y)];
a = A \ b';

% Building approximate function using founded parameters
approx = a(1) .* time .^ 3 + a(2) .* time .^ 2 + a(3) .* time + a(4) .* sn + a(5);
figure
plot(time, approx), grid;

max_influence = extr
a