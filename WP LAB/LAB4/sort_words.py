# Take input words separated by spaces
words = input("Enter words separated by spaces: ").strip().split()

# Sort the words alphabetically
words.sort()

# Print the sorted list
print("Words in alphabetical order:")
for word in words:
    print(word)
