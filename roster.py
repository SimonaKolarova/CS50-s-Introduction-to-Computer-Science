from sys import argv, exit
import cs50

# Ensure name of house is provided as a command line argument
if len(argv) != 2:
    print("Missing command line argument.")
    exit(1)
    
# Open populated students database
db = cs50.SQL("sqlite:///students.db")

# Query the students table
query_results = db.execute(
    "SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last ASC, first ASC", argv[1])

# Print the rooster
for i in query_results:
    
    # For students with middle names:
    if i['middle'] == None:
        print(f"{i['first']} {i['last']}, born {i['birth']}")
    
    else:
        print(f"{i['first']} {i['middle']} {i['last']}, born {i['birth']}")