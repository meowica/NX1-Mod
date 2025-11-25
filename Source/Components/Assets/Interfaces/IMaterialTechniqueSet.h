#pragma once

#include "IMaterialVertexDeclaration.h"
#include "IMaterialVertexShader.h"
#include "IMaterialPixelShader.h"

namespace IMaterialTechniqueSet
{
	struct MaterialArgumentCodeConst
	{
		unsigned short index;
		unsigned char firstRow;
		unsigned char rowCount;
	};

	union MaterialArgumentDef
	{
		const float* literalConst;
		MaterialArgumentCodeConst codeConst;
		unsigned int codeSampler;
		unsigned int nameHash;
	};

	struct MaterialShaderArgument
	{
		unsigned char type;
		unsigned char buffer_bind_slot;
		unsigned short dest;
		MaterialArgumentDef u;
	};

	struct MaterialPass
	{
		IMaterialVertexDeclaration::MaterialVertexDeclaration* vertexDecl;
		IMaterialVertexShader::MaterialVertexShader* vertexShaderArray[17];
		IMaterialVertexShader::MaterialVertexShader* vertexShader;
		IMaterialPixelShader::MaterialPixelShader* pixelShader;
		unsigned char perPrimArgCount;
		unsigned char perObjArgCount;
		unsigned char stableArgCount;
		unsigned char customSamplerFlags;
		unsigned char precompiledIndex;
		MaterialShaderArgument* args;
	};

	struct MaterialTechnique
	{
		const char* name;
		unsigned short flags;
		unsigned short passCount;
		MaterialPass passArray[1];
	};

	struct MaterialTechniqueSet
	{
		const char* name;
		unsigned char worldVertFormat;
		unsigned char unused[2];
		MaterialTechniqueSet* remappedTechniqueSet;
		MaterialTechnique* techniques[52];
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
