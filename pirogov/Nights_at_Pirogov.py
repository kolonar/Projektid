import time
import pygame
import math
from pygame import mixer
from random import randint

pygame.init()
mixer.init()
EKRAANX = 1280
EKRAANY = 720
win = pygame.display.set_mode((EKRAANX, EKRAANY)) 
pygame.display.set_caption("Pirogov")
width = 50
height = 50

def movement_x(x,vel):
    global width
    global EKRAANX
    global EKRAANY
    keys = pygame.key.get_pressed() 
    if keys[pygame.K_LEFT] and x>0: 
        x -= vel 
    if keys[pygame.K_RIGHT] and x<EKRAANX-width: 
        x += vel
    return x

def movement_y(y,vel,vähim_y):
    global height
    global EKRAANX
    global EKRAANY
    keys = pygame.key.get_pressed()
    if keys[pygame.K_UP] and y>vähim_y: 
        y -= vel 
    if keys[pygame.K_DOWN] and y<EKRAANY-height: 
        y += vel 
    return y

def pudel_spawn(pudel,pudel_location):
    for n in range(len(pudel_location)):
        win.blit(pudel, pudel_location[n-1])

def restart(kust,kuhu):
    global valik
    keys = pygame.key.get_pressed()
    if keys[pygame.K_SPACE]:
        return kuhu
    else:
        return kust

def lahku_mängust():
    keys = pygame.key.get_pressed()
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            return False
    if keys[pygame.K_ESCAPE]:
        return False
    else:
        return True

def piro_helid():
    for heli in piro_helid:
        time.sleep(randint(2,5))
        mixer.music.load(heli)
        mixer.music.set_volume(1)
        pygame.mixer.Channel(1).play(pygame.mixer.Sound(heli))

