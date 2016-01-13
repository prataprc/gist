import re
import sys
import json

obj = []

for line in open(sys.argv[1]).readlines() :
    line = line.strip("\r\t\n")
    if line.startswith("==== StorageStats ====") :
        obj.append([])
        # print("storagestats", obj)
        continue

    m = re.match(r'^==== Index Instance ([0-9]+) ====', line)
    if m != None :
        obj[-1].append([m.groups()[0], []])
        # print("instance", obj)
        continue

    m = re.match(r'^----([a-zA-Z0-9\[\]]+)----', line)
    if m != None :
        obj[-1][-1][1].append([m.groups()[0], []])
        # print("block", obj)
        continue

    m = re.match(r'^([a-zA-Z0-9_]+)[ ]+=[ ]+([0-9+\-.]+)', line)
    if m != None :
        obj[-1][-1][1][-1][1].append(m.groups())
        # print("kv", obj)
        continue

stats = [
    dict([(i, dict([(n, dict(ys)) for n, ys in xs])) for i, xs in stat])
    for stat in obj ]
print(json.dumps(stats))
