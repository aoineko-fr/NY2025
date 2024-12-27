// ____________________________
// ██▀▀█▀▀██▀▀▀▀▀▀▀█▀▀█        │
// ██  ▀  █▄  ▀██▄ ▀ ▄█ ▄▀▀ █  │
// █  █ █  ▀▀  ▄█  █  █ ▀▄█ █▄ │
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀────────┘
//  New Year 2025 demo
//─────────────────────────────────────────────────────────────────────────────

// Segment		Content
//------------------------------------
// 0-3			Main program
//------------------------------------
// 4-5			Page #0
//------------------------------------
// 6-7			(empty)
//------------------------------------
// 8-15			Proj 3D
//------------------------------------
// 16-31		Muls

// Unit				Qm.n	Sign	Min		Max		Precision
//-----------------------------------------------------------------------------
// Screen Pos		Q8.0	U		0		255		1.0
// Mesh Vertex		Q8.0	S		-128	127		1.0
// Angle			Q8.0	U		0		255		1.0
// Sin/cos			Q2.6	S		-2		1.98	0.015625
// Vector 3D		Q10.6	S		-512	511.98	0.015625

//=============================================================================
// INCLUDES
//=============================================================================
#include "msxgl.h"
#include "color.h"
#include "draw.h"
#include "memory.h"
#include "psg.h"
#include "vgm/lvgm_player.h"
#include "ny2025_rawdef.h"

//=============================================================================
// DEFINES
//=============================================================================

// Library's logo
#define MSX_GL "\x01\x02\x03\x04\x05\x06"

// 2D point on screen
struct Vector2D
{
	u8 x;
	u8 y;
};

// Line between 2 points
struct Line
{
	u8 a; // Start point index
	u8 b; // End point index
};

// 2D vector
struct Vector3D
{
	u8 x;
	u8 y;
	u8 z;
};

#define PRIMITIVE_LINE			0
#define PRIMITIVE_LINE_STRIP	1

// 3D mesh
struct Primitive
{
	// u8 Type;
	const u8* Points;
	u8 PointNum;
};

// 3D mesh
struct Mesh
{
	// const struct Primitive* Primitives;
	// u8 PrimNum;
	const struct Vector3D* Points;
	u8 PointNum;
	const struct Line* Lines;
	u8 LineNum;
};

// 3D object
struct Object
{
	u8 ID;
	struct Vector3D Position;
	const struct Mesh* Shape;
	struct VDP_Command36* RenderBuffer[2];
	struct Point* Projected; 
};

// 3D letter points
#define W0							0
#define W1							5
#define W2							10
#define W3							15
#define W4							20
#define H0							0
#define H1							8
#define H2							16
#define H3							24
#define H4							32

// Hblank lines
#define HBANK_LINE_LOW				208
#define HBANK_LINE_HIGH				240

// Angle parameters
#define ANGLE_MAX					64
#define ANGLE_MASK					0x3F

// Function prototypes
void UpdateSprite();

//=============================================================================
// READ-ONLY DATA
//=============================================================================

// Fonts data
#include "font/font_mgl_sample6.h"

// Trigonometry tables
// #include "content/mt_trigo.h"
#include "mathtable/mt_trigo_64.inc"

// 
#include "content/lvgm_psg_honotori_09.h"

// Animation characters
const u8 g_ChrAnim[] = { '-', '/', '|', '\\' };

//.............................................................................
//	A
const struct Vector3D g_PointsA[] = { { W0, H0, 0 }, { W2, H4, 0 }, { W4, H0, 0 }, { W1, H2, 0 }, { W3, H2, 0 } };
const struct Line g_LinesA[] = { { 0, 1 }, { 1, 2 }, { 3, 4 } };
const struct Mesh g_MeshA = { g_PointsA, numberof(g_PointsA), g_LinesA, numberof(g_LinesA) };

