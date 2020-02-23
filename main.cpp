#include <windows.h>
#include <conio.h>
#include <stdio.h>

#include "funciones.h"
#include "zip.h"
#include "unzip.h"
#include <png.h>

using namespace std;

HZIP hz; DWORD writ;

byte QCPDATA[174] =
{
0x51,0x4c,0x43,0x4d,0x66,0x6d,0x74,0x20,0x96,0x00,0x00,0x00,0x01,0x00,0x41,0x6d,0x7f,0x5e,0x15,0xb1,0xd0,0x11,0xba,0x91,
0x00,0x80,0x5f,0xb4,0xb9,0x7e,0x02,0x00,0x51,0x63,0x65,0x6c,0x70,0x20,0x31,0x33,0x4b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x38,0x23,0x00,0xa0,0x00,0x40,0x1f,
0x10,0x00,0x04,0x00,0x00,0x00,0x03,0x01,0x07,0x02,0x10,0x03,0x22,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x72,0x61,0x74,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

char *names[115]=
{
"Dialog_Help",
"Dialog_Popup",
"Dialog_Wandpopup",
"Door_Close",
"Door_Locked",
"Door_Open",
"Door_Unlocked",
"Gib",
"Gib_Bone",
"Gib_Stone",
"Gib_Wood",
"Misc_Buff_Expiring",
"Misc_Chest",
"Misc_Coins",
"Misc_Force",
"Misc_Lockpick_Neg",
"Misc_Lockpick_Pos",
"Misc_Negative",
"Misc_Raise",
"Misc_Rumble",
"Misc_Scroll",
"Misc_Switch",
"Misc_Wardrums1",
"Monster_Boss_Drow_Laugh",
"Monster_Boss_Wizard_Attack1",
"Monster_Boss_Wizard_Attack2",
"Monster_Boss_Wizard_Death",
"Monster_Boss_Wizard_Idle",
"Monster_Boss_Wizard_Pain",
"Monster_Drow_Attack",
"Monster_Drow_Death",
"Monster_Drow_Pain",
"Monster_HighPitch_Attack",
"Monster_HighPitch_Death",
"Monster_HighPitch_Idle",
"Monster_HighPitch_Pain",
"Monster_Mimic_Attack",
"Monster_Orc_Alert",
"Monster_Orc_Attack",
"Monster_Orc_Death",
"Monster_Orc_Idle",
"Monster_Orc_Pain",
"Monster_Shadow_Alert",
"Monster_Shadow_Attack",
"Monster_Shadow_Death",
"Monster_Shadow_Idle",
"Monster_Shadow_Pain",
"Monster_Skeleton_Alert",
"Monster_Skeleton_Attack",
"Monster_Skeleton_Death",
"Monster_Skeleton_Idle",
"Monster_Skeleton_Pain",
"Monster_Tree_Alert",
"Monster_Tree_Attack",
"Monster_Tree_Death",
"Monster_Tree_Pain",
"Monster_Troll_Alert",
"Monster_Troll_Attack1",
"Monster_Troll_Attack2",
"Monster_Troll_Death",
"Monster_Troll_Idle",
"Monster_Troll_Pain",
"Monster_Turned_Alert",
"Monster_Turned_Attack",
"Monster_Turned_Death",
"Monster_Turned_Idle",
"Monster_Turned_Pain",
"Monster_Wererat_Alert",
"Monster_Wererat_Attack",
"Monster_Wererat_Death",
"Monster_Wererat_Pain",
"Monster_Worg_Alert",
"Monster_Worg_Attack",
"Monster_Worg_Death",
"Monster_Worg_Idle",
"Monster_Worg_Pain",
"Monster_Wraith_Alert",
"Monster_Wraith_Attack1",
"Monster_Wraith_Attack2",
"Monster_Wraith_Death",
"Monster_Wraith_Idle",
"Monster_Wraith_Pain",
"Music_Graveyard",
"Music_Intro",
"Music_Levelup",
"Music_M04",
"Music_Title",
"Music_Topo",
"Pickup_Ale",
"Pickup_Food",
"Pickup_Item",
"Pickup_Potion",
"Player_Death",
"Player_Pain",
"Sconce_Off",
"Use_Ale",
"Use_Item",
"Weapon_Crossbow_Flyby",
"Weapon_Dagger_Flesh",
"Weapon_Dagger_Swing",
"Weapon_Familiar",
"Weapon_Familiar_Tired",
"Weapon_Flame_Flesh",
"Weapon_Flame_Metal",
"Weapon_Flame_Swing",
"Weapon_Flame_Wood",
"Weapon_Orb_Freeze",
"Weapon_Orb_Mold",
"Weapon_Orb_Shrink",
"Weapon_Staff_Flesh",
"Weapon_Staff_Wood",
"Weapon_Sword_Metal",
"Weapon_Sword_Swing",
"Weapon_Sword_Wood",
"Weapon_Wand_Attack"
};

typedef byte*  cache;
static cache writeData;
static unsigned int current = 0;

//Fix Pal Fire Sword Attack State
byte PalFix[768] = {
	0x00, 0x00, 0x00, 0x3E, 0x40, 0x3E, 0xBF, 0xB5, 0x00,
	0x00, 0x00, 0x00, 0x77, 0x71, 0x00, 0xBF, 0xB5, 0x00,
	0xB7, 0xD4, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x0A, 0x0A, 0x0A,
	0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x4B, 0x49,
	0x87, 0x8D, 0x8F, 0x8F, 0x99, 0x97, 0x57, 0x5D, 0x5F,
	0x1E, 0x20, 0x1E, 0x69, 0x6B, 0x69, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x6F, 0x75, 0x77, 0x3F, 0x49, 0x47,
	0xAF, 0xB9, 0xB7, 0x77, 0x79, 0x7F, 0xAF, 0xC8, 0xD0,
	0x7F, 0x8B, 0x89, 0x00, 0x00, 0x00, 0x9F, 0xA9, 0xA7,
	0x00, 0x00, 0x00, 0x34, 0x36, 0x34, 0x5F, 0x6B, 0x69,
	0x9F, 0xA9, 0xA7, 0x00, 0x00, 0x00, 0x5F, 0x61, 0x69,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x9F, 0xA1, 0x9F, 0x77, 0x79, 0x7F, 0x94, 0x96, 0x94,
	0xAF, 0xB9, 0xB7, 0x7F, 0x89, 0x87, 0x00, 0x00, 0x00,
	0x5F, 0x69, 0x67, 0x5F, 0x65, 0x67, 0x00, 0x00, 0x00,
	0x4F, 0x55, 0x4F, 0x74, 0x81, 0x7F, 0x5F, 0x61, 0x5F,
	0xAF, 0xB9, 0xB7, 0x89, 0x8B, 0x94, 0x17, 0x19, 0x17,
	0xB7, 0xD4, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x29, 0x2B, 0x29, 0xBF, 0xBD, 0xBF,
	0xB4, 0xC1, 0xBF, 0x1E, 0x20, 0x1E, 0x14, 0x16, 0x14,
	0x57, 0x65, 0x67, 0x00, 0x00, 0x00, 0x57, 0x65, 0x67,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9F, 0xA1, 0x9F,
	0x94, 0xA1, 0x9F, 0xB7, 0xD4, 0xD8, 0x77, 0x7D, 0x7F,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0x91, 0x8F,
	0x3F, 0x5D, 0x57, 0x1E, 0x20, 0x1E, 0x67, 0x69, 0x67,
	0x14, 0x16, 0x14, 0x14, 0x16, 0x14, 0x00, 0x00, 0x00,
	0x17, 0x19, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x00, 0x00, 0x00,
	0x0E, 0x0E, 0x0C, 0x24, 0x26, 0x22, 0x2E, 0x30, 0x2C,
	0x00, 0x00, 0x00, 0x24, 0x26, 0x24, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x30, 0x2E,
	0x00, 0x00, 0x00, 0x30, 0x32, 0x2E, 0x3F, 0x41, 0x3F,
	0x3F, 0x41, 0x3F, 0x2A, 0x2C, 0x2A, 0x00, 0x00, 0x00,
	0x2E, 0x30, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x6F, 0x75, 0x77, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x15, 0x17, 0x15, 0x10, 0x10, 0x10, 0x12, 0x12, 0x12,
	0x12, 0x12, 0x12, 0x16, 0x18, 0x16, 0x13, 0x15, 0x13,
	0x1E, 0x20, 0x1C, 0x00, 0x00, 0x00, 0x20, 0x22, 0x20,
	0x1F, 0x1F, 0x1D, 0x23, 0x26, 0x22, 0x1E, 0x20, 0x1B,
	0x1B, 0x1D, 0x1A, 0x24, 0x26, 0x24, 0x20, 0x22, 0x1E,
	0x21, 0x23, 0x21, 0x00, 0x00, 0x00, 0x26, 0x28, 0x26,
	0x28, 0x2A, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x20, 0x22, 0x1E, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x2E, 0x30, 0x2C, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x10, 0x13, 0x15, 0x13, 0x16, 0x18, 0x16,
	0x12, 0x12, 0x12, 0x17, 0x19, 0x15, 0x17, 0x19, 0x17,
	0x1E, 0x20, 0x1C, 0x00, 0x00, 0x00, 0x19, 0x1B, 0x19,
	0x20, 0x22, 0x1D, 0x1E, 0x20, 0x1C, 0x00, 0x00, 0x00,
	0x20, 0x1F, 0x1E, 0x00, 0x00, 0x00, 0x28, 0x2A, 0x28,
	0x20, 0x22, 0x1E, 0x20, 0x22, 0x20, 0x22, 0x24, 0x22,
	0x2E, 0x30, 0x2C, 0x2C, 0x2E, 0x2C, 0x2E, 0x30, 0x2C,
	0x28, 0x2A, 0x28, 0x28, 0x2A, 0x28, 0x3B, 0x3D, 0x38,
	0x00, 0x00, 0x00, 0x34, 0x36, 0x34, 0x00, 0x00, 0x00,
	0x30, 0x32, 0x30, 0x30, 0x32, 0x30, 0x2C, 0x2E, 0x29,
	0x3D, 0x3F, 0x3D, 0x2E, 0x30, 0x2C, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x17, 0x15,
	0x1C, 0x1D, 0x19, 0x1E, 0x20, 0x1C, 0x12, 0x12, 0x10,
	0x1B, 0x1D, 0x1B, 0x12, 0x12, 0x12, 0x24, 0x26, 0x24,
	0x12, 0x12, 0x12, 0x17, 0x19, 0x16, 0x1D, 0x1F, 0x1D,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x26, 0x24,
	0x28, 0x2A, 0x28, 0x00, 0x00, 0x00, 0x2E, 0x30, 0x2C,
	0x00, 0x00, 0x00, 0x26, 0x28, 0x26, 0x00, 0x00, 0x00,
	0x12, 0x12, 0x12, 0x26, 0x28, 0x26, 0x00, 0x00, 0x00,
	0x20, 0x22, 0x20, 0x22, 0x24, 0x20, 0x00, 0x00, 0x00,
	0x26, 0x28, 0x24, 0x00, 0x00, 0x00, 0x2C, 0x2C, 0x2A,
	0x13, 0x15, 0x13, 0x10, 0x10, 0x10, 0x12, 0x12, 0x12,
	0x22, 0x24, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x12, 0x12, 0x10, 0x10, 0x10, 0x0E,
	0x27, 0x25, 0x00, 0xF8, 0xD4, 0x2F, 0xF8, 0xD4, 0x2F,
	0x17, 0x00, 0x00, 0x17, 0x00, 0x00, 0xF8, 0xD4, 0x2F,
	0x2F, 0x31, 0x00, 0x97, 0x91, 0x00, 0x2F, 0x31, 0x00,
	0x97, 0x91, 0x00, 0xF8, 0xDC, 0x00, 0x63, 0x5D, 0x00,
	0xBF, 0xB5, 0x00, 0x14, 0x16, 0x14, 0x14, 0x16, 0x14,
	0x17, 0x19, 0x17, 0x0C, 0x0C, 0x09, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x36, 0x32,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3D, 0x3F, 0x3D,
	0x00, 0x00, 0x00, 0x37, 0x39, 0x35, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x2C, 0x2C, 0x2A, 0x00, 0x00, 0x00,
	0x54, 0x56, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF
};


//**************************************************************
//**************************************************************
//  Png_WriteData
//
//  Work with data writing through memory
//**************************************************************
//**************************************************************

static void Png_WriteData(png_structp png_ptr, cache data, size_t length) {
    writeData = (byte*)realloc(writeData, current + length);
    memcpy(writeData + current, data, length);
    current += length;
}

//**************************************************************
//**************************************************************
//  Png_Create
//
//  Create a PNG image through memory
//**************************************************************
//**************************************************************

int *palettes_offset;//

int gettransbyte(int paloffset)
{
    FILE *fpal = fopen ("Datos/palettes.bin","rb");
    int pal;
    if(!fpal)
    {
       error("No puede abrir palettes.bin");
    }
    fseek(fpal, palettes_offset[paloffset] ,SEEK_SET);
    int max = ReadWord(fpal);

    pal = 0;
    int x;
    for(x = 0;x < max;x++)
    {
       int Palbit = ReadWord(fpal);
       int B = (Palbit & 0x1F) << 3;
       int G = (Palbit >> 5 & 0x3F) << 2;
       int R = (Palbit >> 11 & 0x3F) << 3;
       
       if(R == 0 && G == 0 && B == 0 && x == 0){pal = x;}
       else if(R == 248 && G == 252 && B == 248){pal = x;}
       else if(R == 248 && G == 0 && B == 248){pal = x; break;}
       else if(R == 0 && G == 252 && B == 248){pal = x; break;}
       else if(R == 0 && G == 248 && B == 248){pal = x; break;}
       else if(R == 0 && G == 240 && B == 248){pal = x; break;}
       else if(R == 0 && G == 244 && B == 248){pal = x; break;}
       else if(R == 0 && G == 0 && B == 0 && x == 255){pal = x;}
    }
    
    if(x > max) {pal = max;}
    
    fclose(fpal);
    
    return pal;
}

cache Png_Create(cache data, int* size, int width, int height, int paloffset, int bit_depth = 8, int offsetx = 0, int offsety = 0, int tans = -1, int fix = -1)
{
    int i, j;
    cache image;
    cache out;
    cache* row_pointers;
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;
    
    int max = 256;
    if(bit_depth == 4)
        max = 16;
    
    //int bit_depth = 8;
    // setup png pointer
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    if(png_ptr == NULL) {
        error("Png_Create: Failed getting png_ptr");
        return NULL;
    }

    // setup info pointer
    info_ptr = png_create_info_struct(png_ptr);
    if(info_ptr == NULL) {
        png_destroy_write_struct(&png_ptr, NULL);
        error("Png_Create: Failed getting info_ptr");
        return NULL;
    }

    // what does this do again?
    if(setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        error("Png_Create: Failed on setjmp");
        return NULL;
    }

    // setup custom data writing procedure
    png_set_write_fn(png_ptr, NULL, Png_WriteData, NULL);

    // setup image
    png_set_IHDR(
        png_ptr,
        info_ptr,
        width,
        height,
        bit_depth,
        PNG_COLOR_TYPE_PALETTE,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);

    // setup palette
    FILE *fpal = fopen ("Datos/palettes.bin","rb");
    if(!fpal)
    {
       error("No puede abrir palettes.bin");
    }

    //printf("paloffset %d\n", paloffset);
    //Fix Pal Index Fire Sword Idle State
    if(fix == 1){paloffset = 104;}
    
    fseek(fpal, palettes_offset[paloffset] ,SEEK_SET);
    int cntmax = ReadWord(fpal);
    
    palette = (png_colorp) malloc((max*3)*png_sizeof(png_color));

    int x;
    for(x = 0;x < cntmax;x++)
    {
       int Palbit = ReadWord(fpal);
       int B = (Palbit & 0x1F) << 3;
       int G = (Palbit >> 5 & 0x3F) << 2;
       int R = (Palbit >> 11 & 0x3F) << 3;
       
       //Fix Pal Fire Sword Attack State
       if(fix == 2)
       {
          R = PalFix[(x*3)+0];
          G = PalFix[(x*3)+1];
          B = PalFix[(x*3)+2];
       }

       palette[x].red = R;
       palette[x].green = G;
       palette[x].blue = B;
    }
    fclose(fpal);
    
    for(int y = x; y < max;y++)
    {
       palette[y].red = 0;
       palette[y].green = 0;
       palette[y].blue = 0;
    }
    
    png_set_PLTE(png_ptr, info_ptr,palette, max);
    
    if(tans != -1)
    {
        png_byte trans[tans+1]; 
        for(int tr =0;tr < tans+1; tr++)
        {
          if(tr==tans){trans[tr]=0;}
          else {trans[tr]=255;}
        }
        png_set_tRNS(png_ptr, info_ptr,trans,tans+1,NULL);
    }

    // add png info to data
    png_write_info(png_ptr, info_ptr);
    
    if(offsetx !=0 || offsety !=0)
    {
       int offs[2];
    
       offs[0] = Swap32(offsetx);
       offs[1] = Swap32(offsety);
    
       png_write_chunk(png_ptr, (png_byte*)"grAb", (byte*)offs, 8);
    }

    // setup packing if needed
    png_set_packing(png_ptr);
    png_set_packswap(png_ptr);

    // copy data over
    byte inputdata;
    image = data;
    row_pointers = (cache*)malloc(sizeof(byte*) * height);
    for(i = 0; i < height; i++)
    {
        row_pointers[i] = (cache)malloc(width);
        for(j = 0; j < width; j++)
        {
            inputdata = *image;
            row_pointers[i][j] = inputdata;
            image++;
        }
    }

    // cleanup
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, info_ptr);
    free((void**)&palette);
    free((void**)row_pointers);
    palette = NULL;
    row_pointers = NULL;
    png_destroy_write_struct(&png_ptr, &info_ptr);

    // allocate output
    out = (cache)malloc(current);
    memcpy(out, writeData, current);
    *size = current;

    free(writeData);
    writeData = NULL;
    current = 0;

    return out;
}

