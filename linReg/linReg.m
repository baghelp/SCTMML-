%% Machine Learning Online Class
%  Exercise 5 | Regularized Linear Regression and Bias-Variance
%
%  Instructions
%  ------------
% 
%  This file contains code that helps you get started on the
%  exercise. You will need to complete the following functions:
%
%     linearRegCostFunction.m
%     learningCurve.m
%     validationCurve.m
%
%  For this exercise, you will not need to change any code in this file,
%  or any other files other than those mentioned above.
%

%% Initialization
clear ; close all; clc

%% =========== Part 1: Loading and Visualizing Data =============
%  We start the exercise by first loading and visualizing the dataset. 
%  The following code will load the dataset into your environment and plot
%  the data.
%

% Load Training Data
fprintf('Loading and Visualizing Data ...\n')

% Load from ex5data1: 
% You will have X, y, Xval, yval, Xtest, ytest in your environment
% load ('ex5data1.mat');
data = load ('oldLog.txt');
shuffledData = data( randperm( size( data, 1) ), :) ;
m = size(shuffledData, 1);
X = shuffledData(1:round(0.6*m), 1:3);
y = shuffledData(1:round(0.6*m), 4:end);
Xval = shuffledData(round(0.6*m):(0.8*m), 1:3);
yval = shuffledData(round(0.6*m):(0.8*m), 4:end);
Xtest = shuffledData(round(0.8*m):end, 1:3);
ytest = shuffledData(round(0.8*m):end, 4:end);
% yval = yval(:, [1:6,8:end]);
% y = y(:, [1:6,8:end]);

% sxv = size(Xval)
% syv = size(yval)
% sx = size(X)
% sy = size(y)

m = size(X, 1);

% Plot training data
% plot(X, y, 'rx', 'MarkerSize', 10, 'LineWidth', 1.5);
% xlabel('Change in water level (x)');
% ylabel('Water flowing out of the dam (y)');

% fprintf('Program paused. Press enter to continue.\n');
% pause;

%% =========== Part 2: Regularized Linear Regression Cost =============
%  You should now implement the cost function for regularized linear 
%  regression. 
%

% theta = ones(4, 13);
% J = linearRegCostFunction([ones(m, 1) X], y, theta, 1);

% fprintf(['Cost at theta = [1 ; 1]: %f '...
%          '\n(this value should be about 303.993192)\n'], J);

% fprintf('Program paused. Press enter to continue.\n');
% pause;

%% =========== Part 3: Regularized Linear Regression Gradient =============
%  You should now implement the gradient for regularized linear 
%  regression.
%

% theta = [1 ; 1; 1; 1];
% [J, grad] = linearRegCostFunction([ones(m, 1) X], y, theta, 1);

% fprintf(['Gradient at theta = [1 ; 1]:  [%f; %f] '...
%          '\n(this value should be about [-15.303016; 598.250744])\n'], ...
%          grad(1), grad(2));

% fprintf('Program paused. Press enter to continue.\n');
% pause;


%% =========== Part 4: Train Linear Regression =============
%  Once you have implemented the cost and gradient correctly, the
%  trainLinearReg function will use your cost function to train 
%  regularized linear regression.
% 
%  Write Up Note: The data is non-linear, so this will not give a great 
%                 fit.
%

%  Train linear regression with lambda
% lambda = 5000; % 8.64 cv error
% lambda = 500; % 8.64
% lambda = 50; % 8.51
% lambda = 20; % 8.43
lambda = 20; % 8.52
% lambda = 10; % 8.47
% lambda = 5; % 8.56
%% Conclusion: the higher error in cv dataset is not because of overfitting, but
%is just because of inherent nonlinearities in the
fprintf('Training linear regression with lambda = %f\n', lambda);
% [theta] = trainLinearReg([ones(m, 1) X], y, lambda);
theta = ones(4, 12);
% initial_theta = zeros(size(X, 2), 12);
alpha = 0.001;
iterations = 4000;
[theta, J_history] = gradientDescentMulti([ones(m, 1) X], y, theta, lambda, alpha, iterations);
% [theta, J_history] = gradientDescentMulti(X, y, initial_theta, lambda, alpha, iterations);

plot([1:size(J_history, 1)], J_history)
%  Plot fit over the data
% plot(X, y, 'rx', 'MarkerSize', 10, 'LineWidth', 1.5);
% xlabel('Change in water level (x)');
% ylabel('Water flowing out of the dam (y)');
% hold on;
% plot(X, [ones(m, 1) X]*theta, '--', 'LineWidth', 2)
% hold off;
%
fprintf('Model Trained.\n');
theta = theta
fprintf('Program paused. Press enter to continue.\n');
pause;


