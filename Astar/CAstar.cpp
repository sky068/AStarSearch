//
//  CAstar.cpp
//  Astar
//
//  Created by xujw on 15/4/9.
//  Copyright (c) 2015年 xujw. All rights reserved.
//
//  上下左右走一格花销为10，斜着走一格花销为14，以方便计算
//  即格子宽高为10 对角线为14
#include "CAstar.h"

//自定义排序函数
bool mySort(const APoint* p1,const APoint* p2)
{
    return p1->f < p2->f;
}

APoint::APoint():x(0)
                ,y(0)
                ,h(0)
                ,f(0)
                ,g(0)
                ,parent(nullptr)
                ,type(AType::ATYPE_UNKNOWN)
{
    
}
APoint::~APoint()
{}


#pragma mark------CAstar-------

CAstar::CAstar():_endPoint(nullptr)
                ,_curPoint(nullptr)
{
}
CAstar::~CAstar()
{
}

APoint* CAstar::findWay(APoint *beginPoint, APoint *endPoint,APoint*allpoints[MAX_X][MAX_Y])
{
    _endPoint = endPoint;
    for (int i=0; i<MAX_X; i++)
    {
        for (int j = 0; j<MAX_Y; j++)
        {
            _allPoints[i][j] = allpoints[i][j];
        }
    }
    _openList.push_back(beginPoint);
    beginPoint->type = AType::ATYPE_OPENED;
    
    //如果开放列表不为空并且目标节点不在开放列表里
    while (!_openList.empty() && _endPoint->type!=AType::ATYPE_OPENED)
    {
        _curPoint = _openList.at(0);

        //获取当前节点周边的四个点 已经排好序了
        vector<APoint*> neVec = getNeighboringPoint(_curPoint);
        for (int i = 0; i<neVec.size(); i++)
        {
            APoint *po = neVec.at(i);
            if (po->type == AType::ATYPE_CLOSED || po->type == AType::ATYPE_BARRIER)
            {
                continue;
            }
            
            //从open列表移除当前节点，加入到关闭列表里
            _openList.erase(_openList.begin());
            _curPoint->type = AType::ATYPE_CLOSED;
            _closeList.push_back(_curPoint);
            
            //选择一个没在开放列表里的F值最小的加到开放列表里
            if(po->type != AType::ATYPE_OPENED)
            {
                po->parent = _curPoint;
                po->type = AType::ATYPE_OPENED;
                _openList.push_back(po);
                break;
            }
        }        
    }
//    if (_endPoint->type == AType::ATYPE_OPENED)
//    {
//        return _endPoint;
//    }
    
    if (!_openList.empty())
    {
        cout<<"---have found way---"<<endl;
        return _openList.at(0);
    }
    
    cout<<"---can not find way---"<<endl;
    
    return nullptr;
}

//APoint* CAstar::findWay(int beginX, int beginY, int endX, int endY)
//{
//    
//    
//    return nullptr;
//}

int CAstar::getF(APoint *point)
{
    return (point->g + getH(point));
}
int CAstar::getH(APoint *point)
{
    //曼哈顿城市街区估算法
    return (abs(_endPoint->y - point->y) + abs(_endPoint->x - point->x))*10;
}

bool CAstar::isInList(const vector<APoint *>& lis, APoint *point)
{
    for (int i = 0; i<lis.size(); i++)
    {
        if (lis.at(i)==point)
        {
            return true;
        }
    }
    return false;
}

vector<APoint*> CAstar::getNeighboringPoint(APoint *point)
{
    vector<APoint*> tmpVec;
    if (point->y < MAX_Y-1)
    {
        tmpVec.push_back(_allPoints[point->x][point->y+1]);
        _allPoints[point->x][point->y+1]->g = point->g+10;
        _allPoints[point->x][point->y+1]->f = getF(_allPoints[point->x][point->y+1]);
    }
    if (point->y >0)
    {
        tmpVec.push_back(_allPoints[point->x][point->y-1]);
        _allPoints[point->x][point->y-1]->g = point->g+10;
        _allPoints[point->x][point->y-1]->f = getF( _allPoints[point->x][point->y-1]);
    }
    if (point->x < MAX_X-1)
    {
        tmpVec.push_back(_allPoints[point->x+1][point->y]);
        _allPoints[point->x+1][point->y]->g = point->g+10;
        _allPoints[point->x+1][point->y]->f = getF(_allPoints[point->x+1][point->y]);
    }
    if (point->x >0)
    {
        tmpVec.push_back(_allPoints[point->x-1][point->y]);
        _allPoints[point->x-1][point->y]->g = point->g+10;
        _allPoints[point->x-1][point->y]->f = getF(_allPoints[point->x-1][point->y]);
    }
    //排序 f值最小的排到最前面
    sort(tmpVec.begin(), tmpVec.end(), mySort);
    
    return tmpVec;
}


