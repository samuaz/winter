//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-10-10.
//

#ifndef WINTERC_WINTER_UUID_GENERATOR_H
#define WINTERC_WINTER_UUID_GENERATOR_H

#include <sstream>
#include <string>

namespace winter::uuid {
std::string generateUUID();

std::istringstream generateUUIDBlob();
}  // namespace winter::uuid
#endif	// WINTERC_WINTER_UUID_GENERATOR_H