//.............................................................................
//	E
const struct Vector3D g_PointsE[] = { { W4, H0, 0 }, { W0, H0, 0 }, { W0, H4, 0 }, { W4, H4, 0 }, { W0, H2, 0 }, { W3, H2, 0 } };
const struct Line g_LinesE[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 4, 5 } };
const struct Mesh g_MeshE = { g_PointsE, numberof(g_PointsE), g_LinesE, numberof(g_LinesE) };

//.............................................................................
//	H
const struct Vector3D g_PointsH[] = { { W0, H0, 0 }, { W0, H4, 0 }, { W4, H0, 0 }, { W4, H4, 0 }, { W0, H2, 0 }, { W4, H2, 0 } };
const struct Line g_LinesH[] = { { 0, 1 }, { 2, 3 }, { 4, 5 } };
const struct Mesh g_MeshH = { g_PointsH, numberof(g_PointsH), g_LinesH, numberof(g_LinesH) };

//.............................................................................
//	N
const struct Vector3D g_PointsN[] = { { W0, H0, 0 }, { W0, H4, 0 }, { W4, H0, 0 }, { W4, H4, 0 } };
const struct Line g_LinesN[] = { { 0, 1 }, { 1, 2 }, { 2, 3 } };
const struct Mesh g_MeshN = { g_PointsN, numberof(g_PointsN), g_LinesN, numberof(g_LinesN) };

//.............................................................................
//	P
const struct Vector3D g_PointsP[] = { { W0, H0, 0 }, { W0, H4, 0 }, { W2, H4, 0 }, { W4, H3, 0 }, { W2, H2, 0 }, { W0, H2, 0 } };
const struct Line g_LinesP[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 } };
const struct Mesh g_MeshP = { g_PointsP, numberof(g_PointsP), g_LinesP, numberof(g_LinesP) };

//.............................................................................
//	R
const struct Vector3D g_PointsR[] = { { W0, H0, 0 }, { W0, H4, 0 }, { W2, H4, 0 }, { W4, H3, 0 }, { W2, H2, 0 }, { W4, H0, 0 }, { W0, H2, 0 } };
const struct Line g_LinesR[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 4, 6 } };
const struct Mesh g_MeshR = { g_PointsR, numberof(g_PointsR), g_LinesR, numberof(g_LinesR) };

//.............................................................................
//	Y
const struct Vector3D g_PointsY[] = { { W0, H0, 0 }, { W4, H4, 0 }, { W0, H4, 0 }, { W2, H2, 0 } };
const struct Line g_LinesY[] = { { 0, 1 }, { 2, 3 } };
const struct Mesh g_MeshY = { g_PointsY, numberof(g_PointsY), g_LinesY, numberof(g_LinesY) };

//.............................................................................
//	W
const struct Vector3D g_PointsW[] = { { W0, H4, 0 }, { W1, H0, 0 }, { W2, H2, 0 }, { W3, H0, 0 }, { W4, H4, 0 } };
const struct Line g_LinesW[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }  };
const struct Mesh g_MeshW = { g_PointsW, numberof(g_PointsW), g_LinesW, numberof(g_LinesW) };

//.............................................................................
//	0
const struct Vector3D g_Points0[] = { { W0, H1, 0 }, { W0, H3, 0 }, { W1, H4, 0 }, { W3, H4, 0 }, { W4, H3, 0 }, { W4, H1, 0 }, { W3, H0, 0 }, { W1, H0, 0 } };
const struct Line g_Lines0[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 0 }  };
const struct Mesh g_Mesh0 = { g_Points0, numberof(g_Points0), g_Lines0, numberof(g_Lines0) };

//.............................................................................
//	2
const struct Vector3D g_Points2[] = { { W4, H0, 0 }, { W0, H0, 0 }, { W4, H3, 0 }, { W3, H4, 0 }, { W1, H4, 0 }, { W0, H3, 0 } };
const struct Line g_Lines2[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }  };
const struct Mesh g_Mesh2 = { g_Points2, numberof(g_Points2), g_Lines2, numberof(g_Lines2) };

