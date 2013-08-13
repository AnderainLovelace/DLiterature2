#include "dl2_all.h"

void draw_picture (int x,int y,int width,int height,int mode,uchar * pGraph)
{
	DISPGRAPH dg;

	dg.x					= x;
	dg.y					= y;
	dg.GraphData.width		= width;
	dg.GraphData.height		= height;
	dg.GraphData.pBitmap	= pGraph;
	dg.WriteModify			= mode+1;
	dg.WriteKind			= IMB_WRITEKIND_OVER;

	Bdisp_WriteGraph_VRAM(&dg);
}

void area_clear (int left,int top,int right,int bottom,int sel) 
{ 
	DISPBOX box; 
	box.left = left;box.top = top;box.right = right;box.bottom = bottom; 
 	if (sel != 1) 
		Bdisp_AreaClr_VRAM (&box); 
	if (sel != 0){ 
 		Bdisp_DrawLineVRAM (box.left,box.top,box.right,box.top); 
		Bdisp_DrawLineVRAM (box.left,box.bottom,box.right,box.bottom); 
		Bdisp_DrawLineVRAM (box.left,box.top,box.left,box.bottom); 
		Bdisp_DrawLineVRAM (box.right,box.top,box.right,box.bottom); 
    } 
}