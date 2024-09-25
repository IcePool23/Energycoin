// Copyright (c) 2014 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2023-2024 The Nrgc Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef NRGC_ZMQ_ZMQCONFIG_H
#define NRGC_ZMQ_ZMQCONFIG_H

#if defined(HAVE_CONFIG_H)
#include "config/nrgc-config.h"
#endif

#include <stdarg.h>
#include <string>

#if ENABLE_ZMQ
#include <zmq.h>
#endif

#include "primitives/block.h"
#include "primitives/transaction.h"

void zmqError(const char *str);

#endif // NRGC_ZMQ_ZMQCONFIG_H
