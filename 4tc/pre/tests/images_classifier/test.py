import torch

from network import Net
from data import import_cifar10_testing_data

net = Net()
net.load_state_dict(torch.load("./model.model"))
net.eval()

testloader = import_cifar10_testing_data()

correct = 0
total = 0
with torch.no_grad():
    for data in testloader:
        images, labels = data
        outputs = net(images)
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

print('Accuracy of the network on the 10000 test images: %d %%' % (
    100 * correct / total))
