def f():
    counter = 0
    def g():
        nonlocal counter
        counter = counter + 1
        return counter
    return g

new_g = f()
print(new_g())
print(new_g())
print(new_g())

