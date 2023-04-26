#!/bin/bash

# Create or truncate the result file
> result

# Loop through all files in the current directory
for file in *; do
  # Check if the file is a regular file
  if [[ -f "$file" ]]; then
    echo "Processing file: $file"
    # Run the Python script for each file and append the results to the result file
    python <<EOF >> result
import re

filename = "$file"
with open(filename, 'r') as file:
    lines = file.readlines()
    elapsed_times = []
    for line in lines:
        if line.startswith('Running kernel for performance run'):
            match = re.search(r'\[Elapsed time : (\d+\.\d+)ms\]', line)
            if match:
                elapsed_time = float(match.group(1))
                elapsed_times.append(elapsed_time)
    if elapsed_times:
        min_elapsed_time = min(elapsed_times)
        print("File Name: {}".format(filename))
        print("Lower Elapsed Time: {}ms".format(min_elapsed_time))
        print("-----------------------")
    else:
        print("No elapsed times found in the file.")
        print("-----------------------")
EOF
  fi
done

echo "Results written to 'result' file."