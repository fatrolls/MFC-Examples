///////////////////////////////////////////////////////////////////
// Scene File: SPINTORI.POV, for POV-Ray v2.x
//
// Generated With POVCAD 4 © Alfonso Hermida 1993-1995
//                         © Robert McGregor 1993-1995
//
// Created on 6/15/96 at 10:11 pm

#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"
#include "spintori.ani"

background { color Gray75 }

// Set up the camera
camera {
  right     <1.6, 0, 0>
  location  <2.5, 2, -2.5>
  look_at   <0, 0, 0>
}

light_source {<25, 20, -25> color White}
light_source {<-2.5, 2, -2.5> color White}

#declare TorusWheel = 
union {
  torus { 1.5, 0.1
    rotate <90.0, 0.0, 0.0>
  }

  torus { 1.5, 0.1
    rotate <90.0, 45.0, 0.0>
  }

  torus { 1.5, 0.1
    rotate <90.0, 90.0, 0.0>
  }

  torus { 1.5, 0.1
    rotate <90.0, 135.0, 0.0>
  }
  texture { pigment { color Red } finish { Shiny }}
}

object { 
  TorusWheel 
  rotate <0, RotY, 0> 
}