%% =========== Part 5: Learning Curve for Linear Regression =============
%  Next, you should implement the learningCurve function. 
%
%  Write Up Note: Since the model is underfitting the data, we expect to
%                 see a graph with "high bias" -- Figure 3 in ex5.pdf 
%

fprintf('Plotting learning curves.\n');
lambda = 5;
[error_train, error_val] = ...
    learningCurve([ones(m, 1) X], y, ...
                  [ones(size(Xval, 1), 1) Xval], yval, ...
                  lambda, theta, alpha, iterations);

plot(1:50:m, error_train, 1:50:m, error_val);
title('Learning curve for linear regression')
legend('Train', 'Cross Validation')
xlabel('Number of training examples')
ylabel('Error')
axis([0 13 0 150])

fprintf('# Training Examples\tTrain Error\tCross Validation Error\n');
for i = 1:m/50
    fprintf('  \t%d\t\t%f\t%f\n', i, error_train(i), error_val(i));
end

fprintf('Program paused. Press enter to continue.\n');
pause;

%% =========== Part 6: Feature Mapping for Polynomial Regression =============
%  One solution to this is to use polynomial regression. You should now
%  complete polyFeatures to map each example into its powers
%

p = 2;

% Map X onto Polynomial Features and Normalize
X_poly = polyFeatures(X, p);
[X_poly, mu, sigma] = featureNormalize(X_poly);  % Normalize
X_poly = [ones(m, 1), X_poly];                   % Add Ones

% Map X_poly_test and normalize (using mu and sigma)
X_poly_test = polyFeatures(Xtest, p);
X_poly_test = bsxfun(@minus, X_poly_test, mu);
X_poly_test = bsxfun(@rdivide, X_poly_test, sigma);
X_poly_test = [ones(size(X_poly_test, 1), 1), X_poly_test];         % Add Ones

% Map X_poly_val and normalize (using mu and sigma)
X_poly_val = polyFeatures(Xval, p);
X_poly_val = bsxfun(@minus, X_poly_val, mu);
X_poly_val = bsxfun(@rdivide, X_poly_val, sigma);
X_poly_val = [ones(size(X_poly_val, 1), 1), X_poly_val];           % Add Ones

% fprintf('Normalized Training Example 1:\n');
% fprintf('  %f  \n', X_poly(1, :));

fprintf('\nProgram paused. Press enter to continue.\n');
pause;



%% =========== Part 7: Learning Curve for Polynomial Regression =============
%  Now, you will get to experiment with polynomial regression with multiple
%  values of lambda. The code below runs polynomial regression with 
%  lambda = 0. You should try running the code with different values of
%  lambda to see how the fit and learning curve change.
%

lambda = 0;
theta = zeros(10, 12);
[theta, J_history] = gradientDescentMulti( X_poly, y, theta, lambda, alpha, iterations);
theta = theta
% [theta] = trainLinearReg(X_poly, y, lambda);
% "here"

% Plot training data and fit
% figure(1);
% plot(X, y, 'rx', 'MarkerSize', 10, 'LineWidth', 1.5);
% plotFit(min(X), max(X), mu, sigma, theta, p);
% xlabel('Change in water level (x)');
% ylabel('Water flowing out of the dam (y)');
% title (sprintf('Polynomial Regression Fit (lambda = %f)', lambda));

figure(2);
[error_train, error_val] = ...
    learningCurve(X_poly, y, X_poly_val, yval, lambda, theta, alpha,
    iterations);
plot(1:50:m, error_train, 1:50:m, error_val);

title(sprintf('Polynomial Regression Learning Curve (lambda = %f)', lambda));
xlabel('Number of training examples')
ylabel('Error')
axis([0 13 0 100])
legend('Train', 'Cross Validation')

fprintf('Polynomial Regression (lambda = %f)\n\n', lambda);
fprintf('# Training Examples\tTrain Error\tCross Validation Error\n');

i = 1;
for j = 1:50:m
    fprintf('  \t%d\t\t%f\t%f\n', i, error_train(i), error_val(i));
    i++;
end

fprintf('Program paused. Press enter to continue.\n');
pause;

%% =========== Part 8: Validation for Selecting Lambda =============
%  You will now implement validationCurve to test various values of 
%  lambda on a validation set. You will then use this to select the
%  "best" lambda value.
%

[lambda_vec, error_train, error_val] = ...
    validationCurve(X_poly, y, X_poly_val, yval, theta, alpha, iterations);

close all;
plot(lambda_vec, error_train, lambda_vec, error_val);
legend('Train', 'Cross Validation');
xlabel('lambda');
ylabel('Error');

fprintf('lambda\t\tTrain Error\tValidation Error\n');
for i = 1:length(lambda_vec)
	fprintf(' %f\t%f\t%f\n', ...
            lambda_vec(i), error_train(i), error_val(i));
end

fprintf('Program paused. Press enter to continue.\n');
pause;
