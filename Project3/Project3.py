import random
import os
from PIL import Image
from keras.initializers.initializers_v1 import RandomNormal
from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.utils import np_utils
from pandas import DataFrame
from sklearn.metrics import confusion_matrix
from sklearn.utils import shuffle
import matplotlib.pyplot as plt
import numpy as np
from pretty_print_confusion_matrix import plot_confusion_matrix_from_data

# Pre-process data
images = np.load('data/images.npy')
labels = np.load('data/labels.npy')

images, labels = shuffle(images, labels)  # shuffle both arrays so they have the same indices
labels = np_utils.to_categorical(labels, num_classes=10)  # make labels a one hot vector

# Divide data into 60, 15, and 25%
x_train, x_val, x_test = images[:3900], images[3900:4875], images[4875:]
y_train, y_val, y_test = labels[:3900], labels[3900:4875], labels[4875:]

neurons = 128
activationF = 'relu'
inputNeurons = 256
EPOCH = 200
BATCH = 200

# Make the model
model = Sequential()
model.add(Dense(inputNeurons, input_shape=(28*28, ), kernel_initializer='he_normal'))
model.add(Activation(activationF))

model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))
model.add(Dense(neurons, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation=activationF))


model.add(Dense(10, kernel_initializer='he_normal'))  # last layer
model.add(Activation('softmax'))

# Compile Model
model.compile(optimizer='sgd',
              loss='categorical_crossentropy', 
              metrics=['accuracy'])

# Train Model
history = model.fit(x_train, y_train,
                    validation_data=(x_val, y_val),
                    epochs=EPOCH,
                    batch_size=BATCH)

# Save model
model.save("./")

# Report Results
y_pred = model.predict(x_test)

# Plot training performance
fig, axs = plt.subplots(1,2)
for i, h in enumerate(history.history.items()):
    a = axs[i]
    a.plot(h[1])
    a.set_title(h[0])
    a.set_xlabel("epoch")
    if i == 1: break

fig.tight_layout()
plt.show()

test_class, pred_class = np.argmax(y_test, axis=1), np.argmax(y_pred, axis=1)
cols = [i for i in range(10)]
# Plot confusion matrix
plot_confusion_matrix_from_data(test_class, pred_class,
                                columns=cols)

# visualize misclassified images
confm = confusion_matrix(test_class, pred_class)
df_cm = DataFrame(confm, index=cols, columns=cols)
misclass = []
while True:
    index = random.randrange(0, len(test_class))
    if test_class[index] != pred_class[index]:
        misclass.append((index, pred_class[index], test_class[index]))

    if len(misclass) == 3:
        break

for file in os.listdir('./'):
    if file.endswith('.jpg'): os.remove(file)

for i in range(3):
    im = Image.fromarray(x_test[misclass[i][0]].reshape((28, 28)).astype('uint8'))
    im.save("{0} misclassed as {1}.jpg".format(misclass[i][2], misclass[i][1]))

# TODO: write report
# TODO: save best model
