/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Copyright European Organization for Nuclear Research (CERN)
Licensed under the Apache License, Version 2.0 (the "License");
You may not use this file except in compliance with the License.
You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
Authors:
 - Gabriele Gaetano Fronzé, <gfronze@cern.ch>, 2019-2020
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef RUCIO_FUSE_REST_API_H
#define RUCIO_FUSE_REST_API_H

#include <vector>
#include <string>
#include <map>
#include <utils.h>
#include <unordered_map>
#include <fastlog.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Error return values definition
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TOKEN_OK 0
#define SERVER_NOT_LOADED 1
#define CANNOT_AUTH 2
#define TOKEN_ERROR 3
#define CURL_ERROR 4

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ping and server validation methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool rucio_ping(const std::string& short_server_name);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Token retrieval methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int rucio_get_auth_token(const std::string& short_server_name);
int rucio_get_auth_token_userpass(const std::string& short_server_name);
int rucio_get_auth_token_x509(const std::string& short_server_name);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Token and server validation methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool rucio_validate_server(const std::string& short_server_name);
bool rucio_is_token_valid(const std::string& short_server_name);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method used to retrieve the list of valid servers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::vector<std::string>& rucio_list_servers();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Scopes handling cache and methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static std::unordered_map<std::string, std::vector<std::string>> scopes_cache;
std::vector<std::string> rucio_list_scopes(const std::string& short_server_name);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DiDs handling cache and methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static std::unordered_map<std::string, std::vector<rucio_did>> dids_cache;
std::vector<rucio_did> rucio_list_dids(const std::string& scope, const std::string& short_server_name);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Containers' DiDs handling cache and methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static std::unordered_map<std::string, std::vector<rucio_did>> container_dids_cache;
std::vector<rucio_did> rucio_list_container_dids(const std::string& scope, const std::string& container_name, const std::string& short_server_name);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities for detecting container DiDs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static std::unordered_map<std::string, bool> is_container_cache;
bool rucio_is_container(const rucio_did& did);
bool rucio_is_container(const std::string& path);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities for detecting file DiDs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static std::unordered_map<std::string, bool> is_file_cache;
bool rucio_is_file(const std::string& path);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Metadata access methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> rucio_get_replicas_metalinks(const std::string& path);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DiD size methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static std::unordered_map<std::string, size_t> file_size_cache;
size_t rucio_get_size(const std::string& path);

#endif //RUCIO_FUSE_REST_API_H
