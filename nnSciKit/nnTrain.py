from sklearn.neural_network import MLPRegressor
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import learning_curve
import numpy as np
import matplotlib.pyplot as plt


def ReLU( X ) :
    # a.k.a "Make Negative Things Zero"
    new = []
    for i in X:
        if i > 0 :
            new.append(i)
        else :
            new.append(0)
    return new


TRAIN_PERCENT = 0.8
CV_TEST_PERCENT = 0.2

data = np.loadtxt(open("dataLog.txt", "rb"), delimiter=", ")
np.random.shuffle(data)
m = data.shape[0]
mylist = [1]*m
data = np.insert(data, 0, mylist, axis=1)
num_train_samples = int(TRAIN_PERCENT*m);
num_cv_samples = int(CV_TEST_PERCENT*m);
num_test_samples = int(CV_TEST_PERCENT*m);
print num_train_samples," samples for training"
print num_cv_samples," samples for validation"
# X = (data[:num_train_samples, :4])#0-12])
X = (data[:num_train_samples, :-12])
y = (data[:num_train_samples, -12:])
# Xval = (data[num_train_samples:num_train_samples+num_cv_samples, :4])#0-12])
Xval = (data[num_train_samples:num_train_samples+num_cv_samples, :0-12])
yval = (data[num_train_samples:num_train_samples+num_cv_samples, 0-12:])
Xtest = (data[num_train_samples+num_cv_samples:num_train_samples+num_cv_samples+num_test_samples, :0-12])
ytest = (data[num_train_samples+num_cv_samples:num_train_samples+num_cv_samples+num_test_samples, 0-12:])
# print data[0,0]
# print X[0,0]

reg = MLPRegressor( #neural net
        hidden_layer_sizes=(12),  activation='relu', solver='adam',
        alpha=0.001,batch_size='auto',
        learning_rate='constant', learning_rate_init=0.01, power_t=0.5,
        max_iter=10000, shuffle=True,
        random_state=9, tol=0.0001, verbose=False, warm_start=False,
        momentum=0.9, nesterovs_momentum=True,
        early_stopping=False, validation_fraction=0.1,
        beta_1=0.9, beta_2=0.999, epsilon=1e-08)
reg = reg.fit(X, y)


theta =  reg.coefs_
b =  reg.intercepts_

# old_theta0 = [ [0.480282699602 ,-0.376382829159 ,0.0668414935513]
#         ,[0.0299002759557 ,0.971136753854 ,0.0178707825391]
#         ,[0.0750594734271 ,1.21541801579 ,0.329848388173]
#         ,[0.0267547351879 ,0.0226468225198 ,-0.859273339295]
#          ,[0.0111920920372 ,0.0843847154767 ,-0.095946578909]
#          ,[-0.158314931496 ,-0.424602051394 ,-0.400751244397]
#          ,[0.286902019148 ,0.0873524381134,  -1.18281975165]]
# old_theta1 = [ [1.093913772, 0.794829146828, 0.0370303070559, 0.428464153996,
#         1.00073512584, 0.194148798531 ,0.634742902561 ,0.876992063004,
#         0.00578318118618 ,1.04997430873 ,0.718810670711 ,0.226057009431],
#         [0.653680203443 ,0.693461870454 ,1.25996756855 ,0.997843660428,
#         1.03137595599 ,-0.492109597523 ,0.812686375107 ,0.922687209688,
#         0.137106720518 ,0.853176460811 ,0.951217479935 ,0.267912361607],
#         [1.0362707941 ,0.784323959704 ,0.259317276049 ,0.754000776279
#         ,0.93475907517, -0.197608720292 ,1.13759741301 ,0.579094516223
#         ,0.101826493321, 0.348878850427 ,1.21613683123 ,0.565824161804 ] ]
# old_b0 = [0.565824161804, 0.565824161804, 0.565824161804]
# old_b1 = [0.565824161804 ,0.565824161804 ,0.565824161804 ,0.565824161804
#         ,0.565824161804 ,0.565824161804 ,0.565824161804 ,0.565824161804
#         ,0.565824161804 ,0.565824161804 ,0.565824161804 ,0.565824161804]


# sample = Xval[0:4,:]
# for i in [0,1,2,3]:
#     thing = sample[i,:]
#         
# # sample = [1,7,0,0,0.591458,-0.0547478,0.681762]
#     a1 = np.dot(thing,theta[0]) + b[0]
#     # print "a1: ",a1
#     a2 = np.dot(ReLU(a1),theta[1]) + b[1]
#     print "my prediction: \n", ReLU(a2)

