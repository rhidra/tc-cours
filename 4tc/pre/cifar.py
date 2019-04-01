import pickle
import numpy as np

def unpickle(file):
    with open(file, 'rb') as fo:
        d = pickle.load(fo, encoding='bytes')
    return d

def get_training_data(index):
    if index < 1 or index > 5:
        index = 1
    d = unpickle('cifar-10-batches-py/data_batch_{}'.format(index))
    x = d[b'data']
    # y = [[1 if i == label else 0 for i in range(10)] for label in d[b'labels']]
    y = d[b'labels']
    return (x, np.array(y))

def get_test_data():
    d = unpickle('cifar-10-batches-py/test_batch')
    x = d[b'data']
    # y = [[1 if i == label else 0 for i in range(10)] for label in d[b'labels']]
    y = d[b'labels']
    return (x, np.array(y))

def map_label_name(label):
    names = unpickle('cifar-10-batches-py/batches.meta')
    return names[b'label_names'][label].decode()
