// ____________________________
// ██▀▀█▀▀██▀▀▀▀▀▀▀█▀▀█        │
// ██  ▀  █▄  ▀██▄ ▀ ▄█ ▄▀▀ █  │
// █  █ █  ▀▀  ▄█  █  █ ▀▄█ █▄ │
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀────────┘
//  New Year 2025 demo
//─────────────────────────────────────────────────────────────────────────────

#include "msxgl.h"
#include "3d.h"

//.............................................................................
//	A
const Vertex g_PointsA[] = { { W0, H0, 0 }, { W2, H4, 0 }, { W4, H0, 0 }, { W1, H2, 0 }, { W3, H2, 0 } };
const Line g_LinesA[] = { { 0, 1 }, { 1, 2 }, { 3, 4 } };
const Mesh g_MeshA = { g_PointsA, numberof(g_PointsA), g_LinesA, numberof(g_LinesA) };

//.............................................................................
//	E
const Vertex g_PointsE[] = { { W4, H0, 0 }, { W0, H0, 0 }, { W0, H4, 0 }, { W4, H4, 0 }, { W0, H2, 0 }, { W3, H2, 0 } };
const Line g_LinesE[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 4, 5 } };
const Mesh g_MeshE = { g_PointsE, numberof(g_PointsE), g_LinesE, numberof(g_LinesE) };

//.............................................................................
//	H
const Vertex g_PointsH[] = { { W0, H0, 0 }, { W0, H4, 0 }, { W4, H0, 0 }, { W4, H4, 0 }, { W0, H2, 0 }, { W4, H2, 0 } };
const Line g_LinesH[] = { { 0, 1 }, { 2, 3 }, { 4, 5 } };
const Mesh g_MeshH = { g_PointsH, numberof(g_PointsH), g_LinesH, numberof(g_LinesH) };

//.............................................................................
//	N
const Vertex g_PointsN[] = { { W0, H0, 0 }, { W0, H4, 0 }, { W4, H0, 0 }, { W4, H4, 0 } };
const Line g_LinesN[] = { { 0, 1 }, { 1, 2 }, { 2, 3 } };
const Mesh g_MeshN = { g_PointsN, numberof(g_PointsN), g_LinesN, numberof(g_LinesN) };

//.............................................................................
//	P
const Vertex g_PointsP[] = { { W0, H0, 0 }, { W0, H4, 0 }, { W2, H4, 0 }, { W4, H3, 0 }, { W2, H2, 0 }, { W0, H2, 0 } };
const Line g_LinesP[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 } };
const Mesh g_MeshP = { g_PointsP, numberof(g_PointsP), g_LinesP, numberof(g_LinesP) };

//.............................................................................
//	R
const Vertex g_PointsR[] = { { W0, H0, 0 }, { W0, H4, 0 }, { W2, H4, 0 }, { W4, H3, 0 }, { W2, H2, 0 }, { W4, H0, 0 }, { W0, H2, 0 } };
const Line g_LinesR[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 4, 6 } };
const Mesh g_MeshR = { g_PointsR, numberof(g_PointsR), g_LinesR, numberof(g_LinesR) };

//.............................................................................
//	Y
const Vertex g_PointsY[] = { { W0, H0, 0 }, { W4, H4, 0 }, { W0, H4, 0 }, { W2, H2, 0 } };
const Line g_LinesY[] = { { 0, 1 }, { 2, 3 } };
const Mesh g_MeshY = { g_PointsY, numberof(g_PointsY), g_LinesY, numberof(g_LinesY) };

//.............................................................................
//	W
const Vertex g_PointsW[] = { { W0, H4, 0 }, { W1, H0, 0 }, { W2, H2, 0 }, { W3, H0, 0 }, { W4, H4, 0 } };
const Line g_LinesW[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } };
const Mesh g_MeshW = { g_PointsW, numberof(g_PointsW), g_LinesW, numberof(g_LinesW) };

//.............................................................................
//	M
const Vertex g_PointsM[] = { { W0/2, H0/2, 0 }, { W0/2, H4/2, 0 }, { W2/2, H2/2, 0 }, { W4/2, H4/2, 0 }, { W4/2, H0/2, 0 } };
const Line g_LinesM[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } };
const Mesh g_MeshM = { g_PointsM, numberof(g_PointsM), g_LinesM, numberof(g_LinesM) };

//.............................................................................
//	S
const Vertex g_PointsS[] = { { W0/2, H0/2, 0 }, { W2/2, H0/2, 0 }, { W4/2, H1/2, 0 }, { W0/2, H3/2, 0 }, { W2/2, H4/2, 0 }, { W4/2, H4/2, 0 } };
const Line g_LinesS[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 } };
const Mesh g_MeshS = { g_PointsS, numberof(g_PointsS), g_LinesS, numberof(g_LinesS) };

//.............................................................................
//	X
const Vertex g_PointsX[] = { { W0/2, H0/2, 0 }, { W4/2, H4/2, 0 }, { W0/2, H4/2, 0 }, { W4/2, H0/2, 0 } };
const Line g_LinesX[] = { { 0, 1 }, { 2, 3 } };
const Mesh g_MeshX = { g_PointsX, numberof(g_PointsX), g_LinesX, numberof(g_LinesX) };

//.............................................................................
//	0
const Vertex g_Points0[] = { { W0, H1, 0 }, { W0, H3, 0 }, { W1, H4, 0 }, { W3, H4, 0 }, { W4, H3, 0 }, { W4, H1, 0 }, { W3, H0, 0 }, { W1, H0, 0 } };
const Line g_Lines0[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 0 } };
const Mesh g_Mesh0 = { g_Points0, numberof(g_Points0), g_Lines0, numberof(g_Lines0) };

//.............................................................................
//	2
const Vertex g_Points2[] = { { W4, H0, 0 }, { W0, H0, 0 }, { W4, H3, 0 }, { W3, H4, 0 }, { W1, H4, 0 }, { W0, H3, 0 } };
const Line g_Lines2[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 } };
const Mesh g_Mesh2 = { g_Points2, numberof(g_Points2), g_Lines2, numberof(g_Lines2) };

//.............................................................................
//	5
const Vertex g_Points5[] = { { W0, H0, 0 }, { W2, H0, 0 }, { W4, H1, 0 }, { W2, H2, 0 }, { W0, H2, 0 }, { W0, H4, 0 }, { W4, H4, 0 } };
const Line g_Lines5[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 } };
const Mesh g_Mesh5 = { g_Points5, numberof(g_Points5), g_Lines5, numberof(g_Lines5) };

//.............................................................................
//	Cube
const Vertex g_PointsCube[] = { { -16, -16, -16 }, { -16, 16, -16 }, { 16, 16, -16 }, { 16, -16, -16 }, { -16, -16, 16 }, { -16, 16, 16 }, { 16, 16, 16 }, { 16, -16, 16 }};
const Line g_LinesCube[] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 0, 4 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 } };
const Mesh g_MeshCube = { g_PointsCube, numberof(g_PointsCube), g_LinesCube, numberof(g_LinesCube) };