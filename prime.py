import pandas as pd

# Open csv file

# Find all prime numbers in given range
# https://stackoverflow.com/questions/11619942/print-series-of-prime-numbers-in-python

primes = {}
for num in range(1,10000):
    if all(num%i!=0 for i in range(2,num)):
       primes[len(primes) + 1] = num
#print(primes)
prime_dataframe = pd.DataFrame(list(primes.items()), columns = ["INDEX", "PRIME"])
prime_dataframe.to_csv("./prime_numbers.csv", index=False)
