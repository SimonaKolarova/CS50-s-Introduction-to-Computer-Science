import csv
from sys import argv, exit

# Import CSV file of individuals' STRs (argv[1]) and DNA sequence of interest (argv[2])
if len(argv) != 3:
    print("Missing command line argument.")
    exit(1)

# Open CSV file
with open(argv[1]) as csvfile:
    DNA_database = list(csv.reader(csvfile))

# Read DNA sequence into memory
unknown_DNA = open(argv[2], "r")
unknown_DNA = unknown_DNA.read()

# Create lists of target STRs and for storing sequential STR results
STR_count = len(DNA_database[0]) - 1
STR_list = []
sequential_STRs = []

for i in range(STR_count):
    STR_list.append(DNA_database[0][i + 1])
    sequential_STRs.append(0)

# Compute longest run of consecutive STR in DNA sequence of interest
# For each STR
for i in range(STR_count):
    j = len(STR_list[i])

    # For each base pair
    for k in range(len(unknown_DNA)):

        # If base pairs+j = STR
        if unknown_DNA[k:(k+j)] == STR_list[i]:
            
            # Count first STR match
            if sequential_STRs[i] == 0:
                sequential_STRs[i] = 1
            
            # Check remaining base pairs for same base pair sequence
            STR_lenghts_left = int((len(unknown_DNA) - k)/j)
            
            for l in range(STR_lenghts_left - 1):
                if unknown_DNA[(k + j + (l * j)):(k + j + ((l + 1) * j))] == STR_list[i]:
                    if (l + 2) > sequential_STRs[i]:
                        sequential_STRs[i] = l + 2
                else:
                    break
                
# Determine match
# For each person in the database
for i in range(len(DNA_database) - 1):
    sum_matches = 0
   
    # For each STR
    for j in range(STR_count):
        
        # Match in first STR
        if int(sequential_STRs[j]) == int(DNA_database[i + 1][j + 1]):
            sum_matches += 1
            
        if sum_matches == STR_count:
            print(f"{DNA_database[i + 1][0]}")
            exit(0)

print("No match")