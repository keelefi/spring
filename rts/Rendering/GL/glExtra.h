/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#pragma once

#include <tuple>

#include "myGL.h"
#include "VAO.h"
#include "VBO.h"
#include "RenderBuffers.h"
#include "System/UnorderedMap.hpp"

/*
 *  Draw a circle / rectangle on top of the top surface (ground/water).
 *  Note: Uses the current color.
 */

class CWeapon;
struct WeaponDef;

extern void glSurfaceCircle(const float3& center, float radius, const SColor& col, uint32_t res);
extern void glSurfaceCircleLua(const float3& center, float radius, const SColor& col, uint32_t res);

// params.x := radius, params.y := slope, params.z := gravity
extern void glBallisticCircle(const CWeapon* weapon     , const SColor& color, uint32_t resolution, const float3& center, const float3& params);
extern void glBallisticCircle(const WeaponDef* weaponDef, const SColor& color, uint32_t resolution, const float3& center, const float3& params);
extern void glBallisticCircleLua(const CWeapon* weapon, const SColor& color, uint32_t resolution, const float3& center, const float3& params);
extern void glBallisticCircleLua(const WeaponDef* weaponDef, const SColor& color, uint32_t resolution, const float3& center, const float3& params);

using DrawVolumeFunc = void (*)(const void* data);
extern void glDrawVolume(DrawVolumeFunc drawFunc, const void* data);

extern void glWireCube(uint32_t* listID);
extern void glWireCylinder(uint32_t* listID, uint32_t numDivs, float zSize);
extern void glWireSphere(uint32_t* listID, uint32_t numRows, uint32_t numCols);

template<typename TQuad, typename TColor, typename TRenderBuffer> void gleDrawQuadC(const TQuad& quad, const TColor& color, TRenderBuffer& rb) {
	rb.AddQuadTriangles(
		{ {quad.x1, quad.y1, 0.0f}, color }, //tl
		{ {quad.x2, quad.y1, 0.0f}, color }, //tr
		{ {quad.x2, quad.y2, 0.0f}, color }, //br
		{ {quad.x1, quad.y2, 0.0f}, color }  //bl
	);
}

namespace GL {
	class Shapes {
	public:
		void Init();
		void Kill();
		Shader::IProgramObject* GetShader();
		void DrawSolidSphere(uint32_t numRows, uint32_t numCols);
		void DrawWireSphere(uint32_t numRows, uint32_t numCols);
	private:
		// add other shapes if needed
		spring::unordered_map<std::tuple<uint32_t, uint32_t>, size_t> solidSpheresMap;
		spring::unordered_map<std::tuple<uint32_t, uint32_t>, size_t> wireSpheresMap;
		std::vector<std::tuple<VAO, VBO, VBO>> allObjects;
		Shader::IProgramObject* shader = nullptr;
	private:
		void EnableAttribs() const;
		void DisableAttribs() const;
		auto CreateSolidSphere(uint32_t numRows, uint32_t numCols) -> decltype(solidSpheresMap)::iterator;
		auto CreateWireSphere(uint32_t numRows, uint32_t numCols) -> decltype(wireSpheresMap)::iterator;
	};

	extern Shapes shapes;
}