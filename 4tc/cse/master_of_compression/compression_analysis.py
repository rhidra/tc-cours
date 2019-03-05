"""
    compression_analysis.py

    Author : Rémy Hidra

    2018/2019
"""

import os
import sys
import random
import subprocess
import filecmp
import numpy as np
from functools import reduce
from math import log, floor
from matplotlib import pyplot as plt
import matplotlib

# Generate an input file for the algorithm
# using a dictionnary {symbol: probability, ...}
def generate_file(name, prob, size):
    with open(name, 'w') as file:
        l = list(np.random.choice([chr(a) for a in range(ord('a'), ord('a')+len(prob))], size, p=prob))
        for i in l:
            file.write(str(i))

# Write a tuple results at the end of an output file
def write_output(name, results):
    with open(name, 'r+') as file:
        file.seek(0, os.SEEK_END)
        file.write("{} {} {} {} {} {}\n".format(results[0], results[1], results[2], results[3], results[4], results[5]))

# Utility function to run a shell command
def run_command(*cmd):
    r = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    s = r.stdout.decode('utf-8')
    return s

# Run the compression algorithm in different conditions
def test_algo():
    for depth in [5, 10, 100, 250]:
        for index in range(1, 1000):
            size = index * 100
            generate_file('input.txt', np.random.dirichlet(np.ones(depth),size=1)[0], size)
            run_command('./mp3_20180326', '-c', 'input.txt')
            run_command('./mp3_20180326', '-d', 'input.txt.zz')
            if not check_identical('input.txt', 'input.txt.zz.yy'):
                print("ERREUR !!!!!!!")
                exit()
            size1 = file_size('input.txt')
            size2 = file_size('input.txt.zz')
            entropy1 = entropy('input.txt')
            entropy2 = entropy('input.txt.zz')
            results = (depth, size, size1, size2, entropy1, entropy2)
            print(results)
            write_output('output.csv', results)

# Check if two files are identical
def check_identical(file1, file2):
    return filecmp.cmp(file1, file2)

# Return the file size in bytes
def file_size(path):
    return os.stat(path).st_size

# Display a graph from a CSV file
# Can be run independantely of the main part
def show_graph(path="output.csv"):
    # matplotlib.rcParams['toolbar'] = 'None'
    # plt.style.use('dark_background')
    # fig = plt.figure()
    # fig.patch.set_facecolor('#1D1F21')
    with open(path, 'r') as file:
        depth = []
        size1 = {}
        size2 = {}
        entropy1 = []
        entropy2 = []
        results = []

        for line in file:
            depth_, size_file_, size1_, size2_, entropy1_, entropy2_ = list(map(float, line.split(' ')))
            depth.append(depth_)
            results.append([size1_, size2_, entropy1_, entropy2_])

            if depth_ not in size1:
                size1[depth_] = []
            size1[depth_].append(size1_)
            if depth_ not in size2:
                size2[depth_] = []
            size2[depth_].append(size2_)


        for (d, values1), (_, values2) in zip(size1.items(), size2.items()):
            plt.plot(values1[::20], values2[::20], linestyle='solid', marker='.', linewidth='.7', label="{} different symbols".format(int(d)))
        plt.plot(values1[::100], values1[::100], linestyle='solid', linewidth='.8', label='Uncompressed file')

        plt.title('Comparison of the compressed sizes of different files using a Huffman compression algorithm')
        plt.xlabel('Original size (in bytes)')
        plt.ylabel('Compressed size (in bytes)')
        plt.legend(loc='upper left')
        plt.show()

        mean_factor = 1

        results = sorted(results, key=lambda e: e[0])
        size1 = [e[0] for e in results]
        entropy1 = [e[2] for e in results]
        entropy2 = [e[3] for e in results]

        # plt.plot(size1[::mean_factor], entropy1[::mean_factor], linestyle='None', marker='.', markersize=2, label='Entropy of uncompressed files')
        # plt.plot(size1[::mean_factor], entropy2[::mean_factor], linestyle='None', marker='.', markersize=2, label='Entropy of compressed files')
        # plt.plot(size1[::mean_factor], [8 for _ in range(len(size1[::mean_factor]))], linestyle='solid', linewidth='1', label='Theoritical entropy limit')
        #
        # plt.title('Entropy of different files using a Huffman compression algorithm')
        # plt.xlabel('Original size (in bytes)')
        # plt.ylabel('Entropy')
        # plt.legend(loc='bottom right')
        # plt.show()


def entropy(path):
    with open(path, "rb") as file:
        byte_arr = file.read()
    file_size = len(byte_arr)
    freq = []
    for b in range(256):
        ctr = 0
        for byte in byte_arr:
            if byte == b:
                ctr += 1
        freq.append(float(ctr) / file_size)

    ent = 0.0
    for f in freq:
        if f > 0:
            ent += f * log(f, 2)
    return -ent

if __name__ == '__main__':
    os.system('touch output.csv')
    test_algo()
    show_graph()
