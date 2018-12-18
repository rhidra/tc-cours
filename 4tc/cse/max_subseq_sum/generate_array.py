import os
import sys
import random
import subprocess
from functools import reduce
from math import log, floor
from matplotlib import pyplot as plt
import matplotlib

def generate_file(name, l):
    with open(name, 'w') as file:
        file.write(str(len(l))+' ')
        for i in l:
            file.write(str(i)+' ')


def write_output(name, results):
    with open(name, 'w') as file:
        for l in results:
            for i in l:
                file.write(str(i).replace('.', ',')+'/')
            file.write('\n')


def run_command(*cmd):
    r = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    s = r.stdout.decode('utf-8')
    return s


def get_running_time(path):
    with open(path, 'r') as file:
        for _ in range(6):
            file.readline()
        s = file.readline()
        print(s)
        return float(s)


if __name__ == '__main__':
    limit = 60
    #matplotlib.rcParams['toolbar'] = 'None'
    #plt.style.use('dark_background')
    #fig = plt.figure()
    #fig.patch.set_facecolor('#1D1F21')
    results = []
    #x = [i*10 for i in range(2, 80)]
    x = [floor(log(i*10)**10)+10 for i in range(2, 180)]
    results.append(x)
    for algo in [1,2,3]:
        print("### Algorithm {} ###".format(algo))
        values = []
        for size in x:
            v = []
            for _ in range(1):
                print("Running time (size={}) : \t".format(size), end='')
                generate_file('input.txt', [random.randint(-10, 20) for _ in range(size)])
                run_command('./mss20180326', 'input.txt', str(algo))
                v.append(get_running_time('result_input.txt'))
                if v[-1] > limit:
                    break
            values.append(reduce(lambda a, b: a+b, v)/len(v))
            if values[-1] > limit:
                break
        plt.plot(x[:len(values)], values, linestyle='solid', marker='.',
            linewidth='.7', label=['O(n²)', 'O(n*log(n))', 'O(n)'][algo-1])
        results.append(values)

    plt.title('Running time for different MSS algorithms, using bigger array sizes')
    plt.xlabel('Array size')
    plt.ylabel('Running Time (in ms)')
    plt.xscale('log')
    plt.legend(loc='upper right')
    plt.show()
    #write_output('output.csv'.format(algo), results)
