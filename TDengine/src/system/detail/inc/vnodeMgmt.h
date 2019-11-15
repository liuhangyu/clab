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

#ifndef TDENGINE_VNODEMGMT_H
#define TDENGINE_VNODEMGMT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char  id[20];
  char  sid;
  void *thandle;
  int   mgmtIndex;
  char  status;  // 0:offline, 1:online
} SMgmtObj;

int vnodeProcessCreateMeterRequest(char *pMsg, int msgLen, SMgmtObj *pMgmtObj);
int vnodeProcessRemoveMeterRequest(char *pMsg, int msgLen, SMgmtObj *pMgmtObj);

#ifdef __cplusplus
}
#endif

#endif  // TDENGINE_VNODEMGMT_H
