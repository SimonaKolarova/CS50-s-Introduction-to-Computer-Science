from cs50 import get_int

# Get integer n from user
n = get_int("Provide a half-pyramid height between 1 and 8: ")

while n < 1 or n > 8:
    n = get_int("Provide a half-pyramid height between 1 and 8: ")

# Construction of pyramid
for i in range(n):

    # Make integer m (resiprocal to n)
    m = n-i-1

    # Print m-related spaces
    for j in range(m):
        print(" ", end="")

    # Print n-related #
    for k in range(i+1):
        print("#", end="")
        
    # Print middle spaces
    print("  ", end="")
    
    # Print n-related #
    for o in range(i+1):
        print("#", end="")
        
    # Print new line
    print("")