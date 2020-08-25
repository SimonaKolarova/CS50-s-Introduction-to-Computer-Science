from sys import argv, exit
import cs50

# Ensure name of house is provided as a command line argument
if len(argv) != 2:
    print("Missing command line argument.")
    exit(1)
    
# Open populated students database
db = cs50.SQL("sqlite:///students.db")

# Query the students table
query_results = db.execute("SELECT first_name, middle_name, last_name, birth FROM students WHERE house = ? ORDER BY last_name ASC, first_name ASC", argv[1])

# Print the rooster
for i in query_results:
    
    # For students with middle names:
    if i['middle_name'] == None:
        print(f"{i['first_name']} {i['last_name']}, born {i['birth']}")
    
    else:
        print(f"{i['first_name']} {i['middle_name']} {i['last_name']}, born {i['birth']}")