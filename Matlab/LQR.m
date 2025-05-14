% Define the transfer function
G = tf(9.928, [1, 6.906, 30.67, 26.99]);

% Extract the numerator and denominator coefficients
[num, den] = tfdata(G, 'v');

% Number of states (order of the denominator polynomial)
n = length(den) - 1;

% Construct the controllable canonical form
A = [zeros(n-1, 1) eye(n-1); -fliplr(den(2:end))];
B = [zeros(n-1, 1); 1];
C = fliplr(num(2:end)) - num(1) * fliplr(den(2:end));
D = num(1);

% Display the controllable canonical form state-space matrices
disp('Controllable Canonical Form A_cc =');
disp(A);
disp('Controllable Canonical Form B_cc =');
disp(B);
disp('Controllable Canonical Form C_cc =');
disp(C);
disp('Controllable Canonical Form D_cc =');
disp(D);

% Augment the system to include the integral of the output error
A_aug = [A, zeros(size(A,1), 1);
         -C, 0];
B_aug = [B;
         0];
C_aug = [C, 0];
D_aug = D;

% Display the augmented state-space matrices
disp('A_aug =');
disp(A_aug);
disp('B_aug =');
disp(B_aug);
disp('C_aug =');
disp(C_aug);
disp('D_aug =');
disp(D_aug);

Q_aug = diag([0.03, 0.1, 0.001, 0.001]);  % Increase weights for speed and integral
R = 0.013;  % Decrease to allow more control effort

% Compute the LQR gain for the augmented system
K_aug = lqr(A_aug, B_aug, Q_aug, R);

% Extract the state feedback gain and integral gain
K = K_aug(1:end-1);
Ki = K_aug(end);

% Display the LQR gains
disp('State feedback gain K =');
disp(K);
disp('Integral gain Ki =');
disp(Ki);