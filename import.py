import csv
from sys import argv, exit
import cs50

# Ensure CSV file is provided as a command line argument
if len(argv) != 2:
    print("Missing command line argument.")
    exit(1)

# Create a SQL database using CSV file provided

# Open CSV file with name, house and birth information 
with open (argv[1], "r") as csv_input:
    reader = csv.DictReader(csv_input)

    # Open empty students database
    db = cs50.SQL("sqlite:///students.db")
    
    # Create students table in students database
    db.execute("CREATE TABLE students (first_name TEXT, middle_name TEXT, last_name TEXT, house TEXT, birth NUMERIC)")

    # Transfer information from CSV file into students.db
    for row in reader: 
        
        #For all students
        name = row["name"].rsplit(' ')
        house = row["house"]
        birth = row["birth"]
        
        # For students with a first, middle and last name
        if len(name) == 3:
            
            # Populate SQL students table
            db.execute("INSERT INTO students (first_name, middle_name, last_name, house, birth) VALUES(?, ?, ?, ?, ?)",
            name[0], name[1], name[2], house, birth)
            
        # For students with a first and last name only
        if len (name) == 2:
        
            # Populate SQL students table
            db.execute("INSERT INTO students (first_name, middle_name, last_name, house, birth) VALUES(?, ?, ?, ?, ?)",
            name[0], None, name[1], house, birth)