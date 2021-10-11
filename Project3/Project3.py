from keras.initializers.initializers_v1 import RandomNormal
from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.utils import np_utils
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

# Make the model
model = Sequential()
model.add(Dense(5, input_shape=(28*28, ), kernel_initializer='he_normal'))
model.add(Activation('relu'))

model.add(Dense(32, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation='relu'))
model.add(Dense(32, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation='relu'))
model.add(Dense(32, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation='relu'))
model.add(Dense(32, kernel_initializer=RandomNormal(0.0, 0.10, 1), activation='relu'))

model.add(Dense(10, kernel_initializer='he_normal'))  # last layer
model.add(Activation('softmax'))

# Compile Model
model.compile(optimizer='sgd',
              loss='categorical_crossentropy', 
              metrics=['accuracy'])

# Train Model
history = model.fit(x_train, y_train,
                    validation_data=(x_val, y_val),
                    epochs=100,
                    batch_size=512)

# Save model
# model.save("./")

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

# Plot confusion matrix
plot_confusion_matrix_from_data(np.argmax(y_test, axis=1), np.argmax(y_pred, axis=1),
                                columns=[i for i in range(10)])

# TODO: 3 visualizations of misclassified images
# TODO: precision and recall calculations
# TODO: write report
# TODO: save best model
