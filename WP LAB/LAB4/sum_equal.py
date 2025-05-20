class TwoSumFinder:
    def __init__(self, numbers):
        self.numbers = numbers

    def find_pair_with_sum(self, target):
        seen = {}
        for i, num in enumerate(self.numbers):
            complement = target - num
            if complement in seen:
                return seen[complement], i
            seen[num] = i
        return None  # No valid pair found

if __name__ == "__main__":
    # Take list input from the user
    user_input = input("Enter the list of numbers separated by spaces: ")
    numbers = list(map(int, user_input.strip().split()))
    
    # Take target input
    target = int(input("Enter the target sum: "))

    finder = TwoSumFinder(numbers)
    result = finder.find_pair_with_sum(target)

    if result:
        print(f"Pair found at indices: {result[0]}, {result[1]}")
    else:
        print("No pair found with the given target sum.")
