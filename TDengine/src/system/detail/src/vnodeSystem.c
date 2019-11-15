/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define _DEFAULT_SOURCE
#include <pthread.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

#include "tsdb.h"
#include "tsocket.h"
#include "vnode.h"
#include "vnodeSystem.h"

// internal global, not configurable
void *   vnodeTmrCtrl;
void **  rpcQhandle;
void *   dmQhandle;
void *   queryQhandle;
int      tsVnodePeers = TSDB_VNODES_SUPPORT - 1;
int      tsMaxQueues;
uint32_t tsRebootTime;

void vnodeCleanUpSystem() {
  vnodeCleanUpVnodes();
}

bool vnodeInitQueryHandle() {
  int numOfThreads = tsRatioOfQueryThreads * tsNumOfCores * tsNumOfThreadsPerCore;
  if (numOfThreads < 1) numOfThreads = 1;
  queryQhandle = taosInitScheduler(tsNumOfVnodesPerCore * tsNumOfCores * tsSessionsPerVnode, numOfThreads, "query");
  return true;
}

bool vnodeInitTmrCtl() {
  vnodeTmrCtrl = taosTmrInit(TSDB_MAX_VNODES * (tsVnodePeers + 10) + tsSessionsPerVnode + 1000, 200, 60000, "DND-vnode");
  if (vnodeTmrCtrl == NULL) {
    dError("failed to init timer, exit");
    return false;
  }
  return true;
}

int vnodeInitSystem() {

  if (!vnodeInitQueryHandle()) {
    dError("failed to init query qhandle, exit");
    return -1;
  }

  if (!vnodeInitTmrCtl()) {
    dError("failed to init timer, exit");
    return -1;
  }

  if (vnodeInitStore() < 0) {
    dError("failed to init vnode storage");
    return -1;
  }

  int numOfThreads = (1.0 - tsRatioOfQueryThreads) * tsNumOfCores * tsNumOfThreadsPerCore / 2.0;
  if (numOfThreads < 1) numOfThreads = 1;
  if (vnodeInitPeer(numOfThreads) < 0) {
    dError("failed to init vnode peer communication");
    return -1;
  }

  if (vnodeInitMgmt() < 0) {
    dError("failed to init communication to mgmt");
    return -1;
  }

  if (vnodeInitShell() < 0) {
    dError("failed to init communication to shell");
    return -1;
  }

  if (vnodeInitVnodes() < 0) {
    dError("failed to init store");
    return -1;
  }

  dPrint("vnode is initialized successfully");

  return 0;
}

void vnodeInitQHandle() {
  tsMaxQueues = (1.0 - tsRatioOfQueryThreads)*tsNumOfCores*tsNumOfThreadsPerCore / 2.0;
  if (tsMaxQueues < 1) tsMaxQueues = 1;

  rpcQhandle = malloc(tsMaxQueues*sizeof(void *));

  for (int i=0; i< tsMaxQueues; ++i ) 
    rpcQhandle[i] = taosInitScheduler(tsSessionsPerVnode, 1, "dnode");

  dmQhandle = taosInitScheduler(tsSessionsPerVnode, 1, "mgmt");
}
