from cs50 import get_string

# Get user input
user_text = get_string("Please type in the text you want assessed: ")

# Count the number of letters, sentences and words
letters = 0
sentences = 0
words = 1

for i in user_text:
    if i.isalpha():
        letters += 1
    elif(i == "." or i == "!" or i == "?"):
        sentences += 1
    elif i == " ":
        words += 1
    
# Calculate the Coleman-Liau index
CL_index = (0.0588 * 100 * letters / words) - (0.296 * 100 * sentences / words) - 15.8

if CL_index >= 1 and CL_index <=16:
    print(f"Grade {round(CL_index)}")
elif CL_index <1:
    print("Before Grade 1")
else:
    print("Grade 16+")

