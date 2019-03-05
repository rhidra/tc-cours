import torch
import torch.nn as nn
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import torch.nn.functional as F


def draw_plot():
    ax.clear()
    x_min, x_max = inputs[:, 0].min()-.5, inputs[:, 0].max() + .5
    y_min, y_max = inputs[:, 1].min()-.5, inputs[:, 1].max() + .5
    xx, yy = torch.meshgrid(torch.arange(x_min, x_max, 0.001), torch.arange(y_min, y_max, 0.02))
    xx, yy = xx.contiguous(), yy.contiguous()
    map = model(torch.from_numpy(np.c_[xx.view(-1), yy.view(-1)])).argmax(dim=1).reshape(xx.shape)
    ax.contourf(xx, yy, map, cmap=plt.cm.coolwarm)
    # ax.axis('off')
    ax.scatter(inputs[:, 0], inputs[:, 1], c=targets, cmap=plt.cm.Paired)

NBRE_POINTS = 40
learning_rate = .01
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
        self.fc2 = nn.Linear(10, 20)
        self.fc3 = nn.Linear(20, 30)
        self.fc4 = nn.Linear(30, 40)
        self.fc5 = nn.Linear(40, 50)
        self.fc6 = nn.Linear(50, 50)
        self.fc7 = nn.Linear(50, 50)
        self.fc8 = nn.Linear(50, 40)
        self.fc9 = nn.Linear(40, 30)
        self.fc10 = nn.Linear(30, 20)
        self.fc11 = nn.Linear(20, 10)
        self.fc12 = nn.Linear(10, 2)

    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = F.relu(self.fc3(x))
        x = F.relu(self.fc4(x))
        x = F.relu(self.fc5(x))
        x = F.relu(self.fc6(x))
        x = F.relu(self.fc7(x))
        x = F.relu(self.fc8(x))
        x = F.relu(self.fc9(x))
        x = F.relu(self.fc10(x))
        x = F.relu(self.fc11(x))
        x = self.fc12(x)
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

    ani = animation.FuncAnimation(fig, run_epoch, fargs=(inputs, targets, model, criterion, optimizer), interval=1)
    plt.show()
