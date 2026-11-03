import math

gravity = 9.81
distance = 20
impact_radius = 1


def draw_scene():
    print("_" * 80)


def calculate_impact(ang, vel):
    range = vel ** 2 * 2 * math.sin(math.radians(ang)) * \
            math.cos(math.radians(ang)) / gravity
    print("range: ", range)
    return range


def get_input():
    vel = float(input("podaj predkosc w m/s: "))
    while not 0 <= (ang := float(input("podaj kat w stopniach: "))) <= 90:
        print("podany kat jest poza zakresem!")
    return vel, ang


def main():
    draw_scene()
    hit = False
    count = 1
    while not hit:
        player = 0 if count % 2 else 1
        print("Gracz: ", player)
        print("Proba: ", count)
        vel, ang = get_input()
        if (abs(distance - calculate_impact(ang, vel)) <= impact_radius):
            print("Trafiony!")
            print("Wygral gracz: ", player)
            hit = True
        else:
            count += 1
            print("nie trafiles")
    print("Prob koniecznie: ", count)


# vel, ang=get_input()
# print("predkosc: ", vel)
# print("kat: ", ang)

main()