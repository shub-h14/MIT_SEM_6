def binary_search(arr, target, low, high):
    if low > high:
        return -1  # target not found

    mid = (low + high) // 2

    if arr[mid] == target:
        return mid  # target found at index mid
    elif arr[mid] > target:
        return binary_search(arr, target, low, mid - 1)  # search left half
    else:
        return binary_search(arr, target, mid + 1, high)  # search right half

if __name__ == "__main__":
    # Take array input from user, space-separated integers
    arr_input = input("Enter sorted array elements separated by spaces: ")
    arr = list(map(int, arr_input.strip().split()))

    # Ask for the target element
    target = int(input("Enter the number to search: "))

    # Perform binary search
    result = binary_search(arr, target, 0, len(arr) - 1)

    if result != -1:
        print(f"Element {target} found at index {result}.")
    else:
        print(f"Element {target} not found in the array.")
