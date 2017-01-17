#程序说明
本程序实现了Air Hockey小游戏

#按键说明
- 左方向键：向左移动镜头
- 右方向键：向右移动镜头
- 上方向键：向上移动镜头
- 下方向键：向下移动镜头
- 数字1：启用弱AI（默认）
- 数字2：启用强AI
- 回车：重新开始游戏
- esc：退出程序

运行程序后，按下相应的按键即进行操作。

#文件说明
- Camera.h/cpp：相机类，负责存储计算与视角相关的参数
- Color.h/cpp：颜色类，负责存储各种颜色的RGB值
- Cuboid.h/cpp：长方体类，负责长方体的参数存储与绘制
- Cylinder.h/cpp：圆柱类，负责圆柱体的参数存储与绘制
- Game.h/cpp：游戏类，本程序的核心类，负责游戏场景的绘制、游戏逻辑的运行
- HandleError.h/cpp：错误处理类，负责输出错误信息
- HockeyAI.h/cpp：AI类，负责计算电脑玩家方的下一步行动
- Image.h/cpp：图像类，负责读取纹理图像、存储纹理图像、对像素进行操作等等。
- Rect.h/cpp：矩形类，负责矩形的参数存储与绘制
- utils.h/cpp：常用工具函数
- Vector3.h/cpp：3维向量类，负责实现常用向量计算
- floor.bmp：地板纹理

# 运行说明

## 部署

将项目导入VS后，编译，将在bin目录下生成repos.exe可执行文件，运行即可。

或者可以直接运行已编译好的repos.exe

## 运行

双击repos.exe即可。