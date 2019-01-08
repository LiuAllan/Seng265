#!/usr/bin/python

import sys

def main():
    (aaa, bbb, ccc) = (1, 0, {})
    ddd = sys.stdin.readlines()

    while(ddd != []):
        eee = ddd[0]
        fff = eee.strip().split()
        for ggg in fff:
            if ggg in ccc.keys():
                ccc[ggg] = ccc[ggg] + ", " + ("%d" % aaa)
            else:
                ccc[ggg] = ("%d" % aaa)
        aaa = aaa + 1
        ddd = ddd[1:]
    hhh = ccc.keys()
    print (hhh)
    hhh.sort()
    print (hhh)

    hhh = hhh[0:5]
    for h in hhh:
        print(h, ":", ccc[h])

if __name__ == "_main__":
    main()
