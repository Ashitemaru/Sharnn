import subprocess
import sys
import os
from math import log2, floor
from shutil import copy

input_file = 'sample.out'

size =  os.path.getsize(input_file) * 8

block_size = 80

prelude = f"""
0
{input_file}
0
"""

n_size = 1_500_000

# adjust the size of n
# according to requirements 
# specified in the documentation
n = {
    2: block_size * 100,
    8: block_size * 100,
    10: 3_000_000,
}

# test parameters
tests = {
    2: f"""
        1
        {block_size}
        0
        """,
    8: f"""
        0
        """,
    9: f"""
        1
        10
        0
        """,
    11: f"""
        1
        {floor(log2(n_size)) - 5 - 1}
        0
        """,  # m < floor(log_2 n) - 2
    14: f"""
        1
        {floor(log2(n_size)) - 2 - 1}
        0
        """,  # m < floor(log_2 n) - 2
    15: f"""
        1
        1000
        0
        """,
}

def evaluate(test_id: int):
    
    choice = "0" * (test_id - 1) + "1" + "0" * (15 - test_id)
    num_streams = n[test_id] if test_id in n else n_size
    input_s = f"""
    {prelude}
    {choice}
    {tests[test_id] if test_id in tests else ""}
    {size // num_streams} 
    1
    
    """
    print("Total bits:", size)
    print("Bits in a single stream:", num_streams)
    print("Total Streams:", size // num_streams)
    print(input_s)
    p = subprocess.run(['./assess', str(num_streams)], input=input_s ,encoding='ascii')
    print(p.returncode, p.stdout)
    copy("experiments/AlgorithmTesting/finalAnalysisReport.txt", f"report_{test_id}.txt")

if __name__ == "__main__":
    for i in range(1, 16):
        evaluate(i)