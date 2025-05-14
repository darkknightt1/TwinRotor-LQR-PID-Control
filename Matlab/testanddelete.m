% % Define the s-domain transfer function
 num = [1];            % Numerator coefficients
 den = [1 1 0];        % Denominator coefficients
sys_s = tf(num, den); % Transfer function in the s-domain
sys_s
% Specify the sampling time
Ts = 1; % Sampling time (in seconds)

% Convert the s-domain system to the z-domain using zero-order hold (ZOH)
sys_z = c2d(sys_s, Ts, 'zoh');

% Display the z-domain system
disp('Z-domain Transfer Function (ZOH):');
sys_z

% Define feedback (unit feedback, H(z) = 1)
H = 1; % Feedback transfer function

% Compute the closed-loop system in the z-domain
closed_loop_sys = feedback(sys_z, H);
% 
% % Display the closed-loop transfer function
% disp('Closed-loop Z-domain Transfer Function:');
% closed_loop_sys
% 
% % Optional: Plot step response for the closed-loop system
% figure;
% step(closed_loop_sys);
% title('Closed-loop Step Response (ZOH)');

% T = 0.5;
% G_s = tf(num, den); % Define G(s) in transfer function form
% G_z = c2d(G_s, T, 'zoh')      % Convert to discrete-time using zoh method
% 
% K=4;
% CLTF = feedback(K * G_z, 1)             % Closed-loop transfer function
% 
% Gz = tf([0.2304, 0.212], [1, -1.548, 0.9908], 2); 
% syms s z;
% G_s = subs(Gz, z, (s+1)/(s-1))
% 
% Gs_again = d2c(CLTF, 'tustin'); % Convert back to G(s) using Tustin
%Gs_again
%rlocus(Gs_again)
