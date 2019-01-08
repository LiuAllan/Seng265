import sys
import string


def main():
    wc = {}
    with open(sys.argv[1], "r") as f:
        #print(f.readlines())
        #lines = f.readlines() 
        #word = lines.split()
        for w in f.read().split():
            w = w.strip(string.whitespace + string.punctuation)
            wc[w] = wc[w] + 1 if w in wc else 1

    for w, c in sorted(wc.items(), key=lambda x: x[1], reverse=True)[:11]:
        print("{}: {}".format(w, c))


if __name__ == "__main__":
    main()
