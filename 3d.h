// ____________________________
// ██▀▀█▀▀██▀▀▀▀▀▀▀█▀▀█        │
// ██  ▀  █▄  ▀██▄ ▀ ▄█ ▄▀▀ █  │
// █  █ █  ▀▀  ▄█  █  █ ▀▄█ █▄ │
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀────────┘
//  New Year 2025 demo
//─────────────────────────────────────────────────────────────────────────────

#pragma once
#include "msxgl.h"


// Screen coordinates (Q8.0)
typedef struct
{
	u8 x;
	u8 y;
	u8 z;
} Point;

// Line between 2 points
typedef struct
{
	u8 a; // Start point index
	u8 b; // End point index
} Line;

// Mesh vertex (Q8.0)
typedef struct
{
	i8 x;
	i8 y;
	i8 z;
} Vertex;

// Space coordinates (Q10.6)
typedef struct
{
	i16 x;
	i16 y;
	i16 z;
} Vector;

#define PRIMITIVE_LINE			0
#define PRIMITIVE_LINE_STRIP	1

// 3D mesh
typedef struct 
{
	// u8 Type;
	const u8* Points;
	u8 PointNum;
} Primitive;

// 3D mesh
typedef struct
{
	// const struct Primitive* Primitives;
	// u8 PrimNum;
	const Vertex* Points;
	u8 PointNum;
	const Line* Lines;
	u8 LineNum;
} Mesh;

typedef void (*TransformCB)(Vertex* point, Vector* rot);

// 3D object
typedef struct
{
	u8 ID;
	Vector Position;
	Vector Rotation;
	const Mesh* Shape;
	TransformCB Transform;
	struct VDP_Command36* RenderBuffer[2];
	Point* Projected; 
} Object;

// 3D letter points
#define W0							-10
#define W1							-5
#define W2							0
#define W3							5
#define W4							10
#define H0							-16
#define H1							-8
#define H2							0
#define H3							8
#define H4							16