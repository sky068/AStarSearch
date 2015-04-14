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
{
}


#pragma mark------CAstar-------

CAstar::CAstar():_endPoint(nullptr)
                ,_curPoint(nullptr)
{
}

CAstar::~CAstar()
{
    _openList.clear();
    _closeList.clear();
    _neighbourList.clear();
    _allPoints.clear();
}

APoint* CAstar::findWay(APoint *beginPoint, APoint *endPoint,vector< vector<APoint*> >& allPoints)
{
    //传递地图
    _allPoints = allPoints;
    
    _endPoint = endPoint;

    if (_endPoint->type == AType::ATYPE_BARRIER)
    {
        cout<<"终点是障碍"<<endl;
        return nullptr;
    }
    if (*_endPoint == *beginPoint)
    {
        cout<<"起始点相同"<<endl;
        return nullptr;
    }
    
    _openList.push_back(beginPoint);
    beginPoint->type = AType::ATYPE_OPENED;
    beginPoint->f = getF(beginPoint);
    //---------
    do
    {
        //获取最小值的节点
        _curPoint = _openList[0];
        _openList.erase(_openList.begin());
        _curPoint->type = AType::ATYPE_CLOSED;
        _closeList.push_back(_curPoint);
        
        if (*_curPoint == *_endPoint)
        {
            cout<<"have find way"<<endl;
            return _curPoint;
        }
        //获取相邻的节点
        vector<APoint*> neVec = getNeighboringPoint(_curPoint);
        for (int i = 0; i<neVec.size(); i++)
        {
            auto tmpoint = neVec[i];
            if (tmpoint->type == AType::ATYPE_CLOSED)
            {
                continue;
            }
            //是否在开放列表里
            if (tmpoint->type != AType::ATYPE_OPENED)
            {
                tmpoint->parent = _curPoint;
                tmpoint->g = _curPoint->g + 10;
                //计算H值
                tmpoint->h = getH(tmpoint);
                //添加到开放列表里
                _openList.push_back(tmpoint);
                tmpoint->type = AType::ATYPE_OPENED;
            }
            else
            {
                //已经在开放列表里
                if (tmpoint->h < _curPoint->h)
                {
                    tmpoint->parent = _curPoint;
                    tmpoint->g = _curPoint->g + 10;
                }
            }
        }
        //排序 F值最小的排在前面
        sort(_openList.begin(), _openList.end(), mySort);
        
    } while (_openList.size()>0);
    
    
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
    _neighbourList.clear();
//    cout<<"nei size:"<<_neighbourList.size()<<endl;
    if (point->x < MAX_X-1)
    {
        if (_allPoints[point->x+1][point->y]->type != AType::ATYPE_BARRIER)
        {
            _neighbourList.push_back(_allPoints[point->x+1][point->y]);
        }
    }
    if (point->x >0)
    {
        if (_allPoints[point->x-1][point->y]->type != AType::ATYPE_BARRIER)
        {
            _neighbourList.push_back(_allPoints[point->x-1][point->y]);
        }
    }
    if (point->y < MAX_Y-1)
    {
        if (_allPoints[point->x][point->y+1]->type != AType::ATYPE_BARRIER)
        {
            _neighbourList.push_back(_allPoints[point->x][point->y+1]);
        }
    }
    if (point->y >0)
    {
        if (_allPoints[point->x][point->y-1]->type != AType::ATYPE_BARRIER)
        {
            _neighbourList.push_back(_allPoints[point->x][point->y-1]);
        }
    }
    
    return _neighbourList;
}