//--------Rotar 90º Y Flip--------//
static void rotate90andflip(byte *input, byte *output, int width, int height)
{
    int i;
    int length = (width*height);
    int height0 = height;//width
    int width0 = length / height;//height
    //printf("sizeof(input) %d\n",length);
    
    int bit1 = width0;
    int bit2 = 1;
    int bit3 = 0;
    
    int offset = length;
    
    byte pixel;
    for(i = 0; i < length; i++)
    {
    pixel = (byte)input[i];
    output[length - offset + bit3] = (byte)pixel;
    
    if(bit2 == height0){offset = length;}
    else{offset = length - bit1;}
    
    if(bit2 == height0){bit2 = 0; bit3 += 1;}
    bit2 +=1;
    bit1 = width0 * bit2;
    }
}

void GetIndex(char *name,int checkindex, int* filenum, int* offset)
{
    FILE *index;
    index = fopen(name,"rb");
    if(!index)
    {
     error("No puede abrir %s", name);
    }
    
    int count = ReadWord(index)*3;
    //printf("count %d\n",count);
    
    int k = 0;
    for (int n = 0; n < count; n += 3)
    {
        int i1 = ReadByte(index);
        int i2 = ReadWord(index);
        
        if (i1 != 255)
        {
           if(k == checkindex)
           {
             *filenum = i1;
             *offset = i2;
           }
           k++;
        }
        else
        {
            n -= 3;
        }
    }
    int i1 = ReadByte(index);
    int i2 = ReadWord(index);
    if(k == checkindex)
    {
      *filenum = i1;
      *offset = i2;
    }
    fclose(index);
}