//.............................................................................
//	5
const struct Vector3D g_Points5[] = { { W0, H0, 0 }, { W2, H0, 0 }, { W4, H1, 0 }, { W2, H2, 0 }, { W0, H2, 0 }, { W0, H4, 0 }, { W4, H4, 0 } };
const struct Line g_Lines5[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 }  };
const struct Mesh g_Mesh5 = { g_Points5, numberof(g_Points5), g_Lines5, numberof(g_Lines5) };

//.............................................................................
//	Cube
const struct Vector3D g_PointsCube[] = { { H0, H0, H0 }, { H0, H4, H0 }, { H4, H4, H0 }, { H4, H0, H0 }, { H0, H0, H4 }, { H0, H4, H4 }, { H4, H4, H4 }, { H4, H0, H4 }};
const struct Line g_LinesCube[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 0, 4 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }   };
const struct Mesh g_MeshCube = { g_PointsCube, numberof(g_PointsCube), g_LinesCube, numberof(g_LinesCube) };

// Snow flakes
#include "content/sprt_snow.h"

// Snow fall X coordinate offset
const i8 g_FallOffset[] = 
{
	2,	2,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	0,
	0,	0,	0,	-1,	0,	-1,	0,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-2,
	-2,	-2,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	0,	-1,	0,	-1,	0,	0,
	0,	0,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	2
};

const i16 g_ProjTable[] = { 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 3, 3, 2, 2, 2 };

//=============================================================================
// VARIABLES
//=============================================================================

// Sprite attributes
struct VDP_Sprite g_SpriteData0[32];

// Synch render
bool g_VSynch = false;
u8 g_LoopCount = 0;
u8 g_FrameCount = 0;
u8 g_ShowPage = 0;
u8 g_DrawPage = 1;
u8 g_State = 0;
bool g_MusicPlay = FALSE;

//=============================================================================
// FUNCTIONS
//=============================================================================

#define F_VDP_REG			0x80 // VDP register write port (bit 7=1 in second write)
#define F_VDP_VRAM			0x00 // VRAM address register (bit 7=0 in second write)
#define F_VDP_WRIT			0x40 // bit 6: read/write access (1=write)
#define F_VDP_READ			0x00 // bit 6: read/write access (0=read)

#define VDP_REG(_r)			(F_VDP_REG | _r)

//-----------------------------------------------------------------------------
// Multiply two signed 8-bit integers using a lookup table
inline i16 MultiplyS8(i8 a, i8 b)
{
	u8 seg = MT_MULS_BIN_SEG + ((u8)a >> 4);
	SET_BANK_SEGMENT(3, seg);
	return (i16)Peek16(0xA000 + ((u8)a & 0x0F) * 512 + (u8)b * 2);
}

//-----------------------------------------------------------------------------
// H-Blank handler
void VDP_HBlankHandler()
{
	if(g_State == 0) // 212
	{
		VDP_SetColor(COLOR_WHITE);
		VDP_SetHBlankLine(HBANK_LINE_HIGH);
		g_State++; // = 1
	}
	else // 240
	{
		VDP_SetColor(COLOR_BLACK);
		VDP_SetHBlankLine(HBANK_LINE_LOW);
		g_State--; // = 0
	}
}

//-----------------------------------------------------------------------------
// V-blank interrupt andler
void VDP_InterruptHandler()
{
	g_VSynch = TRUE;
	g_FrameCount++;

	if (g_MusicPlay)
		LVGM_Decode();
}

//-----------------------------------------------------------------------------
// V-blank interrupt andler
void WaitVBlank()
{
	while(!g_VSynch) {}
	g_VSynch = FALSE;
	g_LoopCount++;
}

//-----------------------------------------------------------------------------
//
void Object_DrawCommand(const void* buffer)
{
	buffer; // HL
	__asm
		ld		a, #36
		di
		out		(P_VDP_ADDR), a
		ld		a, #VDP_REG(17)
		out		(P_VDP_ADDR), a
		ld		c, #P_VDP_IREG
	.rept 11
		outi
	.endm
		ei
	__endasm;	
}

