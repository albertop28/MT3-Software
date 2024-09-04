import random

# Listas de nombres y apellidos comunes
first_names = [
    "Adriana", "Alejandro", "Alejandra", "Ana", "Antonio", "Arturo", "Beatriz", "Carlos", "Carmen", "Claudia",
    "David", "Fernando", "Francisco", "Gabriela", "Gustavo", "Hugo", "Isabel", "Javier", "Jessica", "Jorge",
    "José", "Luis", "Laura", "Marta", "María", "Miguel", "Néstor", "Óscar", "Pamela", "Raúl", "Ricardo",
    "Sandra", "Silvia", "Sofía", "Vanessa"
]

last_names = [
    "Ávila", "Bermúdez", "Cordero", "Cruz", "Delgado", "Flores", "Figueroa", "García", "Gómez", "González",
    "Guerrero", "Hernández", "López", "Mendoza", "Molina", "Montoya", "Navarro", "Orozco", "Paredes", "Ponce",
    "Ramírez", "Rangel", "Reyes", "Rivas", "Ruiz", "Salazar", "Sánchez", "Serrano", "Torres", "Valdez", "Vargas",
    "Velázquez", "Vega", "Vega", "Zúñiga"
]

def generate_unique_names(num_names):
    # Genera una lista de nombres completos únicos aleatorios.
    # num_names: Número de nombres completos únicos a generar
    # return: Lista de nombres completos únicos
    if num_names > len(first_names) * len(last_names):
        print(f'El número de valores es superior a los {len(first_names)} * {len(last_names)} datos')
        raise ValueError("El número de nombres solicitados excede el número de combinaciones posibles.")

    names_set = {'Nestor Ruiz', 'Pamela Mejia'}
    while len(names_set) < num_names:
        first_name = random.choice(first_names)
        last_name = random.choice(last_names)
        if len(first_name) + len(last_name) + 1 < 20:
            full_name = f'{first_name} {last_name}'
            names_set.add(full_name)

    return list(names_set)

def main():
    num_names = int(input("Introduce el número de nombres únicos a generar: "))

    print(f"\nGenerando {num_names} nombres completos...")

    unique_names = generate_unique_names(num_names)
    
    print("\nNombres generados:")
    for index, name in enumerate(unique_names):
        print("{",f'{index+1}, "{name}", 0', "},")

if __name__ == "__main__":
    main()
