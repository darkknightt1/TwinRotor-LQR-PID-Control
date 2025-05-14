
%getting the steadystate model from the system identefication

% num =[2.194];
% den = [1 2.148 12.12 6.5];
% 
% oltf = tf(num,den)
% 
% [A B C D]= tf2ss(num,den)
% 
% 
% %using pole placment
% desired_poles = [-1 -2 -3]; 
%  K = place(A, B, desired_poles)



%third order steady-state
% format long g
% A = [[0 1 0]
%     [0 0 1]
%    [-3.231e+05 -2.498e+04 -361.6]]
% 
% 
% B = [[44.52]
%     [1.161e+04]
%    [-4.99e+06]]
% 
% C = [1 0 0]
% 
% D = [0]
% 
% desired_poles = [-1 , -2 ,-3]; 
% K = place(A, B, desired_poles)



format long g
A = [0 1 0; 0 0 1; -26.9900 -30.6700 -6.9060]

B = [0;0;1]

C = [1 0]

D = [0]

desired_poles = [-1.5+1.25j , -1.5-1.25j]; 
%K = place(A, B, desired_poles)
K=[10.4156 2.6056 0.4359]


