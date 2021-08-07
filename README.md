

##### 实现功能：

1. 设计并实现了一个下载程序，可根据输入的url，下载该网页及该网页链接上的资源并存储到本地；
2. 使用Socket API
3. 下载url下的相关资源
4. 下载后的资源间保持相对路径
5. 可指定下载的目录层数（未全部实现），考虑到程序的实际使用情况只下载一层
6. 可分析复杂url，通过正则表达式实现
     exp：http://images.gaga.me/photos2/2019/0416/5cb5e9950e25a.jpeg?watermark/1/image/aHR0cDovL3Jlcy5nYWdhLm1lL3dhdGVybWFyay9wYWl4aW4xLnBuZz9pbWFnZVZpZXcyLzIvdy80MDAvaC80MDA=/dissolve/50/gravity/Center/ws/1
7. 程序具有一定的健壮性，对异常情况有一定的处理能力
8. 自动格式化输入的url
     exp：输入http://www.baidu.com 则自动格式为 http://www.baidu.com/
9. 若收到的HTTP响应包无内容，即只有HTTP头部时，自动生成一个html文件，显示error！
10. gif等图片文件暂无法处理



##### 功能描述：

- 实现URL类以及类内相关函数的实现

- 实现对于文件操作（如创建文件夹、格式化路径）等的实现

- 实现对dll的初始化以及对服务器端的连接，访问，发送数据，并保证程序的健壮性
- 实现接收数据，通过响应头部内容按具体方式下载文件
