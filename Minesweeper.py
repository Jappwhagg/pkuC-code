import random

def print_grid(grid):
    for row in grid:
        print(' '.join(row))
    print()

def place_mines(grid, num_mines):
    positions = random.sample(range(len(grid) * len(grid[0])), num_mines)
    for pos in positions:
        row = pos // len(grid[0])
        col = pos % len(grid[0])
        grid[row][col] = '*'
        for i in range(row - 1, row + 2):
            for j in range(col - 1, col + 2):
                if i >= 0 and i < len(grid) and j >= 0 and j < len(grid[0]) and grid[i][j] != '*':
                    grid[i][j] += 1

def reveal_cell(grid, revealed, row, col):
    if (row, col) in revealed:
        return
    revealed.add((row, col))
    if grid[row][col] == 0:
        for i in range(row - 1, row + 2):
            for j in range(col - 1, col + 2):
                if i >= 0 and i < len(grid) and j >= 0 and j < len(grid[0]):
                    reveal_cell(grid, revealed, i, j)

def play_game(rows, cols,num_mines):
    # initialize grid
    grid = [[0 for _ in range(cols)] for _ in range(rows)]
    # place mines
    place_mines(grid, num_mines)
    # initialize revealed cells set
    revealed = set()
    # game loop
    while True:
        # print current grid
        print_grid([['-' if (row, col) not in revealed else str(grid[row][col]) for col in range(cols)] for row in range(rows)])
        # check for win condition
        if len(revealed) == rows * cols - num_mines:
            print("You win!")
            break
        # get user input
        row = int(input("Choose a row: "))
        col = int(input("Choose a column: "))
        # reveal cell
        if grid[row][col] == '*':
            print("You lose!")
            break
        reveal_cell(grid, revealed, row, col)

# example usage
play_game(10, 10, 5)