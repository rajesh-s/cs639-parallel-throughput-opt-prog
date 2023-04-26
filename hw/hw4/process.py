#!/usr/bin/env python3
import re
import sys

filename = sys.argv[1] # specify the filename

with open(filename, 'r') as file:
    lines = file.readlines()
    elapsed_times = []
    for line in lines:
        match = re.search(r'\[Elapsed time : (\d+\.\d+)ms\]', line)
        if match:
            elapsed_time = float(match.group(1))
            elapsed_times.append(elapsed_time)
    if elapsed_times:
        min_elapsed_time = min(elapsed_times)
        print("File Name: {}".format(filename))
        print("Lower Elapsed Time: {}ms".format(min_elapsed_time))
    else:
        print("No elapsed times found in the file.")