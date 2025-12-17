#include "structures/asset.h"

namespace kaamo::structures {

Asset::Asset(Address base) : GameStructure(base) {}

void Asset::bind_to_lua(sol::state& lua) {
    lua.new_usertype<Asset>("Asset",
        sol::no_constructor,
        "GetAssetFilePath", &Asset::get_asset_file_path,
        "SetAssetFilePath", &Asset::set_asset_file_path
    );
}

}
