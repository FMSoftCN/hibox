/*
 * Copyright (c) 2012,2017 Eric Haszlakiewicz
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 */

/**
 * @file
 * @brief Methods for retrieving the json-c version.
 */
#ifndef _json_c_version_h_
#define _json_c_version_h_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @see JSON_C_VERSION
 * @return the version of the json-c library as a string
 */
HIBOX_EXPORT const char *json_c_version(void); /* Returns JSON_C_VERSION */

/**
 * The json-c version encoded into an int, with the low order 8 bits
 * being the micro version, the next higher 8 bits being the minor version
 * and the next higher 8 bits being the major version.
 * For example, 7.12.99 would be 0x00070B63.
 *
 * @see JSON_C_VERSION_NUM
 * @return the version of the json-c library as an int
 */
HIBOX_EXPORT int json_c_version_num(void); /* Returns JSON_C_VERSION_NUM */

#ifdef __cplusplus
}
#endif

#endif
