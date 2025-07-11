#ifndef RANDOMUNCATEGORIZEDBULLSHIT_H
#define RANDOMUNCATEGORIZEDBULLSHIT_H

void bs_genMtxArrForTheTree(float* vertpos, uint8_t* mtxArr, int tricount) {//mtxarr is 1/3 the length of vertpos
	float centerrad = 1.0f;
	float middlecut = 5.5f;

	for(int i = 0; i < tricount * 3; i++) { //once per vertex
		mtxArr[i] = 0;
		//write this again kill yourself
		if (vertpos[(i*3)+1] >= middlecut) {
			if (vertpos[(i*3)] >= 0) {
				if (vertpos[(i*3)+2] >= 0) {
					//Top right front
					mtxArr[i] = 2;
				} else {
					//Top right back
					mtxArr[i] = 3;
				}
			} else {
				if (vertpos[(i*3)+2] >= 0) {
					//Top left front
					mtxArr[i] = 1;
				} else {
					//Top left back
					mtxArr[i] = 4;
				}
			}
		} else {
			if (vertpos[(i*3)] >= 0) {
				if (vertpos[(i*3)+2] >= 0) {
					//Bottom right front
					mtxArr[i] = 6;
				} else {
					//Bottom right back
					mtxArr[i] = 7;
				}
			} else {
				if (vertpos[(i*3)+2] >= 0) {
					//Bottom left front
					mtxArr[i] = 5;
				} else {
					//Bottom left back
					mtxArr[i] = 8;
				}
			}
		}
		if ( sqrt( fsq(0 - vertpos[(i*3)]) + fsq(0 - vertpos[(i*3)+2]) ) < centerrad ) { //what
			mtxArr[i] = 0;
		}	
	}	
}

void bs_loadTreeMatricies(Mtx view, float x, float y, float z, int frame) {
	Mtx treemtx[9];
	Mtx treemodelview[9];
	Mtx treemvi[9];
	for(int i = 0; i < 9; i++) {
		guMtxIdentity(treemtx[i]);
		guMtxTransApply(treemtx[i], treemtx[i], x, y, z);
	}
	float wavespeed = 0.01f;
	for(int i = 1; i < 9; i++) {
		guMtxTransApply(treemtx[i], treemtx[i], 0.0f, (cosf(   ( ((float)frame * wavespeed) + (float)i * 0.5 )    ) * 0.05), 0.0f);
		Mtx rotmtx;
		guMtxRotAxisDeg(rotmtx, &yAxis, (sinf(   ( ((float)frame * wavespeed) + (float)i * 0.5 )    ) * 2.0f));
		guMtxConcat(treemtx[i], rotmtx, treemtx[i]);
	}
	for(int i = 0; i < 9; i++) {
		guMtxConcat(view, treemtx[i], treemodelview[i]);
	}
	GX_LoadPosMtxImm(treemodelview[0], GX_PNMTX0);
	GX_LoadPosMtxImm(treemodelview[1], GX_PNMTX1);
	GX_LoadPosMtxImm(treemodelview[2], GX_PNMTX2);
	GX_LoadPosMtxImm(treemodelview[3], GX_PNMTX3);
	GX_LoadPosMtxImm(treemodelview[4], GX_PNMTX4);
	GX_LoadPosMtxImm(treemodelview[5], GX_PNMTX5);
	GX_LoadPosMtxImm(treemodelview[6], GX_PNMTX6);
	GX_LoadPosMtxImm(treemodelview[7], GX_PNMTX7);
	GX_LoadPosMtxImm(treemodelview[8], GX_PNMTX8);
	for(int i = 0; i < 9; i++) {
		guMtxInverse(treemodelview[i], treemvi[i]);
		guMtxTranspose(treemvi[i], treemodelview[i]);
	}
	GX_LoadNrmMtxImm(treemodelview[0], GX_PNMTX0);
	GX_LoadNrmMtxImm(treemodelview[1], GX_PNMTX1);
	GX_LoadNrmMtxImm(treemodelview[2], GX_PNMTX2);
	GX_LoadNrmMtxImm(treemodelview[3], GX_PNMTX3);
	GX_LoadNrmMtxImm(treemodelview[4], GX_PNMTX4);
	GX_LoadNrmMtxImm(treemodelview[5], GX_PNMTX5);
	GX_LoadNrmMtxImm(treemodelview[6], GX_PNMTX6);
	GX_LoadNrmMtxImm(treemodelview[7], GX_PNMTX7);
	GX_LoadNrmMtxImm(treemodelview[8], GX_PNMTX8);
}

