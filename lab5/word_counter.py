import sys

words = sys.stdin.read().split()
#word = lines.split(" ") ; word
print("Number of words:{}".format(len(words)))
count = [0] * 256

for word in words: count[len(word)] += 1

for i, c in enumerate(count):
    if c > 0: print("Word length: {:02} = {}".format(i, c))
