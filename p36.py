N = 1000000

def is_palindrome(n):
    n_str = str(n)
    if len(n_str) <= 1:
        return True

    for i in range(len(n_str) // 2):
        if n_str[i] != n_str[len(n_str) - 1 - i]:
            return False
    
    return True

def convert_to_base_2(n):
    if n == 0:
        return "0"

    n_base_2_str = ""

    while n:
        n_base_2_str += str(n % 2)
        n //= 2
    
    return n_base_2_str[::-1]

total = 0
for n in range(N):
    if is_palindrome(n) and is_palindrome(convert_to_base_2(n)):
        total += n

print(total)