int *wtexels_offset;//
static int Create_Walls(int wallindex,int paloffset,int id)
{
    int filenum = 0;
    int walloffset = 0;
    
    //GetIndex("Datos/wtexels.idx",wallindex, &filenum, &walloffset);

    char string[16] = { 0 };
    //printf("filenum %d walloffset %d\n",filenum,walloffset);
    //sprintf(string,"Datos/wtexels%d.bin",filenum);
    sprintf(string,"Datos/wtexels.bin",filenum);
    
    FILE *in, *out;
    in = fopen(string,"rb");
    if(!in)
    {
     error("No puede abrir %s", string);
    }

    fseek(in, wtexels_offset[wallindex],SEEK_SET);
    int mode = ReadByte(in);
    //printf("mode %d\n", mode);//getch();
    
    byte pixel = 0;
    int i;
    
    cache input;
    cache output;
    cache pngout;
    
    input = (byte*)malloc(117*117);
    output = (byte*)malloc(117*117);
    
    if(mode == 8)
    {
        for(i = 0; i < 117*117; i++)
        {
            pixel = ReadByte(in);
            input[i] = (byte)(pixel);
        }
    }
    else
    {
        for(i = 0; i < 117*117; i+=2)
        {
            pixel = ReadByte(in);
            input[i] = (byte)(pixel & 0xF);
            input[i+1] = (byte)(pixel >> 4 & 0xF);
        }
    }
    
    rotate90andflip(input, output, 117, 117);

    fclose(in);

    int pngsize = 0;
    pngout = Png_Create(output, &pngsize,117, 117, paloffset, 8);

    sprintf(string,"WTEXELS/WALL%03d",id);
    ZipAdd(hz, string, pngout, pngsize);
    
    free(input);
    free(output);
    free(pngout);
}

