#!/usr/bin/env python3

import argparse
import re


def print_tests(positive,negative):
    print("Your regex must completely match: {}".format(positive))
    print("Your regex must NOT match: {}".format(negative))

def main():
    parser = argparse.ArgumentParser("Tester program for SENG 265 - Lab 8")
    parser.add_argument('--regex', help='Regex pattern to test (make sure this is in quotes \"\"')
    parser.add_argument('-e', '--exercise', type=int, choices=[0,1,2,3], help='Exercize number')
    parser.add_argument('--no-run', action='store_true', help="Only print the positive and negative samples")
    args = parser.parse_args()


    if args.exercise == 0:
        #solution 1 : '^#?[0-9a-fA-F]{3}([0-9a-fA-F]{3})?$'
        #solution 2 (using lookahead): ^#?(?=[\da-fA-F]*$)(?:.{3}|.{6})$
        positive = ["#fff", "#FFFFFF", "#abc123", "abc123", "#123456", "123456"]
        negative = ["#abH", "#1234567", "1234", "#1234"]
    if args.exercise == 1:
        #solution: .*?p[oai ]t.*
        positive=["pit","spot", "spate", "slap two", "respite"]
        negative=["pt","Pot", "peat", "part"]
    elif args.exercise == 2:
        #solution: .*(ap)[^pd].* 
        positive=["rap them", "tapeth", "apth", "wrap/try", "sap tray", "87ap9th", "apothecary"] 
        negative=["aleht", "happy them", "tarpth", "Apt", "peth", "tarreth", "ddapdg", "apples"]
    
    elif args.exercise == 3:
        #solution: .*(ap)[^pd]e?(?! ).* 
        positive=["rap them", "tapeth", "apth", "wrap/try", "sap tray", "87ap9th", "apothecary"]
        negative=["aleht", "happy them", "tarpth", "Apt", "peth", "tarreth", "ddapdg", "apples", "shape the"]
        
    if args.no_run:
        print_tests(positive,negative)
    else:
        regex = re.compile(args.regex)
        run_test_suite(regex,positive,negative) 

def run_test_suite(regex, positive=[], negative=[]):
    print("\nRESULTS")
    print("="*25)

    """
    #Python 3.5+
    pos_ex = { str_ : True for str_ in positive }
    neg_ex = { str_ : False for str_ in negative }
    test_strs = {**pos_ex, **neg_ex} 
    """
    
    #Python 2,3.4
    test_strs = { str_ : True for str_ in positive }
    test_strs.update({ str_ : False for str_ in negative })
    
    for haystack, result in test_strs.items():
        m = re.search(regex, haystack)
        str_m = m.group() if m is not None else "(None)"
        if bool(m) == result:
            print("   Passed {:<15} = {:<10}".format(haystack, str_m))
        else:
            print("!! FAILED {:<15} = {:<10}".format(haystack, str_m))


if __name__=='__main__':
    main()