void CommandWait() //__PRESERVES(c, d, e, h, l, iyl, iyh)
{
	__asm
	wait_vdp_ready:

		// Set current status register to S#2
		ld		a, #2
		di //~~~~~~~~~~~~~~~~~~~~~~~~~~
		out		(P_VDP_REG), a
		ld		a, #VDP_REG(15)
		out		(P_VDP_REG), a
		in		a, (P_VDP_STAT)		// get S#2 value
		rra							// check CE (bit#0)

		// Reset current status register to S#0 before enabling interruptions
		ld		a, #0				// don't use XOR here to keep C flag from RRA alive
		out		(P_VDP_REG), a
		ld		a, #VDP_REG(15)
		ei //~~~~~~~~~~~~~~~~~~~~~~~~~~
		out		(P_VDP_REG), a
		jp		c, wait_vdp_ready	// CE==1 ? command not finished

	__endasm;
}

//-----------------------------------------------------------------------------
// Rotate a point around an origin
void Vector_RotateZ(struct Vector3D* point, u8 z)
{
	// u8 x = point->x;
	// u8 y = point->y;
	// point->x = (u8)(((x * g_Cosinus256[z]) >> 6 - (y * g_Sinus256[z]) >> 6));
	// point->y = (u8)(((x * g_Sinus256[z]) >> 6 + (y * g_Cosinus256[z]) >> 6));
}

//-----------------------------------------------------------------------------
// Draw an object
void Object_Init(struct Object* obj)
{
	const struct Mesh* mesh = obj->Shape;
	// const struct Point* pt = mesh->Points;
	// const struct Line* line = mesh->Lines;

	loop(i, 2)
		obj->RenderBuffer[i] = (struct VDP_Command36*)Mem_HeapAlloc(mesh->LineNum * sizeof(struct VDP_Command36));

	obj->Projected = (struct Point*)Mem_HeapAlloc(mesh->PointNum * sizeof(struct Point));
}

//-----------------------------------------------------------------------------
// Draw an object
u8 Object_Clear(struct Object* obj)
{
	const struct Mesh* mesh = obj->Shape;
	struct VDP_Command36* cmd = obj->RenderBuffer[g_DrawPage];
	for (u8 i = 0; i < mesh->LineNum; i++)
	{
		cmd->CLR = COLOR_TRANSPARENT;
		cmd->CMD = VDP_CMD_LINE;
		CommandWait();
		Object_DrawCommand((const void*)cmd);
		cmd++;
	}
}

