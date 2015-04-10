//
//  main.cpp
//  Astar
//
//  Created by xujw on 15/4/9.
//  Copyright (c) 2015年 xujw. All rights reserved.
//

#include <iostream>
#include "CAstar.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //初始化地图矩阵 0代表障碍
    int mapdata[MAX_X][MAX_Y] =
    {
        {1,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,0},
        {1,1,1,1,1,1,1,1,1,1},
        {0,1,1,1,1,1,1,1,1,1},
        {1,1,0,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,0,1,1,1,1},
    };
    
    //创建地图
    APoint* map[10][10];
    for (int i = 0; i<MAX_X; i++)
    {
        for (int j = 0; j<MAX_Y; j++)
        {
            APoint *point = new APoint();
            map[i][j] = point;
            point->x = i;
            point->y = j;
            if (mapdata[i][j]==0)
            {
                point->type = AType::ATYPE_BARRIER;
            }
        }
    }
    
    //开始寻路
    auto star = new CAstar();
    auto point = star->findWay(map[0][0], map[9][9], map);
   
    cout<<"---下面是路径点(倒序)---"<<endl;
    while (point)
    {
        cout<<point->x<<","<<point->y<<endl;
        point = point->parent;
    }
    
    
    delete star;
    
    return 0;
}