# sample = [
#         1,0,0,7,45.9878,0.347252,0.0199498,-8.41467,-0.0184404,3.89942,8.42531,
#         -0.0184426,3.87637,-8.42531,-0.0348532,-3.87677,8.41467,-0.0348623,
#         -3.89982,-0.0115327,3.82814,-8.428,0.0115155,3.86095,8.41195,
#         -0.0115116,-3.95756,-8.41156,0.0115301,-3.91923,8.42838,3.59434,
#         -8.14637,0.0130534,3.97767,8.68923,-0.022943,-3.59431,-8.14637,
#         0.0228778]
y_predict = reg.predict(Xval)
# y_predict = reg.predict(sample)
print "\n\n----Neural Net----"
# print "input"
# print sample
print "prediction"
# print y_predict[0:4,:]
# print y_predict
# print "real"
# print yval[0:4,:]
print "avg error = "
# print np.linalg.norm(y_predict - yval)/num_cv_samples
print np.mean(abs(y_predict - yval))
# print "params:"
print "theta0 shape: ",
print theta[0].shape
print "theta1 shape: ",
print theta[1].shape
print "b0 shape: ",
print b[0].shape
print "b1 shape: ",
print b[1].shape
b0 = b[0]
b1 = b[1]


# Print theta's and intercepts to file
print "\n\n\n"
# theta0 = np.matrix.transpose(theta[0])
# theta1 = np.matrix.transpose(theta[1])
theta0 = theta[0]
theta1 = theta[1]
# print theta0
# print theta1
outString = ""
for row in theta0:
    # outString += '{'
    for col in row:
        outString += str(col)
        outString += ' '
        # item+=1
        # if( item%5 == 0 ):
        #     outString+='\n'
    # outString += str(row[-1])
    # outString += '},\n'
    # if( (row == theta0[-1]).all() ):
    #     outString = outString[:-2]
    #     outString += '\n'
# outString += '};'
outFile = open("Theta0.txt", "w")
outFile.write( outString )
outFile.close()
# np.savetxt("Theta0.txt", outString)

outString = ""
for row in theta1:
    for col in row:
        outString += str(col)
        outString += ' '
outFile = open("Theta1.txt", "w")
outFile.write( outString )
outFile.close()

outString = ""
for row in b1:
    outString += str(col)
    outString += ' '
outFile = open("b1.txt", "w")
outFile.write( outString )
outFile.close()

outString = ""
for row in b0:
    outString += str(col)
    outString += ' '
outFile = open("b0.txt", "w")
outFile.write( outString )
outFile.close()


#
#
#
# # x = [1, 2, 3, 4]
# # print x[-1]
#
# # for thing in x[:3]
# #     print thing
#
# # {  { thing, thing, thing },
# #     {stuff, stuff, stuff } };
#     
#
#
#
# # print "\n\n\n"
# # print np.matrix.transpose(theta[1])
# # print "\n\n\n"
#
# #
# #
# reg = LinearRegression(fit_intercept=True, normalize=False) #Linear Regression
# reg = reg.fit(X, y)
#
# y_predict = reg.predict(Xval)
# print "\n\n----LinReg----"
# print "prediction"
# print y_predict[0:4,:]
# print "real"
# print yval[0:4,:]
# print "error = "
# print np.linalg.norm(y_predict - yval)/num_cv_samples
# # # print "params:"
# # # print reg.coef_
# #
# #
# #
# # # est = LinearRegression()
# est = MLPRegressor(
#         hidden_layer_sizes=(3),  activation='relu', solver='adam',
#         alpha=0.001,batch_size='auto',
#         learning_rate='constant', learning_rate_init=0.01, power_t=0.5,
#         max_iter=1000, shuffle=True,
#         random_state=9, tol=0.0001, verbose=False, warm_start=False,
#         momentum=0.9, nesterovs_momentum=True,
#         early_stopping=False, validation_fraction=0.1,
#         beta_1=0.9, beta_2=0.999, epsilon=1e-08)
# train_sizes, train_scores, test_scores = learning_curve(est, X, y)
# train_s_mean = np.mean(train_scores, axis=1)
# train_s_std = np.std(train_scores, axis=1)
# test_s_mean = np.mean(test_scores, axis=1)
# test_s_std = np.std(test_scores, axis=1)
# plt.grid()
# plt.fill_between(train_sizes, train_s_mean - train_s_std,
#         train_s_mean + train_s_std, alpha = 0.1, color="r")
# plt.fill_between(train_sizes, test_s_mean - test_s_std,
#         test_s_mean + test_s_std, alpha = 0.1, color="g")
# plt.plot(train_sizes, train_s_mean, 'o-', color="r", label="Training score")
# plt.plot(train_sizes, test_s_mean, 'o-', color="g", label="Cross-val score")
# plt.legend(loc="best")
# plt.show()
# plot_learning_curve(estimator, title, X, y, (0.7, 1.01), cv=cv, n_jobs=4)
# #
# #
# # fig = plt.figure()
# # ax1 = fig.add_subplot(111)
# # ax1.scatter(X, y, s=10, c='b', marker="s", label='real')
# # ax1.scatter(test_x,test_y, s=10, c='r', marker="o", label='NN Prediction')
# #
# # plt.show()
#
