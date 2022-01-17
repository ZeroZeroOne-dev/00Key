# Overview

Another bottom to place the PCB on with a 7% slope. This one is almost certinaly only useful if it 
is printed out of clear PETG. Otherwise the light from the RGB LEDs can't be seen.

# OpenSCAD

This is designed with OpenSCAD which can be downloaded at https://www.openscad.org. If you want
to make changes the source files can be edited directly or use the customizer built into OpenSCAD, 
Window --> Customizer.

## Files

| Filename | Note |
| -------- | ---- |
| 00keyBottom.scad | The main source file of the design, all the available variables are commented <br/>at the top of the file if you want to change something |
| spacer.scad | The source file for the spacers used to put between the PCB and case |
| cylinders.scad | A library used by spacers.scad, only the `hollowCylcinder` module is used | 
| cubes.scad | A library used by 00keyBottom.scad, only the `roundedCube` module is used |

# Assembly
     
The 2 LED strips should be fastened to the bottom of the PCB using Kapton tape or your favorite 
adhesive. They should be positioned so they line up with the slots on the bottom of the case.

The default design intends that the PCB is connected to the case using M2x4x3.5 heat set inserts with
a 2.5 mm spacer in between case and PCB. The size of the hole for the heatset inserts can be
changed in `00keyBottom.scad` if a different size is wanted. The spacers can be made thicker in
`spacer.scad` if thicker spacers are wanted/needed.

The spacers can be held in place with a dab of super glue during assembly so they stay in place as 
the PCB is screwed down.

*NOTE:* I snipped the legs of the controller pins so they didn't stick so far down. If you 
don't do this you will probably need thicker spacers.
          
# Side View
     
![Side View](IMG_0881.png)
             
# Bottom View

![RGB LED](IMG_0878.png)