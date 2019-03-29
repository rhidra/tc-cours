import numpy as np
import cifar
import time

# Activation function
def sigmoid(t):
    return 1/(1+np.exp(-t))

# Derivative of sigmoid
def sigmoid_derivative(p):
    return p * (1 - p)

def ReLU(x):
    return np.maximum(x, 0, x)

def ReLU_derivative(x):
    x[x<=0] = 0
    x[x>0] = 1
    return x

def softmax(x, y):
    # x : row-vector d'une image
    # y : classe de x
    return (np.exp(x[y]) / np.sum(np.exp(x)))

def softmax_grad(softmax):
    s = softmax.reshape(-1,1)
    return np.diagflat(s) - np.dot(s, s.T)

class NeuralNetwork:
    def __init__(self, x, y):
        # size_layer_1 = 40
        size_output_layer = 10
        self.input      = x
        self.weights1   = np.random.rand(self.input.shape[1], size_output_layer) * .001
        # self.weights2   = np.random.rand(size_layer_1, size_output_layer) *.1
        self.y          = y
        self.output     = np.zeros(self.y.shape)

    def feedforward(self):
        #self.layer1 = ReLU(np.dot(self.input, self.weights1))
        self.output = np.dot(self.input, self.weights1)
        return self.output

    """
    def backprop(self):
        # application of the chain rule to find derivative of the loss function with respect to weights2 and weights1
        d_weights2 = np.dot(self.layer1.T, (2*(self.y - self.output) * sigmoid_derivative(self.output)))
        d_weights1 = np.dot(self.input.T,  (np.dot(2*(self.y - self.output) * sigmoid_derivative(self.output), self.weights2.T) * sigmoid_derivative(self.layer1)))

        # update the weights with the derivative (slope) of the loss function
        self.weights1 += d_weights1
        self.weights2 += d_weights2
    """

    """
    def loss_svm(self):
        loss = []
        for scores, y in zip(self.output, self.y):
            margins = np.maximum(0, scores - scores[y] + 1)
            margins[y] = 0
            loss.append(np.sum(margins))
        l = np.mean(loss)
        return l
    """

    def loss(self):
        loss = []
        for scores, y in zip(self.output, self.y):
            loss.append(-np.log(softmax(scores, y)))
        l = np.mean(loss)
        return l

def eval_numerical_gradient(network):
    fx = network.loss()
    grad_w1 = np.zeros(network.weights1.shape)
    #grad_w2 = np.zeros(network.weights2.shape)
    h = 0.00001

    it = np.nditer(network.weights1, flags=['multi_index'], op_flags=['readwrite'])
    while not it.finished:
        if it.multi_index[0] % 500 == 0 and it.multi_index[1] == 0:
            print("Evaluation du gradient pour (%d, %d)"%(it.multi_index[0], it.multi_index[1]))
        i = it.multi_index
        old_value = network.weights1[i]
        network.weights1[i] = old_value + h
        network.feedforward()
        fxh = network.loss()
        network.weights1[i] = old_value

        grad_w1[i] = (fxh - fx) / h
        it.iternext()

    return (grad_w1)

if __name__ == '__main__':
    #np.set_printoptions(threshold=np.nan)

    # X = np.array(([0,0,1],[0,1,1],[1,0,1],[1,1,1]), dtype=float)
    # y = np.array(([0],[1],[1],[0]), dtype=float)
    x, y = cifar.get_training_data(1)
    x = x[:100]
    y = y[:100]
    net = NeuralNetwork(x, y)
    #print(net.weights1)

    for i in range(5):
        #if i % 100 == 0:
        print("for iteration # " + str(i))
        # print("Input : \n" + str(x))
        # print("Actual Output: \n" + str(y))
        # print("Predicted Output: \n" + str(net.feedforward()))
        # print("Loss: \n" + str(np.mean(np.square(y - net.feedforward())))) # mean sum squared loss
        # print("\n")
        net.feedforward()
        print("Loss : %f" % net.loss())
        grad_w1 = eval_numerical_gradient(net)
        net.weights1 -= 0.001 * grad_w1
