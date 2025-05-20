class StringProcessor:
    def __init__(self):
        self.user_string = ""

    def get_String(self):
        self.user_string = input("Enter a string: ")

    def print_String(self):
        print("String in uppercase:", self.user_string.upper())

# Example usage
if __name__ == "__main__":
    obj = StringProcessor()
    obj.get_String()
    obj.print_String()
