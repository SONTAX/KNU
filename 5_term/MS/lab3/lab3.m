clc
clear


dataY = load("y9.txt", " ");
c = [0.14, 0.2, 0.2, 0.1]';
m = [9, 28, 18]';
t0 = 0;
T = 50;
h = 0.2;
eps = 1e-12;


while true
    U = zeros(6, 3);
    A = matrixA(m, c);
    y = dataY(:, 1);
    deltaY = zeros(6, 1);
    leftI = zeros(3, 3);
    rightI = zeros(3, 1);
    I = 0.0;
    for i = 2:size(dataY, 2)
        newU = U_RK(A, U, y, m, c, h);
        newY = Y_RK(A, y, h);
        newdeltaY = dataY(:, i) - newY;
        leftI = leftI + (newU' * newU + U' * U) * h / 2;
        rightI = rightI + (newU' * newdeltaY + U' * deltaY) * h / 2;
        I = I + (deltaY' * deltaY + newdeltaY' * newdeltaY) * h / 2;
        U = newU;
        y = newY;
        deltaY = newdeltaY;
    end
    deltaBeta = leftI \ rightI;
    c(2) = c(2) + deltaBeta(1);
    c(4) = c(4) + deltaBeta(2);
    m(1) = m(1) + deltaBeta(3);
    if (norm(deltaBeta) < eps)
        break;
    end
    if (I < eps)
        break;
    end
end


fprintf("c2 = %f\n", c(2));
fprintf("c4 = %f\n", c(4));
fprintf("m1 = %f\n", m(1));


function matrix = matrixA (m, c)
    A = zeros(6, 6);
    A(1, 2) = 1;
    A(2, 1) = -(c(2) + c(1)) / m(1);
    A(2, 3) = c(2) / m(1);
    A(3, 4) = 1;
    A(4, 1) = c(2) / m(2);
    A(4, 3) = -(c(2) + c(3)) / m(2);
    A(4, 5) = c(3) / m(2);
    A(5, 6) = 1;
    A(6, 3) = c(3) / m(3);
    A(6, 5) = -(c(3) + c(4)) / m(3);
    matrix = A;
end


function vector = Y_RK(A, y, h)
    k1 = h * A * y;
    k2 = h * A * (y + k1 / 2);
    k3 = h * A * (y + k2 / 2);
    k4 = h * A * (y + k3);
    vector = y + (k1 + 2 * k2 + 2 * k3 + k4) / 6;    
end


function matrix = U_RK(A, U, y, m, c, h)
    dAy_dbeta = zeros(6, 3);
    dAy_dbeta(2, 1) = (- y(1) + y(3)) / m(1);
    dAy_dbeta(2, 3) = ((c(2) + c(1)) * y(1) - c(2) * y(3)) / (m(1) * m(1));
    dAy_dbeta(4, 1) = (y(1) - y(3)) / m(2);
    dAy_dbeta(6, 2) = - y(5) / m(3);
    k1 = h * (A * U + dAy_dbeta);
    k2 = h * (A * (U + k1 / 2) + dAy_dbeta);
    k3 = h * (A * (U + k2 / 2) + dAy_dbeta);
    k4 = h * (A * (U + k3) + dAy_dbeta);
    matrix = U + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
end