int *ftexels_offset;//
static int Create_Flats(int wallindex,int paloffset,int id)
{
    int filenum = 0;
    int walloffset = 0;
    
    //GetIndex("Datos/wtexels.idx",wallindex, &filenum, &walloffset);

    char string[16] = { 0 };
    //printf("filenum %d walloffset %d\n",filenum,walloffset);
    //sprintf(string,"Datos/wtexels%d.bin",filenum);
    sprintf(string,"Datos/ftexels.bin",filenum);
    
    FILE *in, *out;
    in = fopen(string,"rb");
    if(!in)
    {
     error("No puede abrir %s", string);
    }

    fseek(in, ftexels_offset[wallindex],SEEK_SET);
    int mode = ReadByte(in);
    //printf("mode %d\n", mode);//getch();
    
    byte pixel = 0;
    int i;
    
    cache input;
    cache output;
    cache pngout;
    
    input = (byte*)malloc(64*64);
    output = (byte*)malloc(64*64);
    
    if(mode == 8)
    {
        for(i = 0; i < 64*64; i++)
        {
            pixel = ReadByte(in);
            input[i] = (byte)(pixel);
        }
    }
    else
    {
        for(i = 0; i < 64*64; i+=2)
        {
            pixel = ReadByte(in);
            input[i] = (byte)(pixel & 0xF);
            input[i+1] = (byte)(pixel >> 4 & 0xF);
        }
    }
    
    rotate90andflip(input, output, 64, 64);

    fclose(in);

    int pngsize = 0;
    pngout = Png_Create(output, &pngsize,64, 64, paloffset, 8);

    sprintf(string,"FTEXELS/FLAT%03d",id);
    ZipAdd(hz, string, pngout, pngsize);
    
    free(input);
    free(output);
    free(pngout);
}

