#!/usr/bin/python3

"""
Objective:
Script created to convert a bitmap text file into a header file
for usage. Helps speed up edits I make and to ensure that the correct
bitmap is generated.
"""

def create_list() -> list:
    ret = []  

    with open("../docs/sample.txt") as f:
        data = f.read()

    print("Data has been read in...")
    
    curr_line = 0
    index = 0
    index_offset = -4

    for whole_line in data.split("\n"):
        if(whole_line == ''):
            curr_line += 1
            continue

        if ((curr_line % 9) == 0):
            index_offset += 4

        for line in whole_line.split():
            if (index > (len(whole_line.split()) - 1)):
                index = 0

            if((curr_line % 9) == 0):
                ret.append([])
                ret[index + index_offset].append([line])
            else:
                ret[index + index_offset].append([line])

            index += 1

        # done parsing a line
        curr_line += 1

    return ret

def generate_bitmapping(mapping):
    """
    TODO: will require some playing around with the list returned from
    create_list(). Mapping so far is: ret[ ][ ][0][ ]
                                          ^  ^  ^  ^----- selects character
                                          |  |  |
                                          |  |  ------ static
                                          |  ----- row in character list
                                          ----- character #
    """
    pass

if __name__ == "__main__":
    print("Running")
    bit_dict = create_list()
