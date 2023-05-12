#ccontinues asks user for valid input
while True:
    height = input("Height: ")
    if ((height.isdigit() == True) and (int(height) >= 1) and (int(height) <= 8)):
        break

height = int(height)
# prints dots and hashes
for i in range(height):
    for j in range(height - i - 1):
        print(" ", end="")
    for j in range(i + 1):
        print("#", end="")
    print("")