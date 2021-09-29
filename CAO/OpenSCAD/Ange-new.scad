//%ange_outside(size=4, precision = 150);
//aile(size=4, precision = 150, inside=true,jeu = 0);
//elec_contenaire (size=4,top=false, conv=50, precision=150);
elec_contenaire (size=4,top=true, conv=50, precision=150);
//moule_ext(size=4, left=true, conv= 20, precision=150);
//moule_int(size=4, left=true, precision=150, jeu=0.6);
//moule_ext(size=4, left=false, conv= 20, precision=150);
//moule_int(size=4, left=false, precision=150, jeu=0.6);


module ange_outside (size, conv=10, taille_aile=20, precision = 50, jeu = 0.6) {
    largeur = 10*size;
    hauteur = largeur * 3;
    Rsphere = largeur/2;
    layer = size/3;
    
    main_largeur = 4*size;
    main_hauteur = 1.1 * main_largeur;
    main_ep = main_largeur / 2.5;
        
    cone = [[0,0], [0, hauteur], [largeur, 0]];

    nez_longueur = size*1.5;
    nez_largeur = nez_longueur*0.3;
    
    
    union(){
        //Corps
        translate([0,0,layer]) minkowski(){
            cylinder(h=hauteur, r1=largeur, r2=0, $fn=precision);
            sphere(layer, $fn=precision);
        }
        //Tête
        translate([0,0,layer]) translate([0,0,hauteur-Rsphere]) sphere(Rsphere + layer, $fn=precision);
        //Main
        translate([0,0,layer]) minkowski(){
            translate([largeur/3,0,hauteur/2]) rotate([90,30,0]) linear_extrude (height = main_ep, center = true, convexity=conv, $fn=precision)
            {
                union(){
                    square([main_largeur, main_hauteur]);
                    translate([main_largeur/2, main_hauteur]) circle(main_largeur /2);
                    translate([main_largeur/2, 0]) circle(main_largeur /2);
                }
            }
            sphere(layer, $fn=precision);
        }
        //Aile
        aile(size=size, conv=conv, precision = precision, jeu=jeu);
        //Nez
        translate([0,0,layer]) translate([Rsphere,0,hauteur-Rsphere]) rotate([0, 90, 0]) union()
        {
            cylinder(h=nez_longueur, r=nez_largeur, $fn=precision);
            translate([0,0,nez_longueur]) sphere(r=nez_largeur, $fn=precision);
            sphere(r=nez_largeur, $fn=precision);
        }
    }
}

module ange_bottom (size, conv=10, inside=false, precision = 50) {
    
    largeur = 10*size;
    hauteur = largeur * 3;
    layer = size/3;
    
    //Parametres de base pour les volumes
    ep_support = 1*size;
    rayon_goulo = largeur*2/3;
    rayon_support = rayon_goulo + ep_support;
    
    translate([0,0,layer]) union()
    {
        //Piece commune aux deux éléments
        translate([0,0,-layer])cylinder(h = ep_support, r=rayon_goulo, $fn=precision);
        translate([0,0,ep_support-layer]) cylinder(h=ep_support, r=rayon_support, $fn=precision);
        
        if(inside)
        {
            //Intérieure de l'ange
            translate([0,0,ep_support*2-layer]) cylinder(h=hauteur-largeur-ep_support, r1=rayon_support, r2=size*1.7, $fn=precision);
            translate([0,0,ep_support+hauteur-largeur-layer]) cylinder(h=largeur/2+layer, r=size*1.7, $fn=precision);
            translate([0,0,ep_support+hauteur-largeur/2]) sphere(size*1.7, $fn=precision);
        }
    }
}

module aile(size, precision = 50, conv = 10, inside=false, jeu=0.6)
{
    largeur = 10*size;
    hauteur = largeur * 3;
    layer = size/3;
    
    taille_aile = size * 2;
    rayonAile = taille_aile/3;
    
