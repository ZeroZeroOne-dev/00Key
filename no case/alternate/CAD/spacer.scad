use <cylinders.scad>

$fn = 100;
outerDiameter = 8;
innerDiameter = 3.0;
height = 2.5;

hollowCylinder(outerDiameter = outerDiameter, innerDiameter = innerDiameter, topOuterDiameter = outerDiameter, topInnerDiameter = innerDiameter, height = height, center = false, hasFloor = false, 
    rounded = undef, floorThickness = undef);