//-----------------------------------------------------------------------------
// Draw an object
void Object_Draw(struct Object* obj, u8 color)
{
	g_VDP_Command.CLR = color;
	g_VDP_Command.CMD = VDP_CMD_LINE;

	const struct Mesh* mesh = obj->Shape;
	i16 objPosX = obj->Position.x;
	i16 objPosY = obj->Position.y;
	i16 objPosZ = obj->Position.z;

	// Do screen projection
	const struct Vector3D* pt = mesh->Points;
	struct Point* proj = obj->Projected;
	for (u8 i = 0; i < mesh->PointNum; i++)
	{
		// struct Vector3D p0 = { pt->x, pt->y, pt->z };
		// Vector_RotateZ(&p0, g_FrameCount & 0x3F);
		// i16 x1 = objPosX + p0.x;
		// i16 y1 = objPosY - p0.y;
		// i16 z1 = objPosZ + p0.z;

		i16 x1 = objPosX + pt->x;
		i16 y1 = objPosY - pt->y;
		i16 z1 = objPosZ + pt->z;
		u8 seg = MT_PROJ256_BIN_SEG + ((u8)z1 / 32);
		SET_BANK_SEGMENT(3, seg);
		proj->x = PEEK(0xA000 + (z1 & 0x1F) * 256 + x1);
		proj->y = PEEK(0xA000 + (z1 & 0x1F) * 256 + y1);
		pt++;
		proj++;
	}

	// Render mesh primitives
	const struct Line* line = mesh->Lines;
	struct VDP_Command36* cmd = obj->RenderBuffer[g_DrawPage];
	for (u8 i = 0; i < mesh->LineNum; i++)
	{
		const struct Point* pt1 = &obj->Projected[line->a];
		i16 x1 = pt1->x;
		i16 y1 = pt1->y;
		const struct Point* pt2 = &obj->Projected[line->b];
		i16 x2 = pt2->x;
		i16 y2 = pt2->y;

		u16 dx, dy, nx, ny;
		u8 arg = 0;
		if(x1 > x2)
		{
			arg |= VDP_ARG_DIX_LEFT;
			dx = x1 - x2 /*+ 1*/;
		}
		else // (x1 <= x2)
		{
			arg |= VDP_ARG_DIX_RIGHT;
			dx = x2 - x1 /*+ 1*/;
		}
		if(y1 > y2)
		{
			arg |= VDP_ARG_DIY_UP;
			dy = y1 - y2 /*+ 1*/;
		}
		else // (y1 <= y2)
		{
			arg |= VDP_ARG_DIY_DOWN;
			dy = y2 - y1 /*+ 1*/;
		}
		if(dx > dy)
		{
			arg |= VDP_ARG_MAJ_H;
			nx = dx;
			ny = dy;
		}
		else // (dx <= dy)
		{
			arg |= VDP_ARG_MAJ_V;
			nx = dy;
			ny = dx;
		}

		g_VDP_Command.DX = x1;
		g_VDP_Command.DY = y1;
		if(g_DrawPage == 1)
			g_VDP_Command.DY += 256;
		g_VDP_Command.NX = nx;
		g_VDP_Command.NY = ny;
		g_VDP_Command.ARG = arg;
		CommandWait();
		Object_DrawCommand((const void*)((u16)g_VDP_Command + 4));

		Mem_Copy((const void*)((u16)g_VDP_Command + 4), (void*)cmd, sizeof(struct VDP_Command36));
		cmd++;
		line++;
	}
}

//-----------------------------------------------------------------------------
//
void InitializeSprite()
{
	// Initialize Sprite
	VDP_EnableSprite(TRUE);
	VDP_SetSpriteFlag(VDP_SPRITE_SIZE_16);
	VDP_LoadSpritePattern(g_SnowPattern, 0, sizeof(g_SnowPattern) / 8);
	loop(j, 32)
	{
		struct VDP_Sprite* sprt = &g_SpriteData0[j];
		sprt->X = Math_GetRandom8();
		sprt->Y = 255;
		while (sprt->Y > 212 + 16)
			sprt->Y = Math_GetRandom8();
		sprt->Y -= 16;
		sprt->Pattern = (j & 0x03) * 4;
		sprt->Color = j < 24 ? COLOR_WHITE : COLOR_GRAY;
		VDP_SetSpriteExUniColor(j, sprt->X, sprt->Y, sprt->Pattern, sprt->Color);
	}
}

//-----------------------------------------------------------------------------
//
void UpdateSprite()
{
	u8 offset = g_FrameCount >> 1;
	struct VDP_Sprite* sprt = g_SpriteData0;
	loop(i, 32)
	{
		sprt->X += g_FallOffset[offset & 0x3F];
		offset += 2;
		sprt->Y++;
		if((sprt->Y >= 212) && (sprt->Y < 240))
			sprt->Y = 240; // 256 - 16
		sprt++;
	}
	VDP_WriteVRAM((const u8*)g_SpriteData0, g_SpriteAtributeLow, g_SpriteAtributeHigh, 32 * 4);
}

