%% Extract data from CSV file

% Specify the file path and name
filePath = 'data3.csv';

% Read the CSV file into a matrix
data = readmatrix(filePath);

% Now 'data' contains the numeric values from the CSV file

%% Graph the data
x = data(1,:); 
y = data(2,:);

plot(x,y)