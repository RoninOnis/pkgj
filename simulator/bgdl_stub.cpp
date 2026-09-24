// bgdl_stub.cpp
// Stub implementation of bgdl.hpp for the pkgj Linux simulator.
// Background download (LiveArea queue) is not available on PC;
// calls are silently ignored.

#include "bgdl.hpp"

#include <cstdio>

void pkgi_start_bgdl(
        const int type,
        const std::string& title,
        const std::string& url,
        const std::vector<uint8_t>& rif,
        const std::string& license_path)
{
    (void)type;
    (void)rif;
    (void)license_path;
    fprintf(stderr,
            "[sim] pkgi_start_bgdl: bgdl not supported in simulator "
            "(title=%s, url=%s)\n",
            title.c_str(), url.c_str());
}
