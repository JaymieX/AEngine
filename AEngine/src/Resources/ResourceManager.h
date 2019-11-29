//#pragma once
//
//#include "Systems/EntityComponent.h"
//
////template <typename... Args>
////struct IAssetBuilder
////{
////	virtual ~IAssetBuilder() = default;	
////	virtual bool CreateAsset() = 0;
////};
////
////template <typename... Args>
////class ModelBuilder final : IAssetBuilder<Args...>
////{
////	ModelBuilder() = default;
////	explicit ModelBuilder(Args... args);
////	~ModelBuilder() override;
////
////	bool CreateAsset() override;
////};
////
////struct AssetBuilderInfo
////{
////	std::vector<AssetBuilderInfo*> entitiesAttached;
////	std::vector<Component*> componentsAttached;
////};
//
//class ResourceManager
//{
//public:
//	ResourceManager(const ResourceManager&) = delete;
//	ResourceManager(ResourceManager&&) = delete;
//	ResourceManager& operator=(const ResourceManager&) = delete;
//	ResourceManager& operator=(ResourceManager&&) = delete;
//
//	static ResourceManager* GetInstance(EntityManager* manager);
//	
//	void CreateModel(std::string, std::string);
//private:
//	explicit ResourceManager(EntityManager* manager) : manager(manager) { }
//	~ResourceManager();
//
//	EntityManager* manager = nullptr;
//	std::map<std::string, class Model*> models;
//	
//	static std::unique_ptr<ResourceManager> instance;
//	friend std::default_delete<ResourceManager>;
//};
//
//
//
//
//
//
