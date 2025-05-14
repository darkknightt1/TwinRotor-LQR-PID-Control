% % Specify the Excel file name
 excelFile = 'finalyarbbbb.xlsx'; % Replace with your Excel file name
 sheetName = 'Sheet1';    % Replace with the desired sheet name, if applicable
 range = ''; 
 
 
 data = readmatrix(excelFile, 'Sheet', sheetName, 'Range', range);


% Prepare data for continuous-time identification
%timeData = data(:, 6); % Irregular time
outputData = data(:, 2);
inputData = data(:, 3);

% Package data as iddata without specifying Ts (continuous-time)
idData = iddata(outputData, inputData,0.021870);

