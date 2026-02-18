import pygame
from pygame import mixer
import time  # Ajaviite lisamine

# Pygame ja mikseri initsialiseerimine
pygame.init()
mixer.init()

# Ekraani suuruse määramine
EKRAANX = 1000
EKRAANY = 1000

# Loome Pygame akna
win = pygame.display.set_mode((EKRAANX, EKRAANY))
pygame.display.set_caption("mang")  # Aken saab nimeks "mang"

# Muusika laadimine ja taustal mängima panemine
mixer.music.load("msc/ambient.mp3")
mixer.music.set_volume(0.1)  # Muusika helitugevuse seadistamine
mixer.music.play()

# Pildifailide laadimine ja skaleerimine
taust = pygame.image.load("img/taust.png")
taust = pygame.transform.scale(taust, (EKRAANX, EKRAANY))
vic = pygame.image.load("img/vic.png")
vic = pygame.transform.scale(vic, (EKRAANX, EKRAANY))
ring = pygame.image.load("img/O.png")
ring = pygame.transform.scale(ring, (400, 400))
iks = pygame.image.load("img/X.png")
iks = pygame.transform.scale(iks, (400, 400))
font_big = pygame.font.SysFont('Comic Sans MS', 60)
vic_X = font_big.render("Võitis mängija X", True, (97, 252, 0))
vic_O = font_big.render("Võitis mängija O", True, (97, 252, 0))
# Muudame sisendi lugemist failist
def sisend():
    with open("moves.txt", "r") as file:  # Avame faili lugemiseks
        moves = file.readlines()  # Loeme kõik read
    if moves:
        return int(moves[-1].strip())  # Tagastame viimase rea numbrina
    return None  # Kui fail on tühi, tagastame None


# Käikude joonistamine ekraanile
def kaigud(tehtud):
    ring_coords = {
        11: (0, 0), 12: (325, 0), 13: (600, 0), 14: (0, 350), 15: (325, 350),
        16: (600, 350), 17: (0, 650), 18: (325, 650), 19: (600, 650)
    }
    
    iks_coords = {
        21: (0, 0), 22: (325, 0), 23: (600, 0), 24: (0, 350), 25: (325, 350),
        26: (600, 350), 27: (0, 650), 28: (325, 650), 29: (600, 650)
    }
    
    for el in tehtud:
        if el < 20:
            if el in ring_coords:
                win.blit(ring, ring_coords[el])
        else:
            if el in iks_coords:
                win.blit(iks, iks_coords[el])

# Põhifunktsioon, mis käivitab mängu
def main():
    win.blit(taust, (0, 0))  # Joonistame tausta ekraanile
    pygame.display.update()  # Uuendame ekraani
    tehtud = []  # Käikude loetelu
    run = True  # Mängu tsükkel
    while run:
        pygame.event.get()  # Käsitleme Pygame sündmusi
        win.blit(taust, (0, 0))  # Joonistame tausta ekraanile
        sis = sisend()  # Loeme sisendi failist
        if sis is not None:
            if sis >= 100: # Kontrollime, kas keegi on võitnud
                if sis == 100:  # Kontrollime, kas X mängija on võitnud
                    win.blit(vic, (0, 0))
                    win.blit(vic_X,(250,650))
                    pygame.display.update()
                    run = False
                    time.sleep(7)
                elif sis == 200:  # Kontrollime, kas O mängija on võitnud
                    win.blit(vic, (0, 0))
                    win.blit(vic_O,(250,650))
                    pygame.display.update()
                    run = False
                    time.sleep(7)
            else:
                while sis not in tehtud:  # Kui käik ei ole juba tehtud
                    if sis not in tehtud and sis-10 not in tehtud and sis+10 not in tehtud:
                        tehtud.append(sis)  # Lisame käigu loetellu
                    else:
                        print("koht võetud")
                        time.sleep(1)  # Ootame natuke ja proovime uuesti
                        break
                kaigud(tehtud)  # Joonistame kõik tehtud käigud
                pygame.display.update()  # Uuendame ekraani
        time.sleep(1)  # Ootame natuke enne järgmist kontrolli

if __name__ == "__main__":
    main()  # Käivitame põhifunktsiooni
