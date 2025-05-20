class SubsetsGenerator:
    def __init__(self, nums):
        self.nums = nums
        self.result = []

    def generate_subsets(self):
        self.result = []
        self._backtrack(0, [])
        return self.result

    def _backtrack(self, index, path):
        self.result.append(path.copy())
        for i in range(index, len(self.nums)):
            path.append(self.nums[i])
            self._backtrack(i + 1, path)
            path.pop()

if __name__ == "__main__":
    # Take input from user: distinct integers separated by spaces
    user_input = input("Enter distinct integers separated by spaces: ")
    nums = list(map(int, user_input.strip().split()))

    generator = SubsetsGenerator(nums)
    subsets = generator.generate_subsets()

    print("All unique subsets:")
    print(subsets)
