#ifndef FIELD_DRAW_H
#define FIELD_DRAW_H

uint8_t *treemtxarr;
uint8_t *treeleavesmtxarr;

void bs_loadTreeMatricies(Mtx view, float x, float y, float z, int frame); //lalala

void drawField() {
	GXColor fieldAmbient = {138, 189, 255, 0xff};
	GXColor basicallyHalfFieldAmbient = {69, 95, 128, 0xff};

	//A skybox

			GX_SetNumTevStages(1);

			GX_SetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
			GX_SetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

			GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);

			GX_SetZMode(GX_FALSE, GX_NEVER, GX_FALSE);	
			liy_VtxDescConfig(LV_VPIDX16 | LV_TCIDX16, 0);
			guMtxIdentity(model);
			guMtxRotAxisDeg(model, &zAxis, 180.0f);
			guMtxTransApply(model, model, cam.x, cam.y, cam.z);
			guMtxConcat(view,model,modelview);
			GX_LoadPosMtxImm(modelview, GX_PNMTX0);

			GX_SetCullMode(GX_CULL_NONE);
			GX_LoadTexObj(&skyboxTexObj, GX_TEXMAP0);
			ag_draw_skybox(0);

			GX_SetCullMode(GX_CULL_FRONT);
			GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);	

		// A tree

			setlight(view, fieldAmbient, 0);

			GX_SetNumTevStages(1);

			GX_SetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
			GX_SetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

			GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP6, GX_COLOR0A0);

			//GX_SetChanAmbColor(GX_COLOR0A0,fieldAmbient); // i just think they're neat

			bs_loadTreeMatricies(view, 1.0f, 5.0f, 0.0f, rframe);

			GX_SetArray(GX_VA_POS, &treevertpos[0], sizeof(f32)*3);
			GX_SetArray(GX_VA_NRM, &treevertnor[0], sizeof(f32)*3); 
			GX_SetArray(GX_VA_TEX0, &treetexcord[0], sizeof(f32)*2); 

			liy_VtxDescConfig(LV_VPIDX16 | LV_VNIDX16 | LV_TCIDX16 | LV_MX | LV_VC, 0); 
			drawArrConfig(LV_VPIDX16 | LV_VNIDX16 | LV_TCIDX16 | LV_MX | LV_VC, treetricount, 0, 
					NULL, NULL, treevertposidx,
					NULL, NULL, treevertnoridx,
					NULL, NULL, treetexcordidx,
					treemtxarr,
					treevertcol);


			// the leaves 
	
			GX_SetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP); // no blending for these
			GX_SetAlphaUpdate(GX_FALSE);
			GX_SetAlphaCompare(GX_GREATER, 128, GX_AOP_AND, GX_ALWAYS, 0);
			GX_SetZCompLoc(GX_FALSE);

			GX_SetNumTevStages(1);

			GX_SetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
			GX_SetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);

			GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP6, GX_COLOR0A0);

			GX_SetChanCtrl(GX_COLOR0A0, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0 | GX_LIGHT1, GX_DF_CLAMP, GX_AF_NONE);	

			GX_SetChanAmbColor(GX_COLOR0A0, basicallyHalfFieldAmbient);
			
			GX_SetArray(GX_VA_POS, &treeleavesvertpos[0], sizeof(f32)*3);
			GX_SetArray(GX_VA_NRM, &treeleavesvertnor[0], sizeof(f32)*3); 
			GX_SetArray(GX_VA_TEX0, &treeleavestexcord[0], sizeof(f32)*2); 

			liy_VtxDescConfig(LV_VPIDX16 | LV_VNIDX16 | LV_TCIDX16 | LV_MX, 0); 
			drawArrConfig(LV_VPIDX16 | LV_VNIDX16 | LV_TCIDX16 | LV_MX, treeleavestricount, 0, 
					NULL, NULL, treeleavesvertposidx,
					NULL, NULL, treeleavesvertnoridx,
					NULL, NULL, treeleavestexcordidx,
					treeleavesmtxarr,
					NULL);

			GX_SetChanAmbColor(GX_COLOR0A0,fieldAmbient);

			GX_SetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR); //disable alpha
			GX_SetAlphaUpdate(GX_FALSE);
			GX_SetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
			GX_SetZCompLoc(GX_TRUE);

			GX_SetCurrentMtx(GX_PNMTX0);

		// End tree

		// Unlit vertcol

			GXColor oopsies = {140, 140, 140, 255}; 

			GX_SetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
			GX_SetTevKColor(GX_KCOLOR0, oopsies);

			nolight();
			GX_SetChanCtrl(GX_COLOR0A0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHTNULL, GX_DF_CLAMP, GX_AF_NONE);	

			GX_SetNumTevStages(1);

			GX_SetTevOp(GX_TEVSTAGE0,GX_PASSCLR);
	
			//is this free??? i think this is free?? i can do brightness correction for free. because otherwise i'd be using CC_ONE
			GX_SetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_KONST, GX_CC_ZERO);
			GX_SetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);

			GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);

			guMtxIdentity(model);
			guMtxConcat(view,model,modelview);

			LX_LoadMtxImm(modelview, GX_PNMTX0);
			
			GX_SetCurrentMtx(GX_PNMTX0);


			liy_VtxDescConfig(LV_VPIDX16 | LV_VC, 0); 
			ag_draw_field_vunlit(0);

		//Lit vertcol

			setlight(view, fieldAmbient, 0);
			GX_SetChanCtrl(GX_COLOR0A0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE); //dont want green	
			liy_VtxDescConfig(LV_VPIDX16 | LV_VNIDX16 | LV_VC, 0);
			ag_draw_field_vlit(0);

		//Lit textured

		//building lit

			GX_SetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
			GX_SetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

			GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);

			GX_SetChanCtrl(GX_COLOR0A0, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0 | GX_LIGHT1, GX_DF_CLAMP, GX_AF_NONE);	

			GX_LoadTexObj(&buildingTexObj, GX_TEXMAP0);

			liy_VtxDescConfig(LV_VPIDX16 | LV_VNIDX16 | LV_TCIDX16, 0); 
			ag_draw_buildingopaquelit(0);

			GX_SetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP); // no blending for these
			GX_SetAlphaUpdate(GX_FALSE);
			GX_SetAlphaCompare(GX_GREATER, 1, GX_AOP_AND, GX_ALWAYS, 0);
			GX_SetZCompLoc(GX_FALSE);

			ag_draw_buildingtranslit(0);

			GX_LoadTexObj(&chainlinkTexObj, GX_TEXMAP0);

			liy_VtxDescConfig(LV_VPIDX16 | LV_TCIDX16, 0);
			ag_draw_chainlink(0);

			GX_SetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR); //disable alpha
			GX_SetAlphaUpdate(GX_FALSE);
			GX_SetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
			GX_SetZCompLoc(GX_TRUE);

}

#endif
