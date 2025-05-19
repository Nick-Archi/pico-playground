#!/usr/bin/python3

"""
Objective:
Script created to convert a bitmap text file into a header file
for usage. Helps speed up edits I make and to ensure that the correct
bitmap is generated.
"""

def create_list():
    ret = []  

    with open("../docs/sample.txt") as f:
        data = f.read()

    print("Data has been read in...")
    
    curr_line = 0
    index = 0
    index_offset = -4

    for whole_line in data.split("\n"):
        print(f"DEBUG {curr_line}")
        if(whole_line == ''):
            curr_line += 1
            continue

        if ((curr_line % 9) == 0):
            index_offset += 4

        for line in whole_line.split():
            if (index > (len(whole_line.split()) - 1)):
                index = 0

            if((curr_line % 9) == 0):
                ret.append([line])
            else:
                ret[index + index_offset].append([line])

            index += 1

        # done parsing a line
        curr_line += 1

    for entry in ret:
        for line in entry:
            print(line)

if __name__ == "__main__":
    print("Running")
    create_list()
