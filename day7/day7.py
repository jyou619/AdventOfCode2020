import networkx as nx

f = open("input.txt", "r")

rules = {}

for line in f:
    line = line.split()
    # Setting bag type
    bag = line[0] + line[1]     # first two words are always the bag type
    contains = []
    i = 4                       # statements are 4 words long

    while i < len(line) and line[i] != 'no' :
        count = int(line[i])
        child = line[i + 1] + line[i + 2]
        contains.append((child, count))
        i += 4
    rules[bag] = contains
