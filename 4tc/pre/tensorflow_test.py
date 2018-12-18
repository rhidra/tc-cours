import cifar

# TensorFlow and tf.keras
import tensorflow as tf
from tensorflow import keras

# Helper libraries
import numpy as np
import matplotlib.pyplot as plt


model = keras.Sequential([
    keras.layers.Dense(128, activation=tf.nn.relu),
    keras.layers.Dense(10, activation=tf.nn.softmax)
])

model.compile(optimizer=tf.train.AdamOptimizer(),
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])


x1, y1 = cifar.get_training_data(1)
x2, y2 = cifar.get_training_data(2)
x3, y3 = cifar.get_training_data(3)
x4, y4 = cifar.get_training_data(4)
x5, y5 = cifar.get_training_data(5)

x = np.concatenate([x1,x2,x3,x4,x5])
y = np.concatenate([y1,y2,y3,y4,y5])

model.fit(x, y, epochs=5)

test_images, test_labels = cifar.get_test_data()

print("Testing accuracy of the network ...")
test_loss, test_acc = model.evaluate(test_images, test_labels)

print("Test loss : {}".format(test_loss))
print("Test accuracy : {}".format(test_acc))