    rayon_aile = rayonAile + layer;
    sizeX = rayon_aile*7/10;
    sizeY = rayon_aile*4/10;
    translate([-largeur/2.35,0, hauteur/2.1]) rotate([90, -90+atan(largeur/hauteur), layer])  union()
    {
        rotate([-90,0,0])
            if (inside)
                translate([-taille_aile*0.9,0,taille_aile]) rotate([90,90,0]) rotate_extrude(convexity=conv, angle=90, $fn=precision) translate([taille_aile*0.9,0]) square([sizeX+jeu*2, sizeY+jeu*2], center=true);
            else
                cylinder(r=rayon_aile, h=taille_aile, $fn=precision);
            
        rotate([0,180,0]) translate([-taille_aile,taille_aile]) rotate_extrude(convexity=conv, angle=90, $fn=precision) translate([taille_aile,0])
            if (inside)
                square([sizeX+jeu*2, sizeY+jeu*2], center=true);
            else
                circle(r=rayon_aile);

        rotate([0,0,-90]) translate([-taille_aile*2 - taille_aile * 2,taille_aile]) rotate_extrude(convexity=conv, angle=180,$fn=precision) translate([taille_aile*2,0])
            if (inside)
                square([sizeX+jeu*2, sizeY+jeu*2], center=true);
            else
                circle(r=rayon_aile);
            
        translate([taille_aile, taille_aile*6]) rotate([-90,0,90])
            if (inside)
                translate([-(sizeX+jeu*2)/2, -(sizeY+jeu*2)/2,0]) cube([sizeX+jeu*2, sizeY+jeu*2, taille_aile*4]);
            else
                cylinder(r=rayon_aile, h=taille_aile*4,$fn=precision);
            
        translate([-taille_aile*3, taille_aile*4]) rotate([0,0,90]) rotate_extrude(convexity=conv, angle=90, $fn=precision) translate([taille_aile*2,0])
            if (inside)
                square([sizeX+jeu*2, sizeY+jeu*2], center=true);
            else
                circle(r=rayon_aile);
        translate([-taille_aile*5, taille_aile*4])
            if (inside)
                //cube([sizeX*2.5+jeu, sizeX*2.5+jeu, sizeY+jeu], center=true);
                cylinder(h=sizeY+jeu*2, r=sizeX*1.5+jeu, center=true, $fn=precision);
            else
                sphere(rayon_aile*2, $fn=precision);
            
            if (inside)
            {
                translate([-taille_aile*0.9,taille_aile*(1-0.9),0]) rotate([-90,0,90]) translate([-(sizeX+jeu*2)/2, -(sizeY+jeu*2)/2,0]) cube([sizeX+jeu*2, sizeY+jeu*2, taille_aile*4.6]);
                translate([-taille_aile*(0.9+4.6),-taille_aile*(0.9-0.1),0]) rotate([0,0,90]) rotate_extrude(convexity=conv, angle=90, $fn=precision) translate([taille_aile*0.9,0]) square([sizeX+jeu*2, sizeY+jeu*2], center=true);
                translate([-taille_aile*(2*0.9+4.6),-taille_aile*(0.9-0.1),0]) rotate([90,0,0]) translate([-(sizeX+jeu*2)/2, -(sizeY+jeu*2)/2,0]) cube([sizeX+jeu*2, sizeY+jeu*2, taille_aile+jeu]);
            }
    }
}

module elec_contenaire (size, top = true, precision = 50, jeu = 0.6, conv = 10, pcb = false)
{
    layer = size/3;
    largeur = 10*size+layer;
    
    //Dimensions associées au PCB
    haut_composant = 1; //Hauteur des composants hors LED
    haut_PCB = 2; //Hauteur du PCB
    ep_parois = 3; //Epaisseur des parois
    hauteur = haut_composant + haut_PCB + ep_parois; //hauteur de la zone des composants
    diam_led = 6; //Diamètre de la led
    diam_PCB = 75; //Diamètre du PCB
    zone_hors_cmp = 3; //Zone sans composant tout autour du PCB
    pos_vis = 20; //Position du centre des vis par rappor au centre du module
    diam_vis = 3.6; //Diamètre de passage des vis
    diam_tete_vis = 8; //Diamètre de la tête de vis
    
    taille_ecrou = 5.5; //Taille de l'écrou
    jeu_ecrou = 0.2; //jeu; //Jeu autour de l'écrou pour le faire passer.
    h_ecrou = 2.5 + 2; //Epaisseur de l'écrou
    
    
    //Dessous
    l_pile = 65;
    d_pile = 12;
    h_pile = 12;
    h_cmp_dessous = 5;
    hauteur_dessous = h_pile + ep_parois; //prof_tete_vis;
    
