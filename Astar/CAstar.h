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
 
    上下左右走一格花销为10，斜着走一格花销为14，以方便计算
    即格子宽高为10 对角线为14
 */
#ifndef __Astar__CAstar__
#define __Astar__CAstar__

#include <stdio.h>
#include <vector>
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
    bool operator == (const APoint& po)
    {
        if (x == po.x && y == po.y)
        {
            return true;
        }
        return false;
    }
   
};

class CAstar
{
    vector<APoint*> _openList;      //开放列表
    vector<APoint*> _closeList;     //关闭列表
    vector<APoint*> _neighbourList; //周边节点
    APoint* _endPoint;
    APoint* _curPoint;
    vector< vector<APoint*> > _allPoints;
public:
    CAstar();
    ~CAstar();
    APoint* findWay(APoint* beginPoint,APoint* endPoint,vector< vector<APoint*> >& allPoints);
//    APoint* findWay(int beginX,int beginY,int endX,int endY);
private:
    int getF(APoint *point);
    int getH(APoint *point);
    vector<APoint*> getNeighboringPoint(APoint* point);
};




#endif /* defined(__Astar__CAstar__) */
