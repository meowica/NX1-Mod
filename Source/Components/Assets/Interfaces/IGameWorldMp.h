#pragma once

namespace IGameWorldMp
{
	struct G_GlassPiece
	{
		unsigned short damageTaken;
		unsigned short collapseTime;
		int lastStateChangeTime;
		unsigned char impactDir;
		unsigned char impactPos[2];
	};

	struct G_GlassName
	{
		char* nameStr;
		unsigned short name;
		unsigned short pieceCount;
		unsigned short *pieceIndices;
	};

	struct G_GlassData
	{
		G_GlassPiece* glassPieces;
		unsigned int pieceCount;
		unsigned short damageToWeaken;
		unsigned short damageToDestroy;
		unsigned int glassNameCount;
		G_GlassName* glassNames;
		unsigned char pad[108];
	};

	struct GameWorldMp
	{
		const char* name;
		G_GlassData* g_glassData;
	};

#ifdef IS_MP
	namespace MP
	{
		void Load();
		void Unload();
	}
#elif IS_SP
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}
