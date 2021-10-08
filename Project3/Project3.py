import numpy.random
from keras.models import Sequential
from keras.layers import Dense, Activation
import numpy as np

# pre-process data
images = np.load('data/images.npy')
labels = np.load('data/labels.npy')

print(images[0].shape)

num_samples = 6500
num_classes = 10
samples_per_class = int(num_samples/num_classes)

x_train, x_val, x_test = [], [], []
y_train, y_val, y_test = [], [], []

for i in range(num_classes):
    img_class = images[samples_per_class*i:(samples_per_class*(i+1))]
    numpy.random.shuffle(img_class)
    x_train.extend(img_class[:390])  # first 60% is training
    x_val.extend(img_class[390:488])  # next 15% is validation
    x_test.extend(img_class[488:])  # last 25% is test

    one_hot_v = np.zeros(10)
    one_hot_v[i] = 1
    y_train.extend([one_hot_v, ] * 390)
    y_val.extend([one_hot_v, ] * 98)
    y_test.extend([one_hot_v, ] * 162)


# Model Template
model = Sequential() # declare model
model.add(Dense(10, input_shape=(28*28, ), kernel_initializer='he_normal')) # first layer
model.add(Activation('relu'))
#
#
#
# Fill in Model Here
#
#
model.add(Dense(10, kernel_initializer='he_normal')) # last layer
model.add(Activation('softmax'))


# Compile Model
model.compile(optimizer='sgd',
              loss='categorical_crossentropy', 
              metrics=['accuracy'])

# Train Model
print(type(x_train[0]), type(y_train[0]))
history = model.fit(x_train, y_train, 
                    validation_data=(x_val, y_val),
                    epochs=10, 
                    batch_size=512)


# Report Results

print(history.history)
model.predict()