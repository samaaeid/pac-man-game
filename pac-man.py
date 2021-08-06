import random

N, M = 6, 15
counter = 0
a, b = -1, -1
grid = [['+' for x in range(M)] for y in range(N)]


# This function prints the grid of Gomoku as the game progresses
def print_grid():
    print('--' + '---' * M + '--')
    for i in range(N):
        print(end='|  ')
        for j in range(M):
            print(grid[i][j], end='  ')
        print(end='|')
        print()
    print('--' + '---' * M + '--')


# This function checks if the game has a win state or not
def check_win():
    if counter == N * M - (N * M * 1 // 6 + N * M * 1 // 8 + 1):
        return True
    else:
        return False


def check_available_move(i):
    if i == 3:
        if b + 1 > M - 1:
            return False  # right
    elif i == 1:
        if a - 1 < 0:
            return False  # up
    elif i == 2:
        if a + 1 > N - 1:
            return False  # down
    elif i == 4:
        if b - 1 < 0:
            return False  # left
    return True


# This function checks if the game has a tie state or not for the given mark
def check_lose(i):
    if i == 3:
        if grid[a][b + 1] == 'G':
            return True
    elif i == 1:
        if grid[a - 1][b] == 'G':
            return True
    elif i == 2:
        if grid[a + 1][b] == 'G':
            return True
    elif i == 4:
        if grid[a][b - 1] == 'G':
            return True
    return False


def check_wall(i):
    if i == 3:
        if grid[a][b + 1] == '|':
            return True
    elif i == 1:
        if grid[a - 1][b] == '|':
            return True
    elif i == 2:
        if grid[a + 1][b] == '|':
            return True
    elif i == 4:
        if grid[a][b - 1] == '|':
            return True
    return False


def move(i):
    global a
    global b
    global counter
    grid[a][b] = '.'
    if i == 3:  # right
        if grid[a][b + 1] == '+':
            counter += 1
            grid[a][b + 1] = 'P'
        elif grid[a][b + 1] == '.':
            grid[a][b + 1] = 'P'
        b += 1

    elif i == 1:  # up
        if grid[a - 1][b] == '+':
            counter += 1
            grid[a - 1][b] = 'P'
        elif grid[a - 1][b] == '.':
            grid[a - 1][b] = 'P'
        a -= 1

    elif i == 2:  # down
        if grid[a + 1][b] == '+':
            counter += 1
            grid[a + 1][b] = 'P'
        elif grid[a + 1][b] == '.':
            grid[a + 1][b] = 'P'
        a += 1

    elif i == 4:  # left
        if grid[a][b - 1] == '+':
            counter += 1
            grid[a][b - 1] = 'P'
        elif grid[a][b - 1] == '.':
            grid[a][b - 1] = 'P'
        b -= 1


# This function generates pac man
def generate_pac_man():
    global a
    global b
    a = random.randint(0, N - 1)
    b = random.randint(0, M - 1)
    grid[a][b] = 'P'


# This function generates ghosts
def generate_ghost():
    f = N * M * 1 // 6
    while f > 0:
        a = random.randint(0, N - 1)
        b = random.randint(0, M - 1)
        while grid[a][b] == 'P':
            a = random.randint(0, N - 1)
            b = random.randint(0, M - 1)
        grid[a][b] = 'G'
        f -= 1

    # This function generates a wall


def generate_wall():
    f = N * M * 1 // 8
    while f > 0:
        a = random.randint(0, N - 1)
        b = random.randint(0, M - 1)
        while grid[a][b] == 'P' or grid[a][b] == 'G':
            a = random.randint(0, N - 1)
            b = random.randint(0, M - 1)
        grid[a][b] = '|'
        f -= 1


# This function checks if given position is valid or not
def check_valid_direction(i):
    if i == 1 or i == 2 or i == 3 or i == 4:
        return True
    else:
        return False


# This function clears the game structures
def grid_clear():
    global grid
    grid = [['+' for x in range(M)] for y in range(N)]
    global counter
    counter = 0


# This function reads a valid position input
def read_input():
    i = int(input('Enter the direction: '))
    while not check_available_move(i) or not check_valid_direction(i):
        i = int(input('Enter a valid direction: '))
    return i


# MAIN FUNCTION
def play_game():
    print("Pac_Man Game!")
    print("Welcome...")
    print("============================")
    while True:
        # Prints the grid
        print_grid()
        i = read_input()
        # Check if the grid has a tie state
        if check_lose(i):
            # Prints the grid
            print_grid()
            # Announcement of the final statement
            print("GAME OVER!")
            break
        if check_wall(i):
            print("WHATCH OUT you hit a wall !! please ", end=' ')
            i = read_input()
        # Move with the input direction
        move(i)
        # Check if the state of the grid has a win state
        if check_win():
            # Prints the grid
            print_grid()
            # Announcement of the final statement
            print("Congrats, you won!\n")
            break


while True:
    grid_clear()
    generate_pac_man()
    generate_ghost()
    generate_wall()
    play_game()
    c = input('Play Again [Y/N] ')
    if c not in 'yY':
        break
