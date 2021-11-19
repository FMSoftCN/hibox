/*
 * Copyright (c) 2012 Eric Haszlakiewicz
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 */
#include "config.h"
#include "hibox_version.h"

const char *json_c_version(void)
{
    return HIBOX_VERSION;
}

int json_c_version_num(void)
{
    return HIBOX_API_VERSION;
}
