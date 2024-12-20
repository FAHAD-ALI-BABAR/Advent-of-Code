# Read the data from the file
with open('data.txt', 'r') as file:
    grid = [list(line.strip()) for line in file if line.strip()]

# Get the dimensions of the grid
rows = len(grid)
cols = len(grid[0])

# Function to check if a point is within the grid bounds
def is_within_bounds(x, y):
    return 0 <= x < rows and 0 <= y < cols

# Dictionary to store the positions of antennas by their frequency
antenna_positions = {}

# Find positions of antennas and categorize them by frequency
for i in range(rows):
    for j in range(cols):
        if grid[i][j] != '.':
            freq = grid[i][j]
            if freq not in antenna_positions:
                antenna_positions[freq] = []
            antenna_positions[freq].append((i, j))

# Set to store unique antinode locations
antinode_locations = set()

# Iterate through pairs of antennas with the same frequency
for freq, positions in antenna_positions.items():
    n = len(positions)
    for i in range(n):
        for j in range(i + 1, n):
            x1, y1 = positions[i]
            x2, y2 = positions[j]
            
            # Check if the antennas are collinear with a valid midpoint
            if x1 == x2:  # Same row
                if (y2 - y1) % 2 == 0:  # Check if the distance is even
                    mid_y = (y1 + y2) // 2
                    if is_within_bounds(x1, mid_y):
                        antinode_locations.add((x1, mid_y))
            elif y1 == y2:  # Same column
                if (x2 - x1) % 2 == 0:  # Check if the distance is even
                    mid_x = (x1 + x2) // 2
                    if is_within_bounds(mid_x, y1):
                        antinode_locations.add((mid_x, y1))

# Print the total number of unique antinode locations
print("Total Number of Unique Antiiiinds:", len(antinode_locations))
