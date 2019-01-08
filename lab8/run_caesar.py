#!/usr/bin/env python3
from caesar import CaesarCypher
import argparse as ap
import sys
import os

def main():
    parser = ap.ArgumentParser(description="Caesar cipher example")
    group = parser.add_mutually_exclusive_group(required=True);
    group.add_argument('--encrypt', action='store_true')
    group.add_argument('--decrypt', action='store_true')
    args = parser.parse_args()
   
    plain = "THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG"
    encrypted = "WKHTXLFNEURZQIRAMXPSVRYHUWKHODCBGRJ"

    invalid = "ABCED4"
    

    cipher = CaesarCypher(3)
    
    if args.encrypt:
        processed_text = cipher.encrypt(plain)
        if processed_text == encrypted:
            print("Encryption Passed!")
        else:
            print("Failed :(")
            print("Wanted:", encrypted)
            print("Got   :", processed_text)

        try:
            cipher.encrypt(invalid)
        except ValueError as e:
            print("Invalid Input: Passed!")
        except Exception as e:
            print("Invalid Input: Failed")
            print("\tExpected {} but got {}".format(type(ValueError()), type(e)))

    if args.decrypt:
        processed_text = cipher.decrypt(encrypted)
        if processed_text == plain:
            print("Decryption Passed!")
        else:
            print("Failed :(")
            print("Wanted:", plain)
            print("Got   :", processed_text)

        try:
            cipher.decrypt(invalid)
        except ValueError as e:
            print("Invalid Input: Passed!")
        except Exception as e:
            print("Invalid Input: Failed")
            print("\tExpected {} but got {}".format(type(ValueError()), type(e)))


if __name__ == '__main__':
    main()