//-----------------------------------------------------------------------------
// Program entry point
void main()
{
	VDP_SetMode(VDP_MODE_SCREEN5);
	VDP_SetColor(COLOR_BLACK);
	VDP_EnableDisplay(FALSE);
	VDP_SetLineCount(VDP_LINE_212);
	VDP_SetFrequency(VDP_FREQ_60HZ);
	VDP_ClearVRAM();

	Print_SetBitmapFont(g_Font_MGL_Sample6);
	Print_SetColor(COLOR_GRAY, COLOR_TRANSPARENT);
	Print_DrawTextAt(0, 0, MSX_GL);
	Print_DrawTextAt(0, 256, MSX_GL);

	#define OBJ_NUM 16
	struct Object obj[OBJ_NUM] = {
		// { 0, { 64, 64, 0 }, &g_MeshCube },

		{ 0, { 32 + 25 * 0, 32, 0 }, &g_MeshH },
		{ 1, { 32 + 25 * 1, 32, 0 }, &g_MeshA },
		{ 2, { 32 + 25 * 2, 32, 0 }, &g_MeshP },
		{ 3, { 32 + 25 * 3, 32, 0 }, &g_MeshP },
		{ 4, { 32 + 25 * 4, 32, 0 }, &g_MeshY },

		{ 5, { 32 + 25 * 6, 32, 0 }, &g_MeshN },
		{ 6, { 32 + 25 * 7, 32, 0 }, &g_MeshE },
		{ 7, { 32 + 25 * 8, 32, 0 }, &g_MeshW },

		{  8, { 32 + 25 * 0, 160, 0 }, &g_MeshY },
		{  9, { 32 + 25 * 1, 160, 0 }, &g_MeshE },
		{ 10, { 32 + 25 * 2, 160, 0 }, &g_MeshA },
		{ 11, { 32 + 25 * 3, 160, 0 }, &g_MeshR },

		{ 12, { 32 + 25 * 5, 160, 0 }, &g_Mesh2 },
		{ 13, { 32 + 25 * 6, 160, 0 }, &g_Mesh0 },
		{ 14, { 32 + 25 * 7, 160, 0 }, &g_Mesh2 },
		{ 15, { 32 + 25 * 8, 160, 0 }, &g_Mesh5 },
	};
	loop(i, OBJ_NUM)
		Object_Init(&obj[i]);

	InitializeSprite();

	Draw_LineH(0, 255, 211, COLOR_WHITE, 0);
	Draw_LineH(0, 255, 211 + 256, COLOR_WHITE, 0);

	VDP_EnableVBlank(TRUE);
	VDP_EnableHBlank(TRUE);
	VDP_SetHBlankLine(HBANK_LINE_LOW);
	VDP_EnableDisplay(TRUE);

	LVGM_Play(g_lVGM_psg_honotori_09, TRUE);
	g_MusicPlay = TRUE;

	u8 count = 0;
	while(1)
	{
		WaitVBlank(); // Wait for V-Blank interruption signal

		g_ShowPage = 1 - g_ShowPage;
		g_DrawPage = 1 - g_DrawPage;
		VDP_SetPage(g_ShowPage);

		// Update sprites
		UpdateSprite();

		// Clear 3d vector
		struct Object* o = &obj[0];
		if (count)
		{
			loop(i, OBJ_NUM)
			{
				Object_Clear(o);
				o++;
			}
		}
		count = 1;

		// Draw 3d vector
		o = &obj[0];
		loop(i, OBJ_NUM)
		{
			// o->Position.x--;
			// o->Position.x = 32 + (((i16)g_Sinus256[g_FrameCount / 2]) / 128);
			o->Position.y = i < 8 ? 128 - 32 - H2 : 128 + 32 - H2;
			o->Position.y += (((i16)g_Sinus64[i + g_FrameCount & 0x3F]) / 256);
			o->Position.z = 32 + (((i16)g_Sinus64[i + g_FrameCount / 2 & 0x3F]) / 256);

			Object_Draw(o, g_FrameCount & 0b0100000 ? COLOR_LIGHT_RED : COLOR_LIGHT_GREEN);
			o++;
		}
	}
}