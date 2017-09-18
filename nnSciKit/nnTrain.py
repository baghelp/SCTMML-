from sklearn.neural_network import MLPRegressor
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import learning_curve
import numpy as np
import matplotlib.pyplot as plt
TRAIN_PERCENT = 0.99
CV_TEST_PERCENT = 0.005

# X = [[0., 0.], [1., 1.]]
# y = [0, 1]
data = np.loadtxt(open("nnLog.txt", "rb"), delimiter=", ")
np.random.shuffle(data)
m = data.shape[0]
mylist = [1]*m
data = np.insert(data, 0, mylist, axis=1)
train_end = int(TRAIN_PERCENT*m);
cv_end = int(CV_TEST_PERCENT*m);
test_end = int(CV_TEST_PERCENT*m);
X = (data[:train_end, :4])#0-12])
# X = (data[:train_end, :0-12])
y = (data[:train_end, 0-12:])
Xval = (data[train_end:train_end+cv_end, :4])#0-12])
# Xval = (data[train_end:train_end+cv_end, :0-12])
yval = (data[train_end:train_end+cv_end, 0-12:])
Xtest = (data[train_end+cv_end:train_end+cv_end+test_end, :0-12])
ytest = (data[train_end+cv_end:train_end+cv_end+test_end, 0-12:])
print data.shape
print X.shape
print y.shape
# print data[0,0]
# print X[0,0]

reg = MLPRegressor(
        hidden_layer_sizes=(26),  activation='relu', solver='adam',
        alpha=0.001,batch_size='auto',
        learning_rate='constant', learning_rate_init=0.01, power_t=0.5,
        max_iter=1000, shuffle=True,
        random_state=9, tol=0.0001, verbose=False, warm_start=False,
        momentum=0.9, nesterovs_momentum=True,
        early_stopping=False, validation_fraction=0.1,
        beta_1=0.9, beta_2=0.999, epsilon=1e-08)
reg = reg.fit(X, y)



y_predict = reg.predict([1,9,0,0])
print "\n\n----Neural Net----"
print "prediction"
print y_predict[0,:]
# print "real"
# print yval[0,:]
# print "error = "
# print np.linalg.norm(y_predict - yval)/cv_end
# print "params:"
# theta =  reg.coefs_
# print theta[0].shape
# print theta[1].shape

# print "\n\n\n"
# theta0 = np.matrix.transpose(theta[0])
# print(', '.join('{}'.format(k) for k in enumerate(theta0)))
# print theta0
# print "\n\n\n"
# print np.matrix.transpose(theta[1])
# print "\n\n\n"



reg = LinearRegression(fit_intercept=True, normalize=False)
reg = reg.fit(X, y)

y_predict = reg.predict([1,6,0,0])
print "\n\n----LinReg----"
print "prediction"
print y_predict[0,:]
# print "real"
# print yval[0,:]
# print "error = "
# print np.linalg.norm(y_predict - yval)/cv_end
# print "params:"
# print reg.coef_



# est = LinearRegression()
est = MLPRegressor(
        hidden_layer_sizes=(3,1),  activation='relu', solver='adam',
        alpha=0.001,batch_size='auto',
        learning_rate='constant', learning_rate_init=0.01, power_t=0.5,
        max_iter=1000, shuffle=True,
        random_state=9, tol=0.0001, verbose=False, warm_start=False,
        momentum=0.9, nesterovs_momentum=True,
        early_stopping=False, validation_fraction=0.1,
        beta_1=0.9, beta_2=0.999, epsilon=1e-08)
train_sizes, train_scores, test_scores = learning_curve(est, X, y)
train_s_mean = np.mean(train_scores, axis=1)
train_s_std = np.std(train_scores, axis=1)
test_s_mean = np.mean(test_scores, axis=1)
test_s_std = np.std(test_scores, axis=1)
plt.grid()
plt.fill_between(train_sizes, train_s_mean - train_s_std,
        train_s_mean + train_s_std, alpha = 0.1, color="r")
plt.fill_between(train_sizes, test_s_mean - test_s_std,
        test_s_mean + test_s_std, alpha = 0.1, color="g")
plt.plot(train_sizes, train_s_mean, 'o-', color="r", label="Training score")
plt.plot(train_sizes, test_s_mean, 'o-', color="g", label="Cross-val score")
plt.legend(loc="best")
# plt.show()
# plot_learning_curve(estimator, title, X, y, (0.7, 1.01), cv=cv, n_jobs=4)


# fig = plt.figure()
# ax1 = fig.add_subplot(111)
# ax1.scatter(X, y, s=10, c='b', marker="s", label='real')
# ax1.scatter(test_x,test_y, s=10, c='r', marker="o", label='NN Prediction')
#
# plt.show()

