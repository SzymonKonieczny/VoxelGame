#pragma once
#ifndef GLOBAL_H;
#define GLOBAL_H

#define LightPropagationInChunkManager true
#define SAVE_UNLOADED_CHUNKS false
extern bool WindowResized;
extern int WorldSeed;
extern  int ChunkSize;		// = 16;
extern  int screenWidth;	//	= 800; //1280;
extern  int screenHeight;	// = 800;// 720;
extern  int ChunksInColumn;	//	 = 16;
extern  int RenderDistance;	// = 8;
extern bool LightRendering;	// = 8;
extern bool renderShadowMap;
constexpr int MinFastNoiseDim = 3;
#endif  GLOBAL_H;