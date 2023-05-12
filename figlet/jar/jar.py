class Jar:
    def __init__(self, capacity=12):
        if capacity < 1:
            raise ValueError("Wrong capacity Value")
        self._capacity = capacity
        self._n = 0

    def __str__(self):
        return "🍪" * self._n


    def deposit(self, n):
        if self._n + n > self.capacity:
            raise ValueError('Exceed: capacity')
        self._n += n


    def withdraw(self, n):
        if self._n < n:
            raise ValueError('insufficient: capacity')
        self._n -= n


    @property
    def capacity(self):
        return self._capacity


    @property
    def size(self):
        return self._n


my_jar = Jar()
my_jar.deposit(3)
my_jar.deposit(1)
my_jar.withdraw(1)


print(my_jar)
