from keras.models import Sequential
from keras.layers import Dense, Activation
from pandas import DataFrame
import seaborn as sn
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
import numpy as np

# pre-process data
images = np.load('data/images.npy')

num_samples = 6500
num_classes = 10
samples_per_class = int(num_samples/num_classes)

x_train, x_val, x_test = [], [], []
y_train, y_val, y_test = [], [], []

# stratify samples into training, validation, and test
for i in range(num_classes):
    img_class = images[samples_per_class*i:(samples_per_class*(i+1))]
    np.random.shuffle(img_class)
    x_train.extend(img_class[:390])  # first 60% is training
    x_val.extend(img_class[390:488])  # next 15% is validation
    x_test.extend(img_class[488:])  # last 25% is test

    one_hot_v = np.zeros(10)
    one_hot_v[i] = 1
    y_train.extend([one_hot_v, ] * 390)
    y_val.extend([one_hot_v, ] * 98)
    y_test.extend([one_hot_v, ] * 162)

# set lists as numpy arrays
x_train = np.array(x_train)
y_train = np.array(y_train)
x_val = np.array(x_val)
y_val = np.array(y_val)
x_test = np.array(x_test)
y_test = np.array(y_test)


# Model Template
model = Sequential() # declare model
model.add(Dense(5, input_shape=(28*28, ), kernel_initializer='he_normal')) # first layer
model.add(Activation('relu'))
#
#
#
# Fill in Model Here
model.add(Dense(3))
model.add(Activation('selu'))
model.add(Dense(10))
model.add(Activation('selu'))
model.add(Dense(10))
model.add(Activation('relu'))
#
#
model.add(Dense(10, kernel_initializer='he_normal')) # last layer
model.add(Activation('softmax'))


# Compile Model
model.compile(optimizer='sgd',
              loss='categorical_crossentropy', 
              metrics=['accuracy'])

# Train Model
history = model.fit(x_train, y_train,
                    validation_data=(x_val, y_val),
                    epochs=10, 
                    batch_size=512)

y_pred = model.predict(x_test)

# Report Results
# plot training performance
fig, axs = plt.subplots(1,2)
for i, h in enumerate(history.history.items()):
    a = axs[i]
    a.plot(h[1])
    a.set_title(h[0])
    a.set_xlabel("epoch")
    if i == 1: break

fig.tight_layout()
plt.show()

# plot confusion matrix
confm = confusion_matrix(np.argmax(y_test, axis=1), np.argmax(y_pred, axis=1))
df = DataFrame(confm, index=[i for i in range(10)], columns=[i for i in range(10)])
fig, ax = plt.subplots(figsize=(8,8))

ax = sn.heatmap(df, cmap='Oranges', annot=True, linewidths=.5, fmt='g', ax=ax)
plt.title("Confusion Matrix")
plt.xlabel("Predicted")
plt.ylabel("True")
plt.show()

# TODO: 3 visualizations of misclassified images
# TODO: precision and recall calculations
# TODO: write report
# TODO: save best model
