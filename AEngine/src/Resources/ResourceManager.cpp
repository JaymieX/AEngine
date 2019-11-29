#include <Core/AEpch.h>
//#include "ResourceManager.h"
//#include "Graphics/Model.h";
//
//std::unique_ptr<ResourceManager> ResourceManager::instance(nullptr);
//
//ResourceManager* ResourceManager::GetInstance(EntityManager* manager)
//{
//	if (!instance) instance = std::make_unique<ResourceManager>(manager);
//	return instance.get();
//}
//
//void ResourceManager::CreateAsset(const std::string name, const std::string assetPath)
//{
//	auto entity = resourceEntityManager->CreateAndAddEntity();
//
//	
//	//assets.emplace(std::make_pair(name, std::cop));
//}
//
//Entity* ResourceManager::RetrieveAsset(const std::string name)
//{
//	const auto assetIter = assets.find(name);
//	if(!assetIter._Ptr) return nullptr;
//}
//
//ResourceManager::~ResourceManager()
//{
//	
//}
//
//template <typename ... Args>
//ModelBuilder<Args...>::ModelBuilder(Args... args)
//{
//}
//
//template <typename ... Args>
//ModelBuilder<Args...>::~ModelBuilder()
//{
//}
//
//template <typename ... Args>
//bool ModelBuilder<Args...>::CreateAsset()
//{
//	return false;
//}
//