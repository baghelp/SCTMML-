function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));
TESTING = 0;

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%

% size(X)
X = [ones( size( X, 1 ), 1) X];
a1 = sigmoid(X*Theta1');
a1 = [ones( size( a1, 1 ), 1) a1];
out = sigmoid(a1*Theta2');
% predict = find( out' == max(out', [], 1)) - [0:num_labels:num_labels*m - 1]';
% h = out == max(out, [], 1);
h = out;

truth = zeros(m, num_labels);
for row = 1:m
  truth(row, y(row)) = 1;
end
y = truth;

% ysize = size(y)

% xsize = size(X)
% a1size = size(a1)

% outsize = size(out)
% h_samp = h(30:40)'
% y_samp = y(30:40)'
% out_samp = out(1, :)
% ysize = size(truth)
% hsize = size(h)


% for i = 1:m
%   for k = 1:num_labels
%     J += (-y(i, k)*log( h(i, k) ) - (1 - y(i, k) )*log( 1 - h(i, k) ) )/m;
%   end
% end
%
% J = J
% size(Theta1)
% size(Theta2)
% size(sum(Theta1))
% size(sum(Theta2))

J = sum( sum( -y.* log( h ) - ( ones( size( y ) ) - y ) .* ...
log( ones( size( h ) ) - h ) ) )/m +...
lambda*( sum(sum( Theta1(:,2:end).^2 )) +sum(sum( Theta2(:,2:end).^2 )))/(2*m);



for t = 1:m
  % part 1
  a_1 = X(t, :);
  z_2 = a_1*Theta1';
  a_2 = [1 sigmoid(z_2)];
  z_3 = a_2*Theta2';
  a_3 = sigmoid(z_3);

  % part 2
  d_3 = a_3 - y(t, :);

  if 0
    t = t
    sizeTheta2 = size(Theta2)
    sizea_1 = size(a_1)
    sizez_2 = size(z_2)
    sizea_2 = size(a_2)
    sizez_3 = size(z_3)
    sizea_3 = size(a_3)
    sized_3 = size(d_3)
    sizey = size(y(t,:))
  end
  % part 3
  d_2 = Theta2'*d_3'.*[1 sigmoidGradient(z_2)]';

  if 0
    t = t
    sizeTheta2 = size(Theta2)
    sizea_1 = size(a_1)
    sizez_2 = size(z_2)
    sizea_2 = size(a_2)
    sizez_3 = size(z_3)
    sizea_3 = size(a_3)
    sized_3 = size(d_3)
    sized_2 = size(d_2)
  end

  % part 4
  % size(Theta2_grad)
  Theta1_grad += d_2(2:end)*a_1;% d_3(2:end)*a_2];
  Theta2_grad += d_3'*a_2;% d_3(2:end)*a_2];
  % size(d_2)
  % size(a_1)

end
% part 5
Theta1_grad /= m;
Theta2_grad /= m;

Theta1_grad += lambda*[zeros(size(Theta1, 1), 1) Theta1(:, 2:end) ]/m;
Theta2_grad += lambda*[zeros(size(Theta2, 1), 1) Theta2(:, 2:end) ]/m;
  
% Theta2_grad(:,1) = 0;














% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end