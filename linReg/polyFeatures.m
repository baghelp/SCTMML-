function [X_poly] = polyFeatures(X, p)
%POLYFEATURES Maps X (2D matrix) into the p-th power
%   [X_poly] = POLYFEATURES(X, p) takes a data matrix X (size m x 1) and
%   maps each example into its polynomial features where
%   X_poly(i, :) = [X(i) X(i).^2 X(i).^3 ...  X(i).^p];
%


% You need to return the following variables correctly.

x_cols = size(X, 2);
new_features = 0;
while x_cols > 0
  new_features += x_cols;
  x_cols--;
end
% new_features = size(X,2)^2 + (size(X,2) - 1)^2
X_poly = zeros(size(X,1), size(X, 2) + new_features);

% ====================== YOUR CODE HERE ======================
% Instructions: Given a vector X, return a matrix X_poly where the p-th 
%               column of X contains the values of X to the p-th power.
%
% 
x_cols = size(X, 2);
X_poly(:, 1:x_cols) = X;
x_ind = x_cols+1;
for feature = 1:x_cols
  for second = feature:x_cols
    X_poly(:, x_ind) = X(:, feature).*X(:, second);
    x_ind++;
  end
end
% X_poly

% for i = 1:p
%   X_poly(:, x_ind:x_cols*i) = X.^i;
%   x_ind += x_cols;
% end








% =========================================================================

end
