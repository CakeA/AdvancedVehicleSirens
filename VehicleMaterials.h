#pragma once

#include <string>
#include <map>

#include "PluginMultiplayer.h"

#include "game_sa/CVehicle.h"
#include "game_sa/CPools.h"
#include "game_sa/CModelInfo.h"

#include "game_sa/NodeName.h"
#include "game_sa/RenderWare.h"

extern unsigned int FramePluginOffset;

#define FRAME_EXTENSION(frame) ((FramePlugin *)((unsigned int)frame + FramePluginOffset))

typedef RpMaterial* (*VehicleMaterialFunction)(CVehicle* vehicle, RpMaterial* material);

typedef void (*VehicleMaterialRender)(CVehicle* vehicle, int index);

typedef void (*VehicleDummyFunction)(CVehicle* vehicle, RwFrame* frame, std::string name, bool parent);

class VehicleMaterial {
	public:
		RpMaterial* Material;

		RwTexture* Texture;
		RwTexture* TextureActive;

		RwRGBA Color;

		VehicleMaterial(RpMaterial* material);
};

class VehicleMaterials {
	public:
		static void Register(VehicleMaterialFunction function);
		static void RegisterRender(VehicleMaterialRender render);
		static void RegisterDummy(VehicleDummyFunction function);

		static void OnModelSet(CVehicle* vehicle, int model);
		static void OnRender(CVehicle* vehicke);

		static void StoreMaterial(std::pair<unsigned int*, unsigned int> pair);

		static void RestoreMaterials();

	private:
		static std::vector<VehicleMaterialFunction> functions;

		static std::vector<VehicleMaterialRender> renders;

		static std::vector<VehicleDummyFunction> dummy;

		static std::map<int, std::map<RpMaterial*, bool>> materials;
		static std::map<int, std::map<RwFrame*, bool>> frames;
		static std::map<int, bool> dummies;

		static CVehicle* currentVehicle;

		static std::list<std::pair<unsigned int*, unsigned int>> storedMaterials;

		static void findDummies(CVehicle* vehicle, RwFrame* frame, bool parent = false);
};
