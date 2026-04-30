# i wanna be the guy
animated music thing for the wii

<img width="1712" height="960" alt="screenie collage" src="https://github.com/user-attachments/assets/4dd6f625-723d-4f2c-a3e6-7077f5834b71" />

[watch the video](https://youtu.be/Vr-0jVaAAo0) - [project page](https://boxy.neocities.org/stuff/guy/)

## running
### hardware
drop unzipped files on sd in `/apps/guy/`. alternatively, drop `guydat.bin` on root of sd and wiiload
### emulator
drop `guydat.bin` on root of sd card and launch the dol

## compiling
you need libogc 2.11. any newer will break application features. use libdvm i dont think libfat works
```
git clone https://github.com/xOx-Liy-Codez-XD-oXo/guy
cd guy
make
make pack
```
