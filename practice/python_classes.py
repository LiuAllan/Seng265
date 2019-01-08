class Student:
    def __init__(self, n, a):
        self.full_name = n
        self.age = a
    def get_age(self):
        return self.age
    def set_age(self, num):
        self.age = num

class Sample:
    x = 23
    def increment(self):
        self.__class__.x += 1

a = Sample()
a.increment()
print(a.__class__.x)


x = Student("bob", 23)
x.age = 14
print(getattr(x, "get_age")())
print(x.full_name)