int *stexels_offset;//

//void write_png_file(byte* input,int width, int height, int paloffset, int offsetx = 0, int offsety = 0);
static int startoffset = -1;
int Create_Sprites(int bitshapesoffset,int paloffset,int id, int fix = -1)
{
    char string[16] = { 0 };

    FILE *in, *in2;
    in = fopen("Datos/bitshapes.bin","rb");
    if(!in)
    {
     error("No puede abrir bitshapes.bin");
    }
    
    in2 = fopen("Datos/stexels.bin","rb");
    if(!in2)
    {
     error("No puede abrir stexels.bin");
    }

    bitshapesoffset = 4 + (bitshapesoffset);
    fseek(in,bitshapesoffset,SEEK_SET);
    
    int stexelsoffset = ReadUint(in);
    //printf("stexelsoffset %d\n",stexelsoffset);
    
    int bitcount = ReadWord(in)-4;
    int buffsize = ReadWord(in);//Solo usado en el juego original
    //printf("bitcount %d\n",bitcount);
    //getch();
    
    int x0 = ReadByte(in);
    int x1 = ReadByte(in);
    int y0 = ReadByte(in);
    int y1 = ReadByte(in);
    
    int width;
    int height;
    int heightOrg;
    int i14;
    
    int offsetx = 0;
    int offsety = 0;
    
    width = x1 - x0 + 1;
    heightOrg = y1 - y0 + 1;
    height= (i14 = y1 - y0 + 1) % 8 != 0 ? i14 / 8 + 1 : i14 / 8;
    height*=8;
    
    offsetx = (44-x0);
    offsety = (88-y0);

    //printf("x0 -> %d x1 -> %d\n",x0, x1);
    //printf("y0 -> %d y1 -> %d\n",y0, y1);
    
    //printf("width -> %d\n",width);
    //printf("height -> %d\n",height);
    
    cache input;
    cache output;
    cache pngout;
    
    input = (byte*)malloc(width*height);
    output = (byte*)malloc(width*height);
 
    byte pixel;
    byte pixel2;
    int pix = 0;
    int pix2 = 0;
    int count = 0;

    //printf("stexels_offset %d\n", stexels_offset[stexelsoffset]);
    
    fseek(in2,(stexels_offset[stexelsoffset]),SEEK_SET);
    int mode = ReadByte(in2);
    //printf("mode %d\n", mode);

    int trans = -1;
    trans = gettransbyte(paloffset);
    
    //Fix Trans Pixel
    switch (id)
    {
           case 853:case 854:case 855:case 856:
                trans = -1;
                break;
           case 921:case 924:
                trans = 223;
                break;
           case 922:
                trans = 254;
                break;
           case 923:
                trans = 147;
                break;
           case 3:case 4:
           case 925:case 926:case 927:case 928:
           case 953:case 954:case 955:case 956:
           case 985:case 986:case 987:case 988:
           case 993:case 994:case 995:case 996:
           case 997:case 998:case 999:case 1000:
           case 1005:case 1006:case 1007:case 1008:
                trans = 0;
                break;
    }
    
    for(int a = 0; a < bitcount; a++)
    {
        pixel = ReadByte(in);
            
        for(int b = 0; b < 8; b++)
        {
            if((pixel & 1 << b) != 0)
            {
                if(mode == 8)
                {
                    pixel2 = ReadByte(in2);
                    input[count] = (byte)(pixel2);//0xff;
                }
                else
                {
                    fseek(in2,(stexels_offset[stexelsoffset]+1) + pix,SEEK_SET);
                    pixel2 = ReadByte(in2);
                    
                    if(pix2)
                    {
                        input[count] = (byte)(pixel2 >> 4 & 0xF);//0xff;
                    }
                    else
                    {
                        input[count] = (byte)(pixel2 & 0xF);//0xff;
                    }
                    if(pix2 == 1)
                    {
                        pix++;
                        pix2 = 0;
                    }
                    else
                    {
                        pix2++;
                    }
                }
            }
            else
            {
                input[count] = trans;
            }
            count++;
        }
    }

    rotate90andflip(input, output, width, height);

    fclose(in);
    fclose(in2);

    int pngsize = 0;

    pngout = Png_Create(output, &pngsize, width, heightOrg, paloffset, mode, offsetx, offsety, trans, fix);

    sprintf(string,"STEXELS/STEX%03d",id);
    ZipAdd(hz, string, pngout, pngsize);
    
    free(input);
    free(output);
    free(pngout);
}

