%root locus for third order system with no zeros , good response

zeros = [-2.8957+3.97867j ,-2.8957-3.97867j];   
poles = [0, -1.1146 , -2.8957+3.97867j ,-2.8957-3.97867j ]; 
% 
% 
% % Create the transfer function
G = zpk(zeros, poles,9.928)

rlocus(G);
