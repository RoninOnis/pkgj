#pragma once

#include <cstdint>
#include <string>
#include <vector>

enum BgdlType
{
    BgdlTypePsp = 0x00,
    BgdlTypePsm = 0x06,
    BgdlTypeGame = 0x16,
    BgdlTypeDlc = 0x17,
    BgdlTypeTheme = 0xC,
};

void pkgi_start_bgdl(
        const int type,
        const std::string& title,
        const std::string& url,
        const std::vector<uint8_t>& rif,
        const std::string& license_path = "ux0:bgdl/temp.dat");
