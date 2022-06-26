#!/usr/bin/env python3

from argparse import ArgumentParser

import os
import subprocess

EXECUTABLE = os.path.join(os.getcwd(), 'build',
                          'difftool' + ('.exe' if os.name == 'nt' else '') )


def get_test_files(dir):
    left  = []
    right = []
    out   = []

    for file in os.listdir(dir):
        (
                 left  if 'in.left'  in file
            else right if 'in.right' in file
            else out   if 'out'      in file
            else None  # Error
        ).append(file)

    return left, right, out


def run_test(dir, left, right):
    process = subprocess.run( [ EXECUTABLE,
                                os.path.join(dir, left),
                                os.path.join(dir, right)
                              ],
                              stdout=subprocess.PIPE )
    try:
        process.check_returncode()
    except subprocess.CalledProcessError:
        print(f"[{id} FAIL] Program returned non-zero exit code.")
        return False
    else:
        return process.stdout.decode('utf-8')


def check_output(dir, out, id, actual):
    with open(os.path.join(dir, out), 'r') as out_file:
        expected = out_file.read()

        if actual == expected:
            print(f"[{id} PASS]")
        else:
            print(f"[{id} FAIL]  Expected output:", expected,
                  f"[{id} fail] Actual output:", actual, sep='\n')


def main():
    test_dir = os.path.join(os.getcwd(), 'tests')

    left_files, right_files, out_files = get_test_files(test_dir)

    if (len(left_files) != len(right_files) != len(out_files)):
        print("[ERROR] Unequal number of left/right/out files.")
        exit(1)

    for id in range(len(out_files)):
        actual = run_test(test_dir, left_files[id], right_files[id])
        if not actual:
            continue

        check_output(test_dir, out_files[id], id, actual)


if __name__ == '__main__':
    main()
