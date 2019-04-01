import torch
import torch.nn as nn
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import torch.nn.functional as F


def draw_plot():
    RESOLUTION = 0.01
    ax.clear()
    x_min, x_max = inputs[:, 0].min()-.5, inputs[:, 0].max() + .5
    y_min, y_max = inputs[:, 1].min()-.5, inputs[:, 1].max() + .5
    xx, yy = torch.meshgrid(torch.arange(x_min, x_max, RESOLUTION), torch.arange(y_min, y_max, RESOLUTION))
    xx, yy = xx.contiguous(), yy.contiguous()
    map = model(torch.from_numpy(np.c_[xx.view(-1), yy.view(-1)])).argmax(dim=1).reshape(xx.shape)
    ax.contourf(xx, yy, map, cmap=plt.cm.coolwarm)
    # ax.axis('off')
    ax.scatter(inputs[:, 0], inputs[:, 1], c=targets, cmap=plt.cm.Paired, edgecolors='black')

NBRE_POINTS = 30
learning_rate = .1
epochs = 100000


def run_epoch(epoch, inputs, targets, model, criterion, optimizer):
    # Feed forward
    outputs = model(inputs)
    loss = criterion(outputs, targets)

    # Backward + optimizer
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    # Log
    if (epoch + 1) % 5 == 0:
        print('Epoch [{}/{}], Loss: {:.4f}'.format(epoch+1, epochs, loss.item()))
        draw_plot()


class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.fc1 = nn.Linear(2, 10)
        self.fc2 = nn.Linear(10, 30)
        self.fc3 = nn.Linear(30, 50)
        self.fc4 = nn.Linear(50, 20)
        self.fc5 = nn.Linear(20, 2)

    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = F.relu(self.fc3(x))
        x = F.relu(self.fc4(x))
        x = self.fc5(x)
        return x


if __name__ == "__main__":
    fig, ax = plt.subplots()

    # inputs = torch.cat((torch.rand(int(NBRE_POINTS/2), 2)+1, torch.rand(int(NBRE_POINTS/2), 2)))
    # targets = torch.tensor([1]*(int(NBRE_POINTS/2)) + [0]*(int(NBRE_POINTS/2)))
    inputs = torch.rand(NBRE_POINTS, 2)
    targets = torch.randint(2, size=(1, NBRE_POINTS))[0]
    print("Data : {}".format(inputs))
    print("Targets : {}".format(targets))

    # model = nn.Linear(2, 4)
    model = Net()

    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adagrad(model.parameters(), lr=learning_rate)

    print("Starting ...")

    ani = animation.FuncAnimation(fig, run_epoch, fargs=(inputs, targets, model, criterion, optimizer), interval=1)
    plt.show()