def main():
    global width
    global height
    global EKRAANX
    global EKRAANY
    ümbrus = []
    for i in range(30):
        ümbrus.append(i)
    i=0
    x = 640 
    y = 120
    piro_x= randint(50, 500)
    piro_y= randint(450, 600)
    eelmine_piro_x = 140
    eelmine_piro_y = 300
    
    time_all=35
    vel = 6
    eelx = 0
    pudelid = 0
    pudel_all=0
    pudelid = 0
    speed_hind=30
    time_hind=20
    
    with open("parim.txt","r") as f:
        parim_tulemus=int(f.read())
    
    kinnipüütud = 0
    font = pygame.font.SysFont('Comic Sans MS', 30)
    font_big = pygame.font.SysFont('Comic Sans MS', 60)
    pudel = pygame.image.load("img/png/pudel.png")
    pudel = pygame.transform.scale(pudel, (50,50))
    pudel_sml = pygame.image.load("img/png/pudel.png")
    pudel_sml = pygame.transform.scale(pudel, (30,30))
    parim = font.render("Best score: " + str(parim_tulemus), True, (255, 255, 255))
    i=0
    countdown = pygame.image.load("img/jpg/countdown.jpg")
    countdown = pygame.transform.scale(countdown, (EKRAANX,EKRAANY))
    map_img = pygame.image.load("img/jpg/piro_map_timer.jpg")
    map_img = pygame.transform.scale(map_img, (EKRAANX,EKRAANY))
    valgus = pygame.image.load("img/png/lambid.png")
    valgus = pygame.transform.scale(valgus, (EKRAANX,EKRAANY))
    player = pygame.image.load("img/png/player_seisab.png")
    player = pygame.transform.scale(player, (50,50))
    pirokunn = pygame.image.load("img/png/pirokunn.png")
    pirokunn = pygame.transform.scale(pirokunn, (60,60))
    background = pygame.image.load("img/jpg/end_menu.jpg")
    background = pygame.transform.scale(background, (EKRAANX,EKRAANY))
    main_menu = pygame.image.load("img/jpg/main_menu_WIP.jpg")
    main_menu = pygame.transform.scale(main_menu, (EKRAANX,EKRAANY))
    shop = pygame.image.load("img/jpg/shop.jpg")
    shop = pygame.transform.scale(shop, (EKRAANX,EKRAANY))
    nool = pygame.image.load("img/png/nool.png")
    nool = pygame.transform.scale(nool, (50,50))
    versioon = font.render("Nights at Pirogov BETA 1.0", True, (255, 255, 255))
    pudeli_count = font.render("Bottles: " + str(pudelid), True, (255, 255, 255))
    kinnipüütud_pudelid = font.render("Pirokunn stole your bottles!", True, (255, 255, 255))
    blop = mixer.Sound("sounds/effects/blop.mp3")
    blop.set_volume(0.7)
    mixer.music.load("sounds/music/intro.mp3")
    mixer.music.set_volume(1)
    mixer.music.play()
    valik = "0"
    olek = "vasakule"
    piro_olek = "vasakule"
    state = "intro"
    run = True
    while run:
        run = lahku_mängust()
        keys = pygame.key.get_pressed()
        bottles = font.render(str(pudel_all), True, (255, 255, 255))
        if state == "shop":
            velo = font_big.render(str(vel), True, (255, 255, 255))
            aeg_all = font_big.render(str(time_all), True, (255, 255, 255))
            fire = "gifs/fire_gif/fire-" + str(i) + ".png"
            gif = pygame.image.load(fire).convert()
            gif = pygame.transform.scale(gif, (350,350))
            s_hind = font_big.render(str(speed_hind)+"bottles", True, (255, 255, 255))
            t_hind = font_big.render(str(time_hind)+"bottles", True, (255, 255, 255))
            time.sleep(0.1)
            win.blit(shop,(0,0))
            win.blit(gif,(40,210))
            win.blit(s_hind,(880,330))
            win.blit(t_hind,(880,170))
            if valik == "0":
                if movement_y(1,1,0) == 2 or movement_y(1,1,0) == 0:
                    valik = "1"
            elif valik == "1":
                win.blit(nool,(340,170))
                if keys[pygame.K_SPACE] and pudel_all>=time_hind:
                    time_all+=2
                    pudel_all-=time_hind
                    time_hind=round(time_hind*1.2)
                elif movement_y(1,1,0) == 2:
                    valik = "2"
                elif movement_y(1,1,0) == 0:
                    valik = "3"
            elif valik == "2":
                win.blit(nool,(340,340))
                if keys[pygame.K_SPACE] and pudel_all>=speed_hind:
                    vel+=1
                    pudel_all-=speed_hind
                    speed_hind=round(speed_hind*1.3)
                elif movement_y(1,1,0) == 2:
                    valik = "3"
                elif movement_y(1,1,0) == 0:
                    valik = "1"
            elif valik == "3":
                win.blit(nool,(340,490))
                state=restart("shop","intro")
                if movement_y(1,1,0) == 0:
                    valik = "2"
                elif movement_y(1,1,0) == 2:
                    valik = "1"
            i+=1
            if i >= 9:
                i = 0
            win.blit(velo,(420,320))
            win.blit(aeg_all,(420,170))
            if state == "intro":
                valik="0"
        elif state == "intro":
            kinnipüütud = 0
            fire = "gifs/fire_gif/fire-" + str(i) + ".png"
            gif = pygame.image.load(fire).convert()
            gif = pygame.transform.scale(gif, (350,350))
            time.sleep(0.1)
            win.blit(main_menu,(0,0))
            win.blit(gif,(40,210))
            if valik == "0":
                if movement_y(1,1,0) == 2 or movement_y(1,1,0) == 0:
                    valik = "1"
            elif valik == "1":
                win.blit(nool,(340,170))
                state = restart("intro","game")
                if movement_y(1,1,0) == 2:
                    valik = "2"
                elif movement_y(1,1,0) == 0:
                    valik = "3"
            elif valik == "2":
                win.blit(nool,(340,340))
                state=restart("intro","shop")
                if movement_y(1,1,0) == 2:
                    valik = "3"
                elif movement_y(1,1,0) == 0:
                    valik = "1"
            elif valik == "3":
                win.blit(nool,(340,490))
                if keys[pygame.K_SPACE]:
                    run = False
                if movement_y(1,1,0) == 0:
                    valik = "2"
                elif movement_y(1,1,0) == 2:
                    valik = "1"
            i+=1
            if i > 9:
                i = 0
            if state == "game":
                loc = 0
                x=640
                y=120
                mixer.music.stop()
                mixer.music.load("sounds/music/game.mp3")
                mixer.music.set_volume(1)
                pygame.mixer.Channel(0).play(pygame.mixer.Sound("sounds/music/game.mp3"))
                mixer.music.load("sounds/effects/Piro_helid.mp3")
                mixer.music.set_volume(1)
                pygame.mixer.Channel(1).play(pygame.mixer.Sound("sounds/effects/Piro_helid.mp3"))
                pudel_location = []
                pudeli_count = font.render("Bottles: " + str(pudelid), True, (255, 255, 255))
                if olek == "vasakule":
                    player = pygame.transform.flip(player, True, False)
                    olek="paremale"
                j=3
                for i in range(3):
                    timer = font_big.render(str(j-i), True, (255, 255, 255))
                    win.blit(countdown, (0, 0))
                    win.blit(timer,(640,360))
                    pygame.display.update()
                    time.sleep(1)
                uus_aeg=time.time()
                while loc < randint(3,11):
                    pudel_location.append((randint(200,1000), randint(200,520)))
                    loc+=1
            elif state == "shop":
                valik="0"
        
        elif state == "menu":
            i=0
            pudelid = 0
            pygame.mixer.Channel(0).stop()
            pygame.mixer.Channel(1).stop()
            pygame.draw.rect(win, (255,255,255), pygame.Rect(0, 0, EKRAANX, EKRAANY))
            parim = font.render("Best score: " + str(parim_tulemus), True, (255, 255, 255))
            win.blit(background,(0,0))
            if valik == "1":
                win.blit(nool,(340,430))
                state = restart("menu","game")
                if movement_y(1,1,0) == 2 or movement_y(1,1,0) == 0:
                    valik = "2"
            elif valik == "2":
                win.blit(nool,(340,550))
                state = restart("menu","intro")
                if movement_y(1,1,0) == 2 or movement_y(1,1,0) == 0:
                    valik = "1"
            if kinnipüütud == 1:
                win.blit(kinnipüütud_pudelid, (450,140))
            else:
                win.blit(pudeli_count, (555,140))
            win.blit(parim, (510,300))
            time.sleep(0.1)
            if state == "game":
                valik = "0"
                x = 640
                y = 120
                mixer.music.stop()
                mixer.music.load("sounds/music/game.mp3")
                mixer.music.set_volume(1)
                pygame.mixer.Channel(0).play(pygame.mixer.Sound("sounds/music/game.mp3"))
                mixer.music.load("sounds/effects/Piro_helid.mp3")
                mixer.music.set_volume(0.7)
                pygame.mixer.Channel(1).play(pygame.mixer.Sound("sounds/effects/Piro_helid.mp3"))
                mixer.music.play()
                kinnipüütud = 0
                pudelid = 0
                pudel_location = []
                pudeli_count = font.render("Bottles: " + str(pudelid), True, (255, 255, 255))
                if olek == "vasakule":
                    player = pygame.transform.flip(player, True, False)
                    olek="paremale"
                while loc < randint(2,11):
                    pudel_location.append((randint(200,1000), randint(200,520)))
                    loc+=1
                j=3
                for i in range(3):
                    timer = font_big.render(str(j-i), True, (255, 255, 255))
                    win.blit(countdown, (0, 0))
                    win.blit(timer,(640,360))
                    pygame.display.update()
                    time.sleep(1)
                uus_aeg=time.time()
            elif state=="intro":
                valik="1"
        
        elif state == "game":
            aeg = round(time.time()) - round(uus_aeg)
            aeg_count = font.render("Time: " + str(time_all-aeg), True, (255, 255, 255))
            i = 0
            j = 0
            loc = 0
            x = movement_x(x,vel)
            y = movement_y(y,vel,80)
            
            if x != eelx:
                if x > eelx:
                    if olek == "vasakule":
                        player = pygame.transform.flip(player, True, False)
                    olek = "paremale"
                if x < eelx:
                    if olek == "paremale":
                        player = pygame.transform.flip(player, True, False)
                    olek = "vasakule"
                eelx=x
            
            if piro_x < x:
                piro_x += 1.3
                if piro_olek == "paremale":
                    pirokunn = pygame.transform.flip(pirokunn, True, False)
                piro_olek = "vasakule"
            if piro_x > x:
                piro_x -= 1.3
                if piro_olek == "vasakule":
                    pirokunn = pygame.transform.flip(pirokunn, True, False)
                piro_olek = "paremale"
            if piro_y < y:
                piro_y += 1.3
            if piro_y > y:
                piro_y -= 1.3
            
            for i in ümbrus:
                for j in ümbrus:
                    if (x-25+i,y-25+j) in pudel_location:
                        mixer.Sound.play(blop)
                        pudel_location.pop(pudel_location.index((x-25+i,y-25+j)))
                        pudelid+=1
                        pudeli_count = font.render("Bottles: " + str(pudelid), True, (255, 255, 255))
                    if (x+25-i,y+25-j) in pudel_location:
                        mixer.Sound.play(blop)
                        pudel_location.pop(pudel_location.index((x+25-i,y+25-j)))
                        pudelid+=1
                        pudeli_count = font.render("Bottles: " + str(pudelid), True, (255, 255, 255))
            if len(pudel_location) == 0:
                while loc < randint(2,11):
                    pudel_location.append((randint(200,1000), randint(200,520)))
                    loc+=1

            win.blit(map_img, (0, 0))
            win.blit(pudeli_count, (1000,25))
            win.blit(aeg_count, (600,25))
            win.blit(parim,(200,25))
            pudel_spawn(pudel,pudel_location)
            win.blit(player, (x, y))
            win.blit(pirokunn, (piro_x, piro_y))
            win.blit(valgus,(0,0))
            player_rect = pygame.Rect(x,y,35,35)
            pirokunn_rect = pygame.Rect(piro_x,piro_y,35,35)
            
            if player_rect.colliderect(pirokunn_rect):
                piro_x= randint(50, 1100)
                piro_y= randint(450, 600)
                pudelid = 0
                pygame.mixer.Channel(0).stop()
                pygame.mixer.Channel(1).stop()
                mixer.music.load("sounds/music/outro.mp3")
                mixer.music.set_volume(0.7)
                mixer.music.play()
                kinnipüütud = 1
                state = "menu"
                valik = "1"
            elif aeg >= time_all:
                mixer.music.stop()
                pygame.mixer.Channel(0).stop()
                pygame.mixer.Channel(1).stop()
                if pudelid > parim_tulemus:
                    parim_tulemus = pudelid
                    with open("parim.txt", "w") as f:
                        f.write(str(parim_tulemus))
                    mixer.music.load("sounds/music/victory.mp3")
                elif pudelid < parim_tulemus:
                    mixer.music.load("sounds/music/outro.mp3")
                mixer.music.set_volume(0.7)
                mixer.music.play()
                state = "menu"
                valik = "1"
                i=0
                pudel_all+=pudelid
                pudelid=0
                piro_x= randint(50, 1100)
                piro_y= randint(450, 600)

            elif state == "intro":
                valik = "0"
                mixer.music.stop()
                mixer.music.load("sounds/music/intro.mp3")
                mixer.music.set_volume(0.7)
                mixer.music.play()
        win.blit(versioon,(5,680))
        if state == "game":
            pass
        else:
            win.blit(bottles,(5,0))
            if pudel_all<10:
                win.blit(pudel_sml,(15,5))
            else:
                win.blit(pudel_sml,(35,5))
        pygame.display.update()
            
    pygame.quit()

if __name__ == "__main__":
    main()
