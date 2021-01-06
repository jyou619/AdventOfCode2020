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
        contains.append((count, child))
        i += 4
    rules[bag] = contains

G = nx.DiGraph()
for bag,contains in rules.items():
    for _,child in contains:
        G.add_edge(child, bag)

def get_bags(type):
    i = 0
    for count, child in rules[type]:
        i += count * get_bags(child)
    return i + 1

print(len(nx.predecessor(G, 'shinygold')) - 1)

print(get_bags('shinygold') - 1)
