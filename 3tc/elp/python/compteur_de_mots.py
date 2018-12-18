# TD2

# d = {}
#
# with open("/home/rhidra/species-intro.txt") as f:
#     for line in f:
#         for word in line.split(" "):
#
#             if word in d:
#                 d[word] += 1
#             else:
#                 d[word] = 1
#
# for k, v in d.items():
#     print(k, v)

## CORRECTION

histogram = {}

with open("/home/rhidra/species-intro.txt") as f:
    for line in f:
        words = [w.lower() for w in line.split()]
        for word in words:
            for c in "[]{}-_,.;:!?$\"'":
                if c in word: # Nettoyage de word
                    word = word.replace(c, "")
            if word not in histogram:
                histogram[word] = 1
            else:
                histogram[word] += 1

for k in histogram:
    print("{0:20} | {1}".format(k, histogram[k] * "*"))
