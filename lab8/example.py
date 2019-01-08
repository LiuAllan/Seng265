
global_var = 5

class ObjectName(object):
    def __init__(self, arg1, argv):
        print(argv)
        argv[0] = "foo"
        pass

    def test_var_args(self, arg1, *argv):
        print(argv)
        argv[0] = "foo"


if __name__ == '__main__':
    
    foo = list(range(1,5))
    obj = ObjectName("test", foo)
    obj.test_var_args("test", *foo)
