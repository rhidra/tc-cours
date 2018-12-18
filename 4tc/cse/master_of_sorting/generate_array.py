"""
    generate_array.py

    Useful file to compare different sorting algorithms
    implemented in sort.c.
    Use matplotlib librairies to display a graph of the performances.
    Can print all the results in a CSV file.
    Store the results in output_random.csv or output_reversed.csv.
    To generate the graph, run the show_graph(file) function, using
    ipython3, for instance, with "%load generate_array.py".

    Author : Rémy Hidra

    2018/2019
"""
## Parameters
# Limit of running time before stopping the tests for an algorithm
limit = 0
# Sorting decreasingly the input array ?
reversed_array = False
# Averaging the running time ?
mean_size = 5
# Which algorithm to use ?
algorithms = [4]

import os
import sys
import random
import subprocess
from functools import reduce
from math import log, floor
from matplotlib import pyplot as plt
import matplotlib

# Generate an input file for the algorithm
def generate_file(name, l):
    with open(name, 'w') as file:
        file.write(str(len(l))+' ')
        for i in l:
            file.write(str(i)+' ')

# Write a list in an output file
# Can only write the result of only one algorithm on one line
def write_output(name, results, algo_index=None):
    with open(name, 'w+' if algo_index == None else 'r+') as file:
        if algo_index == None:
            for l in results:
                for i in l:
                    file.write(str(i)+' ')
                file.write('\n')
        else:
            data = file.read()
            file.seek(0, os.SEEK_SET)
            for i in range(5):
                if i == algo_index:
                    for i in results:
                        file.write(str(i)+' ')
                    file.write('\n')
                elif len(data.split('\n')) > i:
                    file.write(data.split('\n')[i] + '\n')
                else:
                    file.write('\n')

# Utility function to run a shell command
def run_command(*cmd):
    r = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    s = r.stdout.decode('utf-8')
    return s

# Return the running time computed by the algorithm in an output file
def get_running_time(path):
    with open(path, 'r') as file:
        for _ in range(3):
            file.readline()
        s = file.readline()
        print(float(s))
        return float(s)

# Test one of the algorithm with different inputs
def test_algo(algo=1):
    for index in range(300):
        size = 10000
        generate_file('input.txt', [random.randint(-1000, 1000) for _ in range(size)])
        run_command('./mp2_20180326', 'input.txt', str(algo))
        l = get_sorted_list('result_{}_input.txt'.format(algo))
        if is_sorted(l):
            print("OK %d"%index)
        else:
            print("\nERROR !!!!!")

# Return the sorted list computed by the algorithm, in an output file
def get_sorted_list(path):
    with open(path, 'r') as file:
        for _ in range(4):
            file.readline()
        s = file.readline()
        return list(map(lambda x: int(x), s.split(' ')[:-1]))

# Check if a list is sorted
def is_sorted(l):
    return all(l[i] <= l[i+1] for i in range(len(l)-1))

# Display a graph from a CSV file
# Can be run independantely of the main part
def show_graph(path="output.csv"):
    # matplotlib.rcParams['toolbar'] = 'None'
    # plt.style.use('dark_background')
    # fig = plt.figure()
    # fig.patch.set_facecolor('#1D1F21')
    with open(path, 'r') as file:
        x = list(map(lambda e: int(e), file.readline()[:-2].split(' ')))
        algo = []
        for algo_index in [1,2,3,4]:
            values = list(map(lambda e: float(e), file.readline()[:-2].split(' ')))
            plt.plot(x[:len(values)], values, linestyle='solid', marker='.',
                linewidth='.7', label=['Insertion sort', 'Quick sort', 'Merge sort', 'Introsort'][algo_index-1])

        # plt.title('Running time for different sorting algorithms using random arrays')
        plt.title('Running time for different sorting algorithms using arrays sorted in non-increasing order')
        plt.xlabel('Array size')
        plt.ylabel('Running Time (in ms)')
        plt.xscale('log')
        plt.yscale('log')
        plt.legend(loc='bottom right')
        plt.show()

if __name__ == '__main__':
    # Input sizes
    x = [int(2**(i/2)) for i in range(1, 40)]

    results = []
    filename = "output_reversed.csv" if reversed_array else "output_random.csv"
    write_output(filename, x, algo_index=0)
    results.append(x)
    for algo in algorithms:
        print("### Algorithm {} ###".format(algo))
        values = []
        for size in x:
            v = []
            for _ in range(mean_size):
                print("Running time (size={}) : \t".format(size), end='')

                # Generate input
                if not reversed_array:
                    generate_file('input.txt', [random.choice(range(-10, 20)) for _ in range(size)])
                else:
                    generate_file('input.txt', list(reversed(sorted([random.choice(range(-10, 20)) for _ in range(size)]))))

                # Run sort algorithm
                run_command('./mp2_20180326', 'input.txt', str(algo))

                # Get the running time
                v.append(get_running_time('result_{}_input.txt'.format(algo)))

                # Stop if one value is above the limit
                if limit > 0 and v[-1] > limit:
                    break

            # Mean compute
            values.append(reduce(lambda a, b: a+b, v)/len(v))

            # Partial save of the result (in case the program crash)
            if algo == 1:
                write_output(filename, values, algo_index=algo)
            if limit > 0 and values[-1] > limit:
                break

        # Save the results of the algorithm in the output file
        write_output(filename, values, algo_index=algo)
        results.append(values)

    # Save the results of each algorithm
    # write_output('output.csv'.format(algo), results)
