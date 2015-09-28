# MorsePi
这是一个有趣的项目. 通过这个页面将消息发送给Raspberry Pi, Raspberry Pi会发出对应的声音, 快来试试吧!

## 工作原理
由`morse` web前端作为用户交互界面，将用户的请求添加到消息队列等待处理
由`morsed` Linux应用程序处理消息队列中待处理的信息

## 环境搭建
连接Raspberry Pi，将Raspberry Pi连接到网络，连接LED和蜂鸣器
使用`GPIO0、GPIO7、GPIO8`
LED0:GPIO0
LED1:GPIO7
BUZZ:GPIO8 

## 给Pi更新源
一般使用前需要先更新一下系统。由Raspbian默认更新源很慢，故使用国内中国科技大学的源，速度很快。

* sudo vi  /etc/apt/sources.list  
* 添加`deb http://mirrors.ustc.edu.cn/raspbian/raspbian/ wheezy main contrib non-free rpi`
* sudo apt-get update

## 安装依赖库
安装`wiringPi`库

## 安装Apache2
`sudo apt-get install apache2`
配置`apache`支持CGI程序
修改`/etc/apache2/sites-available/default`文件，添加一下配置

```
	ScriptAlias /morse/cgi-bin/ /var/www/morse/cgi-bin/
	<Directory "/var/www/morse/cgi-bin/">
		AllowOverride None
		Options +ExecCGI -MultiViews +SymLinksIfOwnerMatch
		Order allow,deny
		Allow from all
	</Directory>
```

## 下载代码编译安装
`git clone https://github.com/lvxinliang/MorsePi.git`    
`cd MorsePi/`    
`make`    
`sudo make install`    


