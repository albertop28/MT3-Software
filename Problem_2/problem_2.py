import numpy as np

class car:
    def __init__(self, name, location1, location2, r=True, l=True, u=True, d=True): #right, left, up and down are free?
        self.name = name
        self.location1 = location1
        self.location2 = location2
        self.r = r
        self.l = l
        self.u = u
        self.d = d
    
    # Detect orientation:
    def self_orientation(self):
        if self.location1[0] == self.location2[0]:  # Misma fila, está horizontal
            self.u = False
            self.d = False
        elif self.location1[1] == self.location2[1]:  # Misma columna, está vertical
            self.l = False
            self.r = False

    def __str__(self):
        orientation = 'Horizontal' if self.location1[0] == self.location2[0] else 'Vertical'
        return (f"Coche {self.name}: Posiciones: {self.location1} y {self.location2}, "
                f"Orientación: {orientation}, "
                f"Derecha: {self.r}, Izquierda: {self.l}, "
                f"Arriba: {self.u}, Abajo: {self.d}")

# Objects creation
def objects_creation(car_positions):
    coches = {}
    for car_key, car_pos in car_positions.items():
        coche = car(name = car_key, location1 = car_pos[0], location2 = car_pos[1])
        coche.self_orientation()
        coches[car_key] = coche 
    return coches

# Maping Junk car park matrix
def find_positions(grid):
    car_positions = {}
    empty_position = []
    blocked_position = []

    for r in range(grid.shape[0]):
        for c in range(grid.shape[1]):
            value = grid[r, c]
            if value == -1:
                empty_position.append((r, c))
            elif value == -2:
                blocked_position.append((r, c))
            elif value >= 0:
                if value not in car_positions:
                    car_positions[value] = [(r, c)]
                else:
                    car_positions[value].append((r, c))

    return car_positions, empty_position, blocked_position

#Verify slot to free positions is inbounds
def is_within_bounds(pos, matrix):
    rows, cols = matrix.shape
    r, c = pos
    return 0 <= r < rows and 0 <= c < cols

# Mueve un coche en la dirección especificada si es posible
def move_car(coche, direction, car_park_matrix, empty_positions):
    deltas = {'r': (0, 1), 'l': (0, -1), 'u': (-1, 0), 'd': (1, 0)}
    if direction not in deltas:
        return False
    delta = deltas[direction]

    # Calcula nuevas posiciones para el coche
    new_pos1 = (coche.location1[0] + delta[0], coche.location1[1] + delta[1])
    new_pos2 = (coche.location2[0] + delta[0], coche.location2[1] + delta[1])

    # Verifica que ambas posiciones estén vacías y dentro de los límites
    if new_pos1 in empty_positions and new_pos2 in empty_positions and is_within_bounds(new_pos1, car_park_matrix) and is_within_bounds(new_pos2, car_park_matrix):
        # Actualiza la matriz y las posiciones vacías
        empty_positions.remove(new_pos1)
        empty_positions.remove(new_pos2)
        empty_positions.append(coche.location1)
        empty_positions.append(coche.location2)

        # Actualiza las posiciones del coche
        coche.location1 = new_pos1
        coche.location2 = new_pos2
        return True
    return False

# Búsqueda para liberar el espacio objetivo
def free_slot(slot_pos, coches, empty_positions, car_park_matrix):
    visited = set()
    # queue = [(coches, empty pos, movements)]
    queue = [(coches, empty_positions, [])]

    while queue:
        current_coches, current_empty_positions, moves = queue.pop(0)  # Pop al inicio para simular FIFO (BFS)

        # verify if slot is already free
        if slot_pos in current_empty_positions:
            if not moves:
                print("already free")
            else:
                print("Moves", moves)
            return

        # update matrix status
        state_key = (frozenset((k, v.location1, v.location2) for k, v in current_coches.items()), frozenset(current_empty_positions))
        if state_key in visited:
            continue
        visited.add(state_key)

        # Directions w permission
        for car_key, coche in current_coches.items():
            directions = []
            if coche.r: directions.append('r')
            if coche.l: directions.append('l')
            if coche.u: directions.append('u')
            if coche.d: directions.append('d')

            for direction in directions:
                # Clone
                new_coches = {k: car(v.name, v.location1, v.location2, v.r, v.l, v.u, v.d) for k, v in current_coches.items()}
                new_empty_positions = current_empty_positions[:]
                new_car_park_matrix = car_park_matrix.copy()
                
                if move_car(new_coches[car_key], direction, new_car_park_matrix, new_empty_positions):
                    queue.append((new_coches, new_empty_positions, moves + [(car_key, direction)]))

    print("impossible")
    return

def main():
    # Car junk park size:
    entrada = input("Introduce x and y (separated by a space) size of the junk car park:\n")
    cols, rows = map(int, entrada.split())
    car_park_matrix = np.zeros((rows, cols), dtype=int)
    for r in range(rows):
        car_park_matrix[r] = list(map(int, input().split()))

    # Slot to free
    slot_2free = input("Introduce x and y (separated by a space) for the slot to free\n")
    slot_col, slot_row = map(int, slot_2free.split())
    slot_pos = (slot_row - 1, slot_col - 1)

    # Encuentra las posiciones de los coches y los espacios vacíos/bloqueados
    car_positions, empty_positions, blocked_positions = find_positions(car_park_matrix)
    coches = objects_creation(car_positions)
    # for key, coche in coches.items():
    #     print(coche)

    # Try to free the slot
    free_slot(slot_pos, coches, empty_positions, car_park_matrix)

if __name__ == "__main__":
    main()