void ShowInfo()
{
    setcolor(0x07);printf("     ############");
    setcolor(0x0A);printf("(ERICK194)");
    setcolor(0x07);printf("#############\n"); 
    printf("     #ORCS AND ELVES 2 (BREW) EXTRACTOR#\n");
    printf("     # CREADO POR ERICK VASQUEZ GARCIA #\n");
    printf("     # ES PARA ORCS AND ELVES 2 (BREW) #\n");
    printf("     #           VERSION 1.0           #\n");
    printf("     #           MODO DE USO:          #\n");
    printf("     #   LEER EL LEEME.TXT/README.TXT  #\n");
    printf("     ###################################\n");
    printf("\n");
}

char buffer2[15];
char nom[50];
int main(int argc, char *argv[])
{
    ShowInfo();

    FILE *f1, *f2;
    int i;
    
    //INIT palettes.bin Table
    
    FILE *fpal = fopen ("Datos/palettes.bin","rb");
    if(!fpal)
    {
       error("No puede abrir palettes.bin");
    }

    fseek(fpal,0,SEEK_END);
    int size = ftell(fpal);
    fseek(fpal,0,SEEK_SET);

    int pnum1 = 0;
    int pcnt = 0;
    int w1=13; int e1=10;
    
    int ccn = ReadWord(fpal);
    palettes_offset = (int *)malloc(sizeof(int) * ccn);

    for(int x = 0;x < ccn;x++)
    {
       palettes_offset[x]=ftell(fpal);
       int size = ReadWord(fpal);
       pcnt = 0;
       for(int y = 0;y < size;y++)
       {     
           int Palbit = ReadWord(fpal);
           /*if(pcnt == 0)
           {
               
               sprintf(nom,"paletas/Pal_%d.pal",pnum1);
               f1=fopen (nom,"wb");
               sprintf(buffer2,"JASC-PAL");fputs(buffer2,f1); fputc(w1,f1); fputc(e1,f1);
               sprintf(buffer2,"0100");    fputs(buffer2,f1); fputc(w1,f1); fputc(e1,f1);
               sprintf(buffer2,"256");     fputs(buffer2,f1); fputc(w1,f1); fputc(e1,f1);
               pnum1++;
           }
           int B = (Palbit & 0x1F) << 3;
           int G = (Palbit >> 5 & 0x3F) << 2;
           int R = (Palbit >> 11 & 0x3F) << 3;
   
           B = Palbit & 0x1F;
           G = Palbit << 21;
           R = (Palbit >> 11 & 0x3F);

           //sprintf(buffer2,"%d %d %d",R,G,B);
           sprintf(buffer2,"%d %d %d",v9 << 3,(v8 >> 26 & 0x3F) << 2,(v7) << 3);
    	   fputs(buffer2,f1);
    	   fputc(w1,f1);
    	   fputc(e1,f1);
    	   pcnt++;*/
       }
       
       /*for(int y = pcnt;y < 256;y++)
       {
           sprintf(buffer2,"%d %d %d",0,0,0);
    	   fputs(buffer2,f1);
    	   fputc(w1,f1);
    	   fputc(e1,f1);
    	   pcnt++;
       }
       
       fclose(f1);*/
    }
    fclose(fpal);

    //INIT stexels.bin Table
    
    f1 = fopen("Datos/stexels.bin","rb");
    if(!f1)
    {
     error("No puede abrir stexels.bin");
    }
    int cnt = ReadUint(f1);//walls
    //printf("cnt %d\n\n",cnt);
    
    stexels_offset = (int *)malloc(sizeof(int) * cnt);
    
    for(i = 0; i < cnt; i++)
    {
          stexels_offset[i] = ReadUint(f1) + 4;
    }
    
    fclose(f1);
    
    //INIT wtexels.bin Table
    
    f1 = fopen("Datos/wtexels.bin","rb");
    if(!f1)
    {
     error("No puede abrir wtexels.bin");
    }
    cnt = ReadUint(f1);//walls
    //printf("cnt %d\n\n",cnt);
    
    wtexels_offset = (int *)malloc(sizeof(int) * cnt);
    
    for(i = 0; i < cnt; i++)
    {
          wtexels_offset[i] = ReadUint(f1) + 4;
    }
    
    fclose(f1);
    
    //INIT ftexels.bin Table
    
    f1 = fopen("Datos/ftexels.bin","rb");
    if(!f1)
    {
     error("No puede abrir ftexels.bin");
    }
    cnt = ReadUint(f1);//walls
    //printf("cnt %d\n\n",cnt);
    
    ftexels_offset = (int *)malloc(sizeof(int) * cnt);

    for(i = 0; i < cnt; i++)
    {
          ftexels_offset[i] = ReadUint(f1) + 4;
    }
    
    fclose(f1);

    f1 = fopen("Datos/mappings.bin","rb");
    if(!f1)
    {
     error("No puede abrir mappings.bin");
    }
    
    hz = CreateZip("OrcsAndElvesII_Brew.pk3",0);
    
    int count1 = ReadUint(f1);//walls
    int count2 = ReadUint(f1);//flats
    int count3 = ReadUint(f1);//sprites
    int count4 = ReadUint(f1);
    int count5 = ReadUint(f1);
    int count6 = ReadUint(f1);
    int bitshapeindex;
    int paloffset;
    int wallindex;
    //printf("Walls %d\n\n",count1);
    
    if (count1 > 220)
    {
     error("Error count1 supera el maximo de 220");
    }
    
    int start = 0;
    int end = (count1)-1;
    //count1 = count1 * 8;
    for(i = 0; i < count1; i++)
    {
        PrintfPorcentaje(start,end,true, 9,"Extrayendo Wall Texturas......");
        wallindex = ReadUint(f1);//printf("wallindex %d\n", wallindex);
        paloffset = ReadUint(f1);//printf("paloffset %d\n", paloffset);
        Create_Walls(wallindex, paloffset, i);
        //getch();
        start++;
    }
    
    //printf("Flats %d\n\n",count2);
    if (count2 > 24)
    {
     error("Error count1 supera el maximo de 24");
    }
    
    start = 0;
    end = (count2)-1;
    for(i = 0; i < count2; i++)
    {
        PrintfPorcentaje(start,end,true, 10,"Extrayendo Flat Texturas......");
        wallindex = ReadUint(f1);//printf("wallindex %d\n", wallindex);
        paloffset = ReadUint(f1);//printf("paloffset %d\n", paloffset);
        Create_Flats(wallindex, paloffset, i);
        //getch();
        start++;
    }
    
    printf("Sprites %d\n\n",count3);
    if (count3 > 1057)
    {
     error("Error count3 supera el maximo de 1057");
    }
    
    start = 0;
    end = (count3)-1;
    for(int i = 0; i < count3; i++)
    {
        //printf("i %d\n",i);
        PrintfPorcentaje(start,end,true, 11,"Extrayendo Sprites.......");
        bitshapeindex = ReadUint(f1);//printf("bitshapeindex %d\n",bitshapeindex);
        paloffset = ReadUint(f1);//printf("paloffset %d\n", paloffset);
        
        Create_Sprites(bitshapeindex,paloffset,i);
        
        //Fix Pals Here
        if(i == 35){Create_Sprites(bitshapeindex,paloffset,i, 1);}//Create Fix Graphic
        if(i == 36){Create_Sprites(bitshapeindex,paloffset,i, 2);}//Create Fix Graphic
        start++;
        //getch();
    }
    
    //TEXTURE
    /*FILE *text;
    text = fopen("ifdata.txt","w");
    fprintf(text,"TEXTURES\n");
    for(int i = 0; i < count4; i++)
    {
       int value = ReadWord(f1);
       if(value != 32767)
       {
          fprintf(text,"if(texnum == %d){indx = %d;}\n", i, value);
       }
    }
    fprintf(text,"FLATS\n");
    for(int i = 0; i < count5; i++)
    {
       int value = ReadWord(f1);
       if(value != 32767)
       {
          fprintf(text,"if(texnum == %d){indx = %d;}\n", i, value);
       }
    }
    fprintf(text,"SPRITES\n");
    for(int i = 0; i < count6; i++)
    {
       int value = ReadWord(f1);
       if(value != 32767)
       {
          fprintf(text,"if(texnum == %d){indx = %d;}\n", i, value);
       }
    }
    fclose(text);*/

    fclose(f1);
    
    free(palettes_offset);
    free(stexels_offset);
    free(wtexels_offset);
    free(ftexels_offset);
    
    //-----------------------//
    int cmid_name;
    int file_size;
    int header_size;
    int offset;
    int trac_name;
    int buffer_size;
    char name[256];
    
    start = 0;
    end = (115)-1;
    for(int k = 0; k < 115; k++)
    {
        byte *buffer;
        
        PrintfPorcentaje(start,end,true, 12,"Extrayendo Sonidos.......");
        start++;
            
        sprintf(name,"Datos/%s.pmd",names[k]);
        Printf(true, 13, "%s\t\t\t ", names[k]);
        //printf("%s\n", name);
        f1 = fopen(name,"rb");
        if(!f1)
            error("%s no found", name);
        
        //printf("cmid %d\n", cmid);
        
        cmid_name = ReadUint(f1);
        if(cmid_name != 0x64696D63)//cmid
           error("No es un archivo (.pmd)\n");
           
        file_size = Swap32(ReadUint(f1));
        //printf("file_size %d\n", file_size);
        
        header_size = Swap16(ReadWord(f1));
        //printf("header_size %d\n", header_size);
        
        offset = ftell(f1)+header_size;
        //printf("offset %d\n", offset);
        
        //Skip init definitions
        fseek(f1, offset, SEEK_SET);
    
        trac_name = ReadUint(f1);
        if(trac_name != 0x63617274)//trac
           error("No conside el nombre [trac] offset %d\n", ftell(f1)-4);
           
        buffer_size = Swap32(ReadUint(f1));
        //printf("buffer_size %d\n", buffer_size);
        
        //aling 2
        ReadByte(f1); //unk pad
        /*offset = ftell(f1);
        offset += (unsigned int)offset & 1;
        fseek(f1, offset, SEEK_SET);
        printf("offset %d\n", offset);*/
        
        // Set buffer malloc
        buffer = (byte *)malloc(buffer_size);
        
        //copy data to buffer
        int cnt = 0;
        int data_size = 0;
        int data_offset = 0;
        while(cnt < buffer_size-1)
        {
           int code = ReadWord(f1);
           //printf("code %X, cnt %d\n", code, cnt);
           cnt += 2; 
           
           switch (code)
           {
              case 0xC3FF://unk
                   ReadWord(f1); cnt += 2; 
                   break;
              case 0xDEFF://unk
                   ReadWord(f1); cnt += 2; 
                   break;
              case 0xDFFF://unk
                   ReadByte(f1); cnt += 1; //unk
                   break;
              case 0xE8FF://unk
                   ReadWord(f1); cnt += 2; 
                   break;
              default:
                   error("code desconocido [%x] offset [%d]\n", code, ftell(f1)-2);
                   break;
              case 0xF1FF://block datasize
                   data_size = Swap16(ReadWord(f1))-7;  cnt += 2; 
                   //printf("data_size %d\n", data_size);
                   
                   int type = Swap16(ReadWord(f1));  cnt += 2; 
                   if(type != 0x44)
                        error("formato de tipo desconocido [%x] offset [%d]\n", type, ftell(f1)-2);
                        
                   int size = Swap32(ReadUint(f1));  cnt += 4; 
                   //printf("size %d\n", size);
                   
                   ReadByte(f1); cnt += 1; //unk
                   
                   for(int i = 0; i < data_size; i++)
                   {
                        buffer[data_offset] = ReadByte(f1);
                        cnt += 1;
                        data_offset++;
                   }
                   
                   ReadByte(f1); cnt += 1; //unk
                   
                   //printf("offset %d\n", ftell(f1));
                   //getch();
                   break;
              
           }
           
           //getch();
        }
        fclose(f1);
        
        //Write All QCP data
        f2 = fopen("PureVoice/tmp.qcp","wb");
        int RIFF = 0x46464952;
        int f_size = data_offset+186;
        fwrite (&RIFF, sizeof(uint), 1, f2);
        fwrite (&f_size, sizeof(uint), 1, f2);//file size
        fwrite (&QCPDATA, sizeof(QCPDATA), 1, f2);
        
        int data = 0x61746164;
        int b_size = data_offset/0x23;
        fwrite (&b_size, sizeof(uint), 1, f2);//block_data size
        fwrite (&data, sizeof(uint), 1, f2);
        fwrite (&data_offset, sizeof(uint), 1, f2);//data size
    
        for(int i = 0; i < data_offset; i++)
        {
           fputc(buffer[i], f2);
        }
        fclose(f2);
        
        free(buffer);
        
        //Convertir qcp a wav con PureVoice tool
        
        SHELLEXECUTEINFO ShExecInfo = {0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
        ShExecInfo.hwnd = NULL;
        ShExecInfo.lpVerb = NULL;
        ShExecInfo.lpFile = "QCP2WAV.bat";		
        ShExecInfo.lpParameters = "";	
        ShExecInfo.lpDirectory = "PureVoice";
        ShExecInfo.nShow = SW_HIDE;
        ShExecInfo.hInstApp = NULL;	
        ShellExecuteEx(&ShExecInfo);
        WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
        
        //Read Wav file
        f2 = fopen("PureVoice/tmp.wav","rb");
        
        fseek(f2, 0, SEEK_END);
        file_size = ftell(f2);
        fseek(f2, 0, SEEK_SET);
        
        // Set buffer malloc
        buffer = (byte *)malloc(file_size);
        
        for(int i = 0; i < file_size; i++)
        {
           buffer[i] = ReadByte(f2);
        }
        
        sprintf(name,"SOUND/%s.wav", names[k]);
        ZipAdd(hz, name, buffer, file_size);
        
        fclose(f2);
        free(buffer);
    }
    
    CloseZip(hz);
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