    prof_tete_vis = hauteur_dessous - h_cmp_dessous - ep_parois -1; //Profondeur de la tête de vis
    
    cong_dessous = size*9/10;
    
    if (top)
    {
        //PCB
        if (pcb)
        {
            translate([0,0,-hauteur+2]) rotate([180,0,0]) import("PCB.stl");
        }
        difference()
        {
            union()
            {
                ange_bottom(size=size, conv= conv, inside=false, precision = precision);
                translate([0,0,-hauteur]) cylinder(hauteur, r=largeur, $fn=precision);
            }
            
            //Objects à retirer
            //Insert de l'aile
            aile(size=size, conv = conv, precision = precision, inside=true, jeu=jeu);
            //Espace pour la LED
            translate([0,0,-hauteur-5]) cylinder(h=hauteur+1*size*2+10, r=diam_led/2+1, $fn=precision);
            //Espace pour le PCB
            translate([0,0,-hauteur-5]) cylinder(h=haut_PCB+5, r=diam_PCB/2+1, $fn=precision);
            //Espace pour les composants
            translate([0,0,-hauteur-5]) cylinder(h=haut_PCB+haut_composant+5, r=diam_PCB/2-zone_hors_cmp+1, $fn=precision);
            //Espace pour les vis
            translate([0,pos_vis,-hauteur-5]) cylinder(h=hauteur+1*size*2+10, r=diam_vis/2, $fn=precision);
            translate([0,-pos_vis,-hauteur-5]) cylinder(h=hauteur+1*size*2+10, r=diam_vis/2, $fn=precision);
            //Espace pour les écrous
            translate([0,-pos_vis,(1*size)*2-layer-h_ecrou]) Ecrou(largeur=taille_ecrou+jeu_ecrou*2, hauteur=h_ecrou+5, precision=precision);
            translate([0,pos_vis,(1*size)*2-layer-h_ecrou]) Ecrou(largeur=taille_ecrou+jeu_ecrou*2, hauteur=h_ecrou+5, precision=precision);
        }
    }
    else
    {
        difference()
        {
            translate([0,0,-hauteur-hauteur_dessous]) cylinder(hauteur_dessous, r=largeur, $fn=precision);
            
            //Objects à retirer
            //Congé du bord
            translate([0,0,-hauteur-hauteur_dessous+cong_dessous]) rotate_extrude(convexity=conv,$fn=precision) translate([largeur-cong_dessous,0]) difference()
            {
                translate([cong_dessous, -cong_dessous]) square(cong_dessous*2, center=true);
                circle(r=cong_dessous, $fn=precision);
            }
            //Espace pour les composants
            translate([0,0,-hauteur+5]) rotate([180,0,0]) cylinder(h=h_cmp_dessous+5, r=diam_PCB/2-zone_hors_cmp+1, $fn=precision);
            //Espace pour la pile
            translate([0,0,-hauteur+5]) rotate([180,0,0]) translate([-l_pile/2, -d_pile/2, 0]) cube([l_pile, d_pile,h_pile+5]);
            
            //Espace pour les vis
            translate([0,-pos_vis,-hauteur+5]) rotate([180,0,0]) cylinder(h=hauteur+hauteur_dessous+10, r=diam_vis/2, $fn=precision);
            translate([0,pos_vis,-hauteur+5]) rotate([180,0,0]) cylinder(h=hauteur+hauteur_dessous+10, r=diam_vis/2, $fn=precision);
            //Espace pour les têtes de vis
            translate([0,-pos_vis,-hauteur-hauteur_dessous-5]) cylinder(h=prof_tete_vis+5, r=diam_tete_vis/2, $fn=precision);
            translate([0,pos_vis,-hauteur-hauteur_dessous-5]) cylinder(h=prof_tete_vis+5, r=diam_tete_vis/2, $fn=precision);
            translate([-11.3-11.6/2,-10.4+4.8/2, -hauteur+5]) rotate([180,0,0]) cube([11.6,4.8,hauteur+hauteur_dessous+10]);
        }
    }
}

