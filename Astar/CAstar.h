//
//  CAstar.h
//  Astar
//
//  Created by xujw on 15/4/9.
//  Copyright (c) 2015年 xujw. All rights reserved.
//
/*
    F:路径评分 = g+h
    G:走一格格子的花销
    H:当前格子到目标格子的估算花销
 */
#ifndef __Astar__CAstar__
#define __Astar__CAstar__

#include <stdio.h>
#include <list>
#include <vector>
#include <stdlib.h>
#include <iostream>
using namespace std;

//地图最大值
#define MAX_X 10
#define MAX_Y 10

enum class AType
{
    ATYPE_UNKNOWN,
    ATYPE_CLOSED,
    ATYPE_OPENED,
    ATYPE_BARRIER   //障碍
};
enum class ADir
{
    ADIR_UP,
    ADIR_DOWN,
    ADIR_LEFT,
    ADIR_RIGHT
};

class APoint
{
public:
    APoint();
    ~APoint();
    int x;
    int y;
    AType type;   //类型:障碍、开放列表、关闭列表
    int f;  //f = g+h
    int g;
    int h;
    APoint *parent;
};

class CAstar
{
    vector<APoint*> _openList;
    vector<APoint*> _closeList;
    APoint* _endPoint;
    APoint* _curPoint;
    APoint*_allPoints[MAX_X][MAX_Y];
public:
    CAstar();
    ~CAstar();
    APoint* findWay(APoint* beginPoint,APoint* endPoint,APoint*allpoints[MAX_X][MAX_Y]);
//    APoint* findWay(int beginX,int beginY,int endX,int endY);
private:
    int getF(APoint *point);
    int getH(APoint *point);
    bool isInList(const vector<APoint*>& lis,APoint*point);
    vector<APoint*> getNeighboringPoint(APoint* point);
};





#endif /* defined(__Astar__CAstar__) */
