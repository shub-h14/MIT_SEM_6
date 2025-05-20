def reverse_file_content_binary(input_file, output_file):
    try:
        # Read the file as binary
        with open(input_file, 'rb') as f:
            content = f.read()

        # Reverse the bytes
        reversed_content = content[::-1]

        # Write reversed bytes back to output file
        with open(output_file, 'wb') as f:
            f.write(reversed_content)

        print(f"Reversed content saved to '{output_file}'.")

    except FileNotFoundError:
        print(f"Error: '{input_file}' not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Call the function
reverse_file_content_binary("input.txt", "output.txt")