module Ecrou(largeur, hauteur, precision=10)
{
    scw_x1 = (largeur/2)/tan(60);
    scw_x2 = (largeur/2)/cos(30);
    forme_ecrou = [[scw_x2,0], [scw_x1,largeur/2], [-scw_x1,largeur/2], [-scw_x2,0], [-scw_x1,-largeur/2], [scw_x1,-largeur/2]];
    linear_extrude(hauteur, $fn=precision) polygon(forme_ecrou);
}

module moule_ext(size, left=true, conv = 10, precision = 50, jeu =0.6)
{
    largeur = 10*size;
    hauteur = largeur*3;
    layer = size/3;
    taille_aile = size*2;
    ep = size*1.5;
    sizeX = (largeur+layer)*2+(taille_aile*5) * sin(90-atan(largeur/hauteur))+ep;
    sizeY = largeur+layer+ep;
    sizeZ = hauteur+layer*2+ep+size;
    echo(sizeX);
    echo(sizeY);
    echo(sizeZ);
    rayon_support = largeur*4/5;
    vis_pos = size * 3;
    vis_prof = 20; //Taille de la vis : Todo
    vis_r = 3.5/2;
    vis_tete_r = 5.5/2;
    vis_tete_prof = 47-7; //A calculer en fonction de la taille de la vis. //Todo
    ecrou_l = 5.5;
    ecrou_L = (1.15*5.5)/2;
    ecrou_ep = 2.4;
    ecrou_prof = 7; //a calculer en fonction de la taille de la vis. //Todo
    difference()
    {
        union()
        {
            difference()
            {
                if (left)
                {
                    translate([-sizeX+largeur+layer+ep/2, -sizeY, -size]) cube([sizeX, sizeY, sizeZ]);
                }
                else
                {
                    translate([-sizeX+largeur+layer+ep/2, 0, -size]) cube([sizeX, sizeY, sizeZ]);
                }
                
                ange_outside (size=size, conv=conv, precision=precision);
                //translate([0,0,-size*2])cylinder(h = size*4, r=rayon_support, $fn=precision);
                translate([-size*2,-size,-size*2]) cube([size*4, size*2,size*4]);
                if(left)
                {
                    rotate([0,0,180]) translate([0, vis_pos, -size*2]) cylinder(h=vis_prof+size, r=vis_r, $fn=precision);
                }
                else
                {
                    translate([0, vis_pos, -size*2]) cylinder(h=vis_prof+size, r=vis_r, $fn=precision);
                }
                if(!left)
                {
                    translate([-sizeX+largeur+layer+ep/2+size*2, sizeY-vis_tete_prof, size]) rotate([-90,0,0]) cylinder(h=vis_tete_prof+size, r= vis_tete_r, $fn=precision);
                    translate([-sizeX+largeur+layer+ep/2+size*2, sizeY-vis_tete_prof, sizeZ-size*3]) rotate([-90,0,0]) cylinder(h=vis_tete_prof+size, r= vis_tete_r, $fn=precision);
                    translate([largeur+layer+ep/2-size*2, sizeY-vis_tete_prof, sizeZ-size*3]) rotate([-90,0,0]) cylinder(h=vis_tete_prof+size, r= vis_tete_r, $fn=precision);
                }
                else
                {
                    translate([-sizeX+largeur+layer+ep/2+size*2, size, size]) rotate([90,0,0]) cylinder(h=size*2-jeu, r= vis_tete_r-jeu/2, $fn=precision);
                    translate([-sizeX+largeur+layer+ep/2+size*2, size, sizeZ-size*3]) rotate([90,0,0]) cylinder(h=size*2-jeu, r= vis_tete_r-jeu/2, $fn=precision);
                    translate([largeur+layer+ep/2-size*2, size, sizeZ-size*3]) rotate([90,0,0]) cylinder(h=size*2-jeu, r= vis_tete_r-jeu/2, $fn=precision);
                    
                    translate([-sizeX+largeur+layer+ep/2+size*2-(ecrou_l+jeu*2)/2, -ecrou_prof-(ecrou_ep+jeu*2)/2, -size-jeu]) rotate([0,0,0]) cube([ecrou_l+jeu*2, ecrou_ep+jeu*2, vis_pos+ecrou_L+jeu*2]);
                    translate([-sizeX+largeur+layer+ep/2+size*2+(ecrou_l+jeu*2)/2, -ecrou_prof-(ecrou_ep+jeu*2)/2, sizeZ-size+jeu]) rotate([0,180,0]) cube([ecrou_l+jeu*2, ecrou_ep+jeu*2, vis_pos+ecrou_L+jeu*2]);
                    translate([largeur+layer+ep/2-size*2+(ecrou_l+jeu*2)/2, -ecrou_prof-(ecrou_ep+jeu*2)/2, sizeZ-size+jeu]) rotate([0,180,0]) cube([ecrou_l+jeu*2, ecrou_ep+jeu*2, vis_pos+ecrou_L+jeu*2]);
                    
                }
            }
            if(!left)
            {
                translate([-sizeX+largeur+layer+ep/2+size*2, 0, size]) rotate([90,0,0]) cylinder(h=size-jeu, r= vis_tete_r-jeu/2, $fn=precision);
                translate([-sizeX+largeur+layer+ep/2+size*2, 0, sizeZ-size*3]) rotate([90,0,0]) cylinder(h=size-jeu, r= vis_tete_r-jeu/2, $fn=precision);
                translate([largeur+layer+ep/2-size*2, 0, sizeZ-size*3]) rotate([90,0,0]) cylinder(h=size-jeu, r= vis_tete_r-jeu/2, $fn=precision);
            }
        }
        translate([-sizeX+largeur+layer+ep/2+size*2, -ep-sizeY, size]) rotate([-90,0,0]) cylinder(h=(sizeY+ep)*2, r= vis_r, $fn=precision);
        translate([-sizeX+largeur+layer+ep/2+size*2, -ep-sizeY, sizeZ-size*3]) rotate([-90,0,0]) cylinder(h=(sizeY+ep)*2, r= vis_r, $fn=precision);
        translate([largeur+layer+ep/2-size*2, -ep-sizeY, sizeZ-size*3]) rotate([-90,0,0]) cylinder(h=(sizeY+ep)*2, r= vis_r, $fn=precision);
    }
}

