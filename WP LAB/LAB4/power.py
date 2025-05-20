class PowerCalculator:
    def pow(self, x, n):
        # Handle negative exponents
        if n < 0:
            x = 1 / x
            n = -n
        return self._power(x, n)

    def _power(self, x, n):
        if n == 0:
            return 1
        half = self._power(x, n // 2)
        if n % 2 == 0:
            return half * half
        else:
            return half * half * x

# Example usage
if __name__ == "__main__":
    x = float(input("Enter base x: "))
    n = int(input("Enter exponent n: "))

    calc = PowerCalculator()
    result = calc.pow(x, n)
    print(f"{x}^{n} = {result}")
