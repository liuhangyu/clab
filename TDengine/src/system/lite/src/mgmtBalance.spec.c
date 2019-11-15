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
#include "mgmtBalance.h"

void mgmtStartBalanceTimer(int mseconds) {}

int mgmtInitBalance() { return 0; }

void mgmtCleanupBalance() {}

int mgmtAllocVnodes(SVgObj *pVgroup) {
  int        selectedVnode = -1;
  SDnodeObj *pDnode = &dnodeObj;

  for (int i = 0; i < pDnode->numOfVnodes; i++) {
    int vnode = (i + pDnode->lastAllocVnode) % pDnode->numOfVnodes;
    if (pDnode->vload[vnode].vgId == 0 && pDnode->vload[vnode].status == TSDB_VN_STATUS_READY) {
      selectedVnode = vnode;
      break;
    }
  }

  if (selectedVnode == -1) {
    mError("vgroup:%d alloc vnode failed, free vnodes:%d", pVgroup->vgId, pDnode->numOfFreeVnodes);
    return -1;
  } else {
    mTrace("vgroup:%d allocate vnode:%d, last allocated vnode:%d", pVgroup->vgId, selectedVnode,
           pDnode->lastAllocVnode);
    pVgroup->vnodeGid[0].vnode = selectedVnode;
    pDnode->lastAllocVnode = selectedVnode + 1;
    if (pDnode->lastAllocVnode >= pDnode->numOfVnodes) pDnode->lastAllocVnode = 0;
    return 0;
  }
}

bool mgmtCheckModuleInDnode(SDnodeObj *pDnode, int moduleType) {
  return tsModule[moduleType].num != 0;
}

bool mgmtCheckVnodeReady(SDnodeObj *pDnode, SVgObj *pVgroup, SVnodeGid *pVnode) { return true; }

void mgmtUpdateDnodeState(SDnodeObj *pDnode, int lbState) {}

void mgmtUpdateVgroupState(SVgObj *pVgroup, int lbState, int srcIp) {}

bool mgmtAddVnode(SVgObj *pVgroup, SDnodeObj *pSrcDnode, SDnodeObj *pDestDnode) { return false; }