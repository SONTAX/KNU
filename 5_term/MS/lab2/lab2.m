clc
clear

X = double(imread("x1.bmp"));
Y = double(imread("y9.bmp"));
figure
imshow(uint8(X));
figure
imshow(uint8(Y));

X = [X; ones(size(X, 2), 1)'];

% Moore-Penroze
X_g_inv = MoorePenroze(X);
A = Y * X_g_inv + ones(size(Y, 1), size(X, 1)) * Z(X', X_g_inv')';
result = A * X;
figure
imshow(uint8(result));
temp = X * X_g_inv * X;
fprintf('Checking conditions for Moore-Penroze:\n');
fprintf("%d\n", norm(X - temp));
temp = X_g_inv * X * X_g_inv;
fprintf("%d\n", norm(X_g_inv - temp));
temp = X * X_g_inv;
fprintf("%d\n", norm(temp - temp'));
temp = X_g_inv * X;
fprintf("%d\n", norm(temp - temp'));
% ######################################

% Greville
X_g_inv = Greville(X);
A = Y * X_g_inv + zeros(size(Y, 1), size(X, 1)) * Z(X', X_g_inv')';
result = A * X;
figure
imshow(uint8(result));
temp = X * X_g_inv * X;
fprintf('Checking conditions for Greville:\n');
fprintf("%d\n", norm(X - temp));
temp = X_g_inv * X * X_g_inv;
fprintf("%d\n", norm(X_g_inv - temp));
temp = X * X_g_inv;
fprintf("%d\n", norm(temp - temp'));
temp = X_g_inv * X;
fprintf("%d\n", norm(temp - temp'));
% ######################################

function matrix = Z (A, A_g_inv)
  matrix = eye(size(A_g_inv, 1)) - A_g_inv * A;
end

function matrix = MoorePenroze (A)
    delta = 1e-5;
    eps = 1e-12;
    A_g_inv_cur = A' / (A * A' + delta * eye(size(A, 1)));
    A_g_inv_prev = 2 * A_g_inv_cur;
    while (max(max((A_g_inv_cur - A_g_inv_prev) .^ 2)) > eps)
        A_g_inv_prev = A_g_inv_cur;
        delta = delta / 2.0;
        A_g_inv_cur = A' / (A * A' + delta * eye(size(A, 1)));
    end
    matrix = A_g_inv_cur;
end

function matrix = Greville (A)
    a = A(1, :)';
    if ((a' * a) == 0)
        A_g_inv = zeros(size(A, 2), 1);
    else
        A_g_inv = a  / (a' * a);
    end
    for i = 2:size(A, 1)
        a = A(i, :)';
        z = Z(A(1:(i - 1), :), A_g_inv);
        r = A_g_inv * A_g_inv';
        condition = a' * z * a;
        if (condition == 0)
            A_g_inv = [A_g_inv - (r * a * a' * A_g_inv) / (1 + a' * r * a), (r * a) / (1 + a' * r * a)];
        else
            A_g_inv = [A_g_inv - (z * a * a' * A_g_inv) / condition, (z * a) / condition];
        end
    end
    matrix = A_g_inv;
end