module moule_int(size, conv = 10, left=true, precision = 50, jeu = 0.6)
{
    largeur = 10*size;
    hauteur = largeur*3;
    layer = size/3;
    taille_aile = size*2;
    ep = size*1.5;
    rayon_support = largeur*4/5;
    vis_pos = size * 3;
    vis_prof = 30; //Taille de la vis : a définir //Todo
    vis_r = 3.6/2;
    ecrou_l = 5.5;
    ecrou_L = (1.15*5.5)/2;
    ecrou_ep = 2.4;
    ecrou_pos = vis_prof-ecrou_ep-18;
    
    difference()
    {
        union()
        {
            ange_bottom (size=size, conv=conv, inside=true, precision = precision);
            //translate([0,0,-size]) cylinder(h = size, r=rayon_support-0.6, $fn=precision);
            if(left)
            {
                rotate([0,0,180]) translate([-size*2+jeu,0,-size]) cube([size*4-jeu*2, size-jeu, size]);
            }
            else
            {
                translate([-size*2+jeu,0,-size]) cube([size*4-jeu*2, size-jeu, size]);
            }
        }
        if (left)
        {
            translate([-largeur, 0, -size*2]) cube([2*largeur, 2*largeur, hauteur+size*2]);
        }
        else
        {
            translate([-largeur, -2*largeur, -size*2]) cube([2*largeur, 2*largeur, hauteur+size*2]);
        }
        
        aile(size=size, conv = conv, precision = precision, inside=true, jeu=0.6);
        if(left)
        {
            rotate([0,0,180]) translate([0, vis_pos, -size]) cylinder(h=vis_prof+size, r=vis_r, $fn=precision);
            rotate([0,0,180]) translate([-ecrou_l/2-jeu, -jeu, ecrou_pos-ecrou_ep/2-jeu]) cube([ecrou_l+jeu*2, vis_pos+ecrou_L+jeu*2, ecrou_ep+jeu*2]);
        }
        else
        {
            translate([0, vis_pos, -size]) cylinder(h=vis_prof+size, r=vis_r, $fn=precision);
            translate([-ecrou_l/2-jeu, -jeu, ecrou_pos-ecrou_ep/2-jeu]) cube([ecrou_l+jeu*2, vis_pos+ecrou_L+jeu*2, ecrou_ep+jeu*2]);
        }
    }
        
}