f32 testcamDataAahAah[] = {
1.000000f, -0.000000f, 0.000000f, -0.020120f,
-0.000000f, -0.000000f, 1.000000f, -0.842734f,
0.000000f, -1.000000f, -0.000000f, -4.118052f
};

void setTestCam(Mtx view) {
	view[0][0] = testcamDataAahAah[0];
	view[0][1] = testcamDataAahAah[1];
	view[0][2] = testcamDataAahAah[2];
	view[0][3] = testcamDataAahAah[3];
	view[1][0] = testcamDataAahAah[4];
	view[1][1] = testcamDataAahAah[5];
	view[1][2] = testcamDataAahAah[6];
	view[1][3] = testcamDataAahAah[7];
	view[2][0] = testcamDataAahAah[8];
	view[2][1] = testcamDataAahAah[9];
	view[2][2] = testcamDataAahAah[10];
	view[2][3] = testcamDataAahAah[11];
	return;
}

#include "randomuncategorizeddata/load.h"

void drawLoad() {
	GX_SetCopyClear(LC_BLACK, 0x00ffffff);

	Mtx model, modelview;

	GX_SetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
	GX_LoadProjectionMtx(overlayPersp, GX_PERSPECTIVE);
	liy_VtxDescConfig(LV_VP | LV_VC, GX_VTXFMT0);
	GX_SetNumTevStages(1);	
	nolight();
	GX_SetChanAmbColor(GX_COLOR0A0,LC_WHITE);
	GX_SetTevOp(GX_TEVSTAGE0,GX_PASSCLR);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GX_SetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ONE, GX_CC_ONE, GX_CC_ONE); //too tired to do this in a civil way
	guMtxIdentity(model);
	guMtxTransApply(model, model, 0.0f, 0.0f, -5.0f);
	guMtxConcat(overlayView, model, modelview);
	GX_LoadPosMtxImm(modelview, GX_PNMTX0);
	GX_SetCurrentMtx(GX_PNMTX0);


	drawArrDirectPC_UniformCol(loadTriData, LOADTRICOUNT, &LC_WHITE, GX_VTXFMT0);
		

	GX_SetCopyClear(background, 0x00ffffff);

	GX_CopyDisp(frameBuffer[fb],GX_TRUE);

	GX_DrawDone();

	VIDEO_SetBlack(false);

	VIDEO_SetNextFramebuffer(frameBuffer[fb]);
	VIDEO_Flush();
	VIDEO_WaitVSync();

	fb ^= 1;
}

int liy_bufPos(int x, int y, int bufwidth) {
	return x+(y*bufwidth);
}

/*void alphabeltCalcRightbound() {
	for (int i = 0; i < NUM_LETTERS; i++) {
		for (int j = 0; j < alphabetTricounts[i] * 3; j++) {
			alphabetRightbounds[i] = liym_max(alphabetRightbounds[i], alphabetVertpos[i][(j*3)]);
		}
		printf("%f\r", alphabetRightbounds[i]);
	}
	alphabetRightbounds[29] = 0.25f; // space width
}*/

int alphTableIndexFromChar(char c) {
	switch(c) {
		case 'a':
			return 0;
		case 'b':
			return 1;
		case 'c':
			return 2;
		case 'd':
			return 3;
		case 'e':
			return 4;
		case 'f':
			return 5;
		case 'g':
			return 6;
		case 'h':
			return 7;
		case 'i':
			return 8;
		case 'j':
			return 9;
		case 'k':
			return 10;
		case 'l':
			return 11;
		case 'm':
			return 12;
		case 'n':
			return 13;
		case 'o':
			return 14;
		case 'p':
			return 15;
		case 'q':
			return 16;
		case 'r':
			return 17;
		case 's':
			return 18;
		case 't':
			return 19;
		case 'u':
			return 20;
		case 'v':
			return 21;
		case 'w':
			return 22;
		case 'x':
			return 23;
		case 'y':
			return 24;
		case 'z':
			return 25;
		case '(':
			return 26;
		case ')':
			return 27;
		case '?':
			return 28;
		case ' ':
			return 29;
		case '\'':
			return 30;
		case ',':
			return 31;
		case '!':
			return 32;
		case '.':
			return 33;
		default:
			return 28;
	
	}
}

int basicStringsFrame;

