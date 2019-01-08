class CaesarCypher:
    __init__(self, key):
        #print("init")
        print(string.ascii_uppercase)
        self.key = key

    def encrypt(self, s):
        #pass
        #raise NotImplementedError()
        for char in s:
            print(shift(char, self.key)) 

    def decrypt(self, s):
        #pass
        #raise NotImplementedError()
        for char in s:
            print(shift(char, self.key*-1))

    def shift(self, char, key):
        if ord(char) + key > 90:
            num = chr(64) + key
        if ord(char) + key < 65:
            num = chr(91) + key
        else num = ord(char) + key
    return num
             
        