void basicRenderString(char *letters) {
	/*Mtx model, modelview;
	GX_SetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
	GX_SetCurrentMtx(GX_PNMTX0);

	GX_LoadProjectionMtx(overlayPersp, GX_PERSPECTIVE);

	liy_VtxDescConfig(LV_VP | LV_VC, GX_VTXFMT0);
		
	GX_SetNumTevStages(1);	
	nolight();

	GX_SetTevOp(GX_TEVSTAGE0,GX_PASSCLR);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);

	GX_SetChanCtrl(GX_COLOR0A0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHTNULL, GX_DF_CLAMP, GX_AF_NONE);	

	float overscanPadding = 0.0f;
	float lineSpacing = 0.7f;
	float charSpacing = 0.01f;

	float hozpoz = (widescreen) ? -8.0f + overscanPadding : -6.0f + overscanPadding;

	for(int i = 0; i < strlen(letters); i++) {
		int atablei = alphTableIndexFromChar(letters[i]);
		if(i != 0){hozpoz += alphabetRightbounds[alphTableIndexFromChar(letters[i - 1])] + charSpacing;}

		guMtxIdentity(model);
		guMtxTransApply(model, model, hozpoz, 4.0f - (((f32)basicStringsFrame * lineSpacing) + overscanPadding)  ,-10.0f);
		//guMtxTransApply(model, model, ((f32)i * charSpacing) - lorigin, 4.0f - ((f32)basicStringsFrame * lineSpacing)  ,-10.0f);
		guMtxConcat(overlayView,model,modelview);
		GX_LoadPosMtxImm(modelview, GX_PNMTX0);
		GX_LoadNrmMtxImm(modelview, GX_PNMTX0);

		drawArrDirectPC_UniformCol(alphabetVertpos[atablei], alphabetTricounts[atablei], &LC_BLACK, GX_VTXFMT0);
	}
	basicStringsFrame++;*/
}

//liy button
   #define LIYB_UP 0b10000000
#define LIYB_RIGHT 0b01000000
 #define LIYB_DOWN 0b00100000
 #define LIYB_LEFT 0b00010000
    #define LIYB_A 0b00001000
    #define LIYB_B 0b00000100
    #define LIYB_1 0b00000010
    #define LIYB_2 0b00000001

void dbgRefresh() {
	GX_SetCopyClear(background, 0x00ffffff);

	GX_CopyDisp(frameBuffer[fb],GX_TRUE);

	GX_DrawDone();

	VIDEO_SetBlack(false);

	VIDEO_SetNextFramebuffer(frameBuffer[fb]);
	VIDEO_Flush();
	VIDEO_WaitVSync();

	fb ^= 1;
}

void liyrub_drawScreenquad(f32 scale) {
	liy_VtxDescConfig(LV_VP | LV_TC, 0);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(-1.0f, -1.0f, 0.0f);
		GX_TexCoord2f32(0.0f, scale);
		GX_Position3f32(1.0f, -1.0f, 0.0f);
		GX_TexCoord2f32(scale, scale);
		GX_Position3f32(1.0f, 1.0f, 0.0f);
		GX_TexCoord2f32(scale, 0.0f);
		GX_Position3f32(-1.0f, 1.0f, 0.0f);
		GX_TexCoord2f32(0.0f, 0.0f);
}

void liyrub_drawRotScreenquad(f32 scale) {
	liy_VtxDescConfig(LV_VP | LV_TC, 0);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(-1.0f, -1.0f, 0.0f);

		GX_TexCoord2f32(scale, 1.0f);

		GX_Position3f32(1.0f, -1.0f, 0.0f);

		GX_TexCoord2f32(scale, 1.0f - scale);

		GX_Position3f32(1.0f, 1.0f, 0.0f);

		GX_TexCoord2f32(0.0f, 1.0f - scale);

		GX_Position3f32(-1.0f, 1.0f, 0.0f);

		GX_TexCoord2f32(0.0f, 1.0f);
}

void seeds() {
	float tcscal = 0.25f;
	float scale = 0.5f;
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(-scale, -scale, 0.25f);
		GX_TexCoord2f32(0.0f, tcscal);
		GX_Position3f32(scale, -scale, 0.25f);
		GX_TexCoord2f32(tcscal, tcscal);
		GX_Position3f32(scale, scale, 0.25f);
		GX_TexCoord2f32(tcscal, 0.0f);
		GX_Position3f32(-scale, scale, 0.25f);
		GX_TexCoord2f32(0.0f, 0.0f);
}


